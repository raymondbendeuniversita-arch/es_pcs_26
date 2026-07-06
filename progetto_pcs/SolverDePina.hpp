#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>

#include "graph.hpp"
#include "methods.hpp"
#include "graph_visit.hpp"
#include "gradiente_coniugato.hpp"
#include "CircuitComponents.hpp"
#include "CircuitReader.hpp"
#include "CircuitTree.hpp"

class SolverDePina {
public:
    void solve(const CircuitReader& reader) {
        unidirected_graph G = reader.getGraph();
        std::vector<Component> resistors;
        std::vector<Component> voltages;

        for (const auto& comp : reader.getComponents()) {
            if (comp.type == ComponentType::RESISTOR) {
                resistors.push_back(comp);
            } else if (comp.type == ComponentType::VOLTAGE_SOURCE) {
                voltages.push_back(comp);
            }
        }

        if (resistors.empty()) {
            std::cout << "Nessun resistore nel circuito.\n";
            return;
        }

        // generazione dell'albero di copertura T iniziale (usiamo la DFS come prima):
        int source_node = *G.all_nodes().begin();
        lifo<int> s;
        unidirected_graph T = graph_visit(G, source_node, s);

        // isolamento del coalbero C:
        unidirected_graph C = G - T;
        auto cotree_edges = C.all_edges();

        size_t num_resistors = resistors.size();
        size_t num_loops = cotree_edges.size();

        std::cout << "Esecuzione algoritmo di De Pina:\n";
        std::cout << "Numero di resistori (m): " << num_resistors << "\n";
        std::cout << "Numero di maglie individuate (n): " << num_loops << "\n";

        // inizializzazione delle matrici Eigen per la risoluzione del circuito:
        Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistors, num_loops);
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistors, num_resistors);
        Eigen::VectorXd v = Eigen::VectorXd::Zero(num_loops);

        // matrice diagonale delle resistenze R:
        for (size_t i = 0; i < num_resistors; ++i) {
            R(i, i) = resistors[i].value;
        }

        // Ci serve l'oggetto dell'albero per la scrittura estesa col punto
        CircuitTree albero;

        // rappresentazione dei vettori di supporto di De Pina (matrice d'identità iniziale n * n).
        // ciascuna riga rappresenta un vettore di supporto associato a un arco del coalbero:
        std::vector<std::vector<int>> support_vectors(num_loops, std::vector<int>(num_loops, 0));
        for (size_t i = 0; i < num_loops; ++i) {
            support_vectors[i][i] = 1; 
        }

        // vettore che conterrà le maglie trovate dall'algoritmo (ogni maglia è una sequenza ordinata di nodi):
        std::vector<std::vector<int>> final_loops(num_loops);

        // loop principale dell'algoritmo di De Pina:
        for (size_t i = 0; i < num_loops; ++i) {
            
            // per trovare il ciclo a supporto minimo ortogonale al vettore corrente, costruiamo un grafo ausiliario composto dall'albero T più gli archi del coalbero 
            // che hanno un coefficiente attivo (pari a 1) nel vettore di supporto corrente:
            unidirected_graph aux_graph = T;
            for (size_t k = 0; k < num_loops; ++k) {
                if (support_vectors[i][k] == 1) {
                    aux_graph.add_edges(cotree_edges[k].from(), cotree_edges[k].to());
                }
            }

            // cerchiamo il ciclo più corto nell'aux_graph:
            int u = cotree_edges[i].from();
            int v_node = cotree_edges[i].to();

            std::vector<int> tree_path;
            albero.path_in_tree(T, v_node, u, tree_path);

            // ricostruiamo la maglia i-esima:
            std::vector<int> loop_nodes;
            loop_nodes.push_back(u);
            for (int node : tree_path) {
                loop_nodes.push_back(node);
            }
            final_loops[i] = loop_nodes;

            // aggiornamento dei vettori di supporto successivi (serve a mantenere l'indipendenza lineare delle maglie rispetto ai passi futuri):
            for (size_t j = i + 1; j < num_loops; ++j) {
                
                int dot_product = 0;

                for (size_t k = 0; k < num_loops; ++k) {
					if (support_vectors[j][k] == 0) continue;
					
                    int ek_u = cotree_edges[k].from();
                    int ek_v = cotree_edges[k].to();
					
                    for (size_t n = 0; n < loop_nodes.size() - 1; ++n) {
                        int n_c = loop_nodes[n];
                        int n_n = loop_nodes[n + 1];
						
                        if ((n_c == ek_u && n_n == ek_v) || (n_c == ek_v && n_n == ek_u)) {
                           dot_product ^= 1; 
                           break;
                        }
                    }
                }

                // se la maglia interseca l'arco del coalbero j, aggiorniamo il vettore di supporto j tramite l'operazione di XOR:
                if (dot_product == 1) {
                    for (size_t k = 0; k < num_loops; ++k) {
                        support_vectors[j][k] = support_vectors[j][k] ^ support_vectors[i][k];
                    }
                }
            }
        }


        // calcolo dei segni dei generatori e matrice di incidenza B (esattamente come prima):
        for (size_t j = 0; j < num_loops; ++j) {
            const auto& loop_nodes = final_loops[j];

            // segno dei generatori nella maglia j:
            for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                int n_curr = loop_nodes[k];
                int n_next = loop_nodes[k + 1];

                for (const auto& volt : voltages) {
                    if ((volt.node_a == n_curr && volt.node_b == n_next) ||
                        (volt.node_a == n_next && volt.node_b == n_curr)) {
                        
                        if (n_curr == volt.node_b && n_next == volt.node_a) {
                            v(j) += volt.value;  // positivo
                        } else if (n_curr == volt.node_a && n_next == volt.node_b) {
                            v(j) -= volt.value;  // negativo
                        }
                    }
                }
            }


            // matrice d'incidenza B per i resistori nella maglia j:
            for (size_t i = 0; i < num_resistors; ++i) {
                int r_u = resistors[i].node_a;
                int r_v = resistors[i].node_b;
                
                int r_start = std::min(r_u, r_v);
                int r_end = std::max(r_u, r_v);

                for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                    int n_curr = loop_nodes[k];
                    int n_next = loop_nodes[k + 1];

                    if (n_curr == r_start && n_next == r_end) {
                        B(i, j) = 1.0;
                    } else if (n_curr == r_end && n_next == r_start) {
                        B(i, j) = -1.0;
                    }  
                }
            }
        }


        // risoluzione del sistema lineare (B'RB) tramite gradiente coniugato:
        Eigen::MatrixXd A = B.transpose() * R * B;
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(num_loops);
        double toll = 1.0e-10;
        int max_iter = 100;
        
        Eigen::VectorXd x = gradiente_coniugato(A, v, x0, toll, max_iter);
        Eigen::VectorXd V_R = R * B * x;

        // output dei risultati a schermo:
        std::cout << "Risultati delle tensioni sui resistori tramite De Pina:\n";
        for (size_t i = 0; i < num_resistors; ++i) {
            std::cout << resistors[i].name << ": V = " << V_R(i) << " Volts\n";
        }
    }
};