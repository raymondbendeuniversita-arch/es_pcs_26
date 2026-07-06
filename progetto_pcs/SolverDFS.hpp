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

class SolverDFS {
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

        // PRIMA ALTERNATIVA: ci viene richiesto che le maglie fondamentali del circuito devono essere individuate a partire da un albero di copertura generato tramite una visita in profondità (DFS).
        int source_node = *G.all_nodes().begin();    // metodo all_nodes di unidirected_graph implementato in graph.hpp
		
        lifo<int> s;   // struttura LIFO da methods.hpp per eseguire la DFS
        unidirected_graph T = graph_visit(G, source_node, s);    // da graph_visit.hpp

        // calcolo del coalbero C = G \ T mediante l'operatore- implementato in graph.hpp:
        unidirected_graph C = G - T;
        auto cotree_edges = C.all_edges();

        size_t num_resistors = resistors.size();
        size_t num_loops = cotree_edges.size();

        std::cout << "ESECUZIONE ALGORITMO DFS:\n";
		std::cout << "Numero di resistori (m): " << num_resistors << "\n";
        std::cout << "Numero di maglie individuate (n): " << num_loops << "\n";


        // inizializzazione matrici Eigen:
        Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistors, num_loops);   // matrice di incidenza resistori-maglie (sarà dimensione m*n)
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistors, num_resistors);  // magtrice delle resistenza (m*m)
        Eigen::VectorXd v = Eigen::VectorXd::Zero(num_loops);   // vettore dei termini noti pari al numero di maglie (m)

        // inizio a riempire la matrice diagonale delle resistenze R: sulla diagonale ci saranno i valori in ohm di ciascun resistore mentre le altre enetrate della matrice rimangono 0.
        for (size_t i = 0; i < num_resistors; ++i) {
            R(i, i) = resistors[i].value;
        }

        // Ci serve l'oggetto dell'albero per la scrittura estesa col punto
        CircuitTree albero;

        // ci manca da decidere il segno +1 o -1 per ogni generatore e resistore nelle matrici.
        // analizziamo ciascuna maglia indotta dagli archi del coalbero:
        for (size_t j = 0; j < num_loops; ++j) {
            unidirected_edge loop_edge = cotree_edges[j];
            int u = loop_edge.from();
            int v_node = loop_edge.to();

            // trovo il cammino nell'albero T per chiudere la maglia (da v_node a u):
            std::vector<int> tree_path;
            albero.path_in_tree(T, v_node, u, tree_path);

            // costruisco la sequenza ordinata dei nodi della maglia corrente:
            std::vector<int> loop_nodes;
            loop_nodes.push_back(u);   // mettiamo il nodo u in testa e poi attacchiamo il cammino dell'albero, in questo modo otteniamo un anello chiuso che rappresenta il verso di percorrenza della maglia
            for (int node : tree_path) {
                loop_nodes.push_back(node);
            }


            // ricerca del segno dei generatori nella maglia j (in pratica andiamo ad esplorare l'anello definito sopra):
            for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
				
				// analizziamol le coppie adiacenti una dopo l'altra:
                int n_curr = loop_nodes[k];
                int n_next = loop_nodes[k + 1];

                for (const auto& volt : voltages) {
					
                    // controllo se il generatore è presente tra n_curr e n_next:
                    if ((volt.node_a == n_curr && volt.node_b == n_next) ||
                        (volt.node_a == n_next && volt.node_b == n_curr)) {
                        
                        // convenzione fornita: da - a + è positivo. 
                        // in questo caso node_a è il positivo, node_b è il negativo.
                        // se ci muoviamo da node_b a node_a (cioè n_curr == node_b), il contributo è positivo:
                        if (n_curr == volt.node_b && n_next == volt.node_a) {
                            v(j) += volt.value;   // positivo
							
                        } else if (n_curr == volt.node_a && n_next == volt.node_b) {
                            v(j) -= volt.value;   // negativo
                        }
                    }
                }
            }


            // matrice d'incidenza B per i resistori appartenenti alla maglia j:
            for (size_t i = 0; i < num_resistors; ++i) {
                int r_u = resistors[i].node_a;
                int r_v = resistors[i].node_b;
				
				
				// notiamo che la nostra precedente classe unidirected_graph implementava un grafo non orientato, mentre qui abbiamo bisogno di un grafo orientato.
                // per convenzione del progetto, ogni resistore viene considerato come un arco orientato che va sempre dal nodo con indice minore (r_start) al nodo con indice maggiore (r_end).
				// arco orientato dal nodo minore a quello maggiore:
                int r_start = std::min(r_u, r_v);
                int r_end = std::max(r_u, r_v);

                for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                    int n_curr = loop_nodes[k];
                    int n_next = loop_nodes[k + 1];

                    if (n_curr == r_start && n_next == r_end) {
                        B(i, j) = 1.0;   // il verso di percorrenza della maglia e l'orientamento del resistore coincidono, allora scriviamo un 1 positivo nella matrice B alla riga i del resistore e alla colonna j della maglia.
                    } else if (n_curr == r_end && n_next == r_start) {
                        B(i, j) = -1.0;    // verso opposto rispetto all'orientamento dell'arco
                    }  
                }
            }
        }


        // costruzione della matrice A del sistema lineare(B'RB):
        Eigen::MatrixXd A = B.transpose() * R * B;

        // risolviamo tramite il metodo del gradiente coniugato implementato in gradiente_coniugato.hpp.
        // definiamo un vettore iniziale nullo (x0) della stessa dimensione di v:
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(num_loops);
        
        // definiamo tolleranza e iterazioni massime:
        double toll = 1.0e-10;
        int max_iter = 100;
        
        // chiamiamo la funzione:
        Eigen::VectorXd x = gradiente_coniugato(A, v, x0, toll, max_iter);

        // vettore delle tensioni reali sui resistori:
        Eigen::VectorXd V_R = R * B * x;
		

        // output formattato dei risultati delle tensioni sui singoli elementi:
        std::cout << "Risultati delle tensioni sui resistori tramite DFS:\n";
        for (size_t i = 0; i < num_resistors; ++i) {
            std::cout << resistors[i].name << ": V = " << V_R(i) << " Volts\n";
        }
    }
};