#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <limits>
#include <Eigen/Dense>

#include "graph.hpp"
#include "methods.hpp"
#include "graph_visit.hpp"
#include "gradiente_coniugato.hpp"
#include "CircuitComponents.hpp"

class CircuitSolver {
private:
    // inizializzo vettori di generatori e resistori sfruttando la classe Component definita in CircuitComponent.hpp:
    std::vector<Component> resistors;
    std::vector<Component> voltages;
    unidirected_graph G;
    
	// metodo clean_string per ripulire la stringa da eventruali spazi vuoti o malformattazioni qaundo leggerò la netlist:
    std::string clean_string(const std::string& str) {
        std::string cleaned = "";
        for (char c : str) {
            if (c != '"' && c != '\r' && c != '\n' && c != ' ' && c != '\t') {
                cleaned += c;
            }
        }
        return cleaned;
    }


    // BFS generica sul grafo per trovare il cammino minimo non pesato:
    bool path_in_tree(const unidirected_graph& graph, int start, int end, std::vector<int>& path) {
        std::map<int, int> parent;
        std::set<int> visited;
        fifo<int> q;
        
        q.put(start);
        visited.insert(start);
        parent[start] = -1;   // tra parentesi il primo elemento della coppia in parent, dopo l'uguale il secondo elemento
        
        bool found = false;
        while (!q.empty()) {
            int u = q.get();
            if (u == end) {
                found = true;
                break;
            }
            for (int v : graph.neighbours(u)) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    q.put(v);
                }
            }
        }
        
        if (!found) return false;
        
		// ora bisogna ricostruire il cammine a partire dal nodo di arrivo (end) e risalendo fino al nodo di partenùza (start):
        int current = end;
        while (current != -1) {
            path.push_back(current);  // aggiungo il nodo corrente al vettore path
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());  // abbiamo risalito la mappa dall'inizio alla fine quindi ora va iknvertito il percorso
        return true;
    }


    // funzione helper per trovare la resistenza tra due nodi adiacenti (peso dell'arco):
    double get_weight(int u, int v) {
        for (const auto& r : resistors) {
            if ((r.node_a == u && r.node_b == v) || (r.node_a == v && r.node_b == u)) {
                return r.value;
            }
        }
        return 1.0e-3;  // valore minimo per archi senza resistori 
    }


    // algoritmo di Dijkstra pesato sulle resistenze (mi serve per isolare i cicli minimi per l'algoritmo di De Pina).
	// identico all'esercitazione solo che questa volta prendiamo i pesi degli archi con la funzione get_weight:
    bool dijkstra(const unidirected_graph& graph, int start, int end, std::vector<int>& path) {
        std::map<int, double> dist;
        std::map<int, int> parent;
        
        using Pair = std::pair<double, int>;   // per semplicità indico Pair tutte le volte che uso quell'std::pair (primo elemento = distanza del nodo, secondo elemento = numero del nodo)
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;   // prende 3 parametri: il Pair definito sopra, un vettore (contenitore) usato per memorizzare i dati e 
		                                                                       // std::greater che ordina gli elementi in senso crescente, così che la pq può estrarre prima quello con distanza minore

        for (int node : graph.all_nodes()) {
            dist[node] = std::numeric_limits<double>::infinity();
        }

        dist[start] = 0.0;
        pq.push({0.0, start});   // per come è definita, nella pq si inseriscono coppie {distanza, nodo}
        parent[start] = -1;

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;
            if (u == end) break;

            for (int v : graph.neighbours(u)) {
                double weight = get_weight(u, v);
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[end] == std::numeric_limits<double>::infinity()) return false;


        // come prima, una volta trovato il percorso si inseriscono i nodi nel vettore path dalla fine all'inizio e poi si rigira:
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        std::reverse(path.begin(), path.end());
        return true;
    }

    // confronto sicuro per archi non orientati:
    bool same_edge(const unidirected_edge& e1, int u, int v) {
        return (e1.from() == u && e1.to() == v) || (e1.from() == v && e1.to() == u);
    }

public:
    CircuitSolver() = default;

    // legge il file riga per riga come nella prima esercitazione:
    bool read_netlist(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Errore: impossibile aprire il file netlist " << filename << "\n";
            return false;
        }

        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;   // salta direttamente le linee vuote

            std::istringstream ss(line);
            std::string name;
            double value;
            int node_a, node_b;

            if (!(ss >> name >> value >> node_a >> node_b)) continue;

            name = clean_string(name);
            if (name.empty()) continue;

            Component comp;
            comp.name   = name;
            comp.value  = value;
            comp.node_a = node_a;
            comp.node_b = node_b;   
            
			// classificazione dei componenti sulla base della prima lettera del nome (risolutore di scope per i tipi della enum class):
            if (comp.name[0] == 'R' || comp.name[0] == 'r') {
                comp.type = ComponentType::RESISTOR;
                resistors.push_back(comp);
            } else if (comp.name[0] == 'V' || comp.name[0] == 'v') {
                comp.type = ComponentType::VOLTAGE_SOURCE;
                voltages.push_back(comp);
            }
            
            G.add_edges(comp.node_a, comp.node_b);
        }
        
        std::sort(resistors.begin(), resistors.end(), [](const Component& a, const Component& b) {  // il terzo parfamentro passato a sort è il criterio di confronto
            return a.name < b.name;
        });
        
        return true;
    }



    // PRIMA ALTERNATIVA: ALGORITMO DFS
    void solve_circuit_dfs() {
        if (resistors.empty()) {
            std::cout << "Nessun resistore nel circuito.\n";
            return;
        }

        int source_node = *G.all_nodes().begin();
        lifo<int> s;
        unidirected_graph T = graph_visit(G, source_node, s);

        unidirected_graph C = G - T;
        auto cotree_edges = C.all_edges();

        size_t num_resistors = resistors.size();
        size_t num_loops = cotree_edges.size();
        
		std::cout << "\n";
        std::cout << "------ ESECUZIONE ALGORITMO DFS ------\n";
		std::cout << "\n";
        std::cout << "Numero di resistori (m): " << num_resistors << "\n";
        std::cout << "Numero di maglie individuate (n): " << num_loops << "\n";

        Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistors, num_loops);  
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistors, num_resistors);
        Eigen::VectorXd v = Eigen::VectorXd::Zero(num_loops);

        // matrice diagonale con i valori delle resistenze:
        for (size_t i = 0; i < num_resistors; ++i) {
            R(i, i) = resistors[i].value;
        }


        // calcolo delle maglie fondamentali:
        for (size_t j = 0; j < num_loops; ++j) {
            unidirected_edge loop_edge = cotree_edges[j];
            int u = loop_edge.from();
            int v_node = loop_edge.to();

            std::vector<int> tree_path;
            path_in_tree(T, v_node, u, tree_path);

            std::vector<int> loop_nodes;
            loop_nodes.push_back(u);
            for (int node : tree_path) {
                loop_nodes.push_back(node);   // ogni arco del coalbero inserito all'interno dell'albero isola una e una sola maglia fondamentale
            }


            // vettore v dei termini noti (se il verso di percorrenza coincide con l'orinetgamento si somma altrimenti si sottrae):
            for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                int n_curr = loop_nodes[k];
                int n_next = loop_nodes[k + 1];

                for (const auto& volt : voltages) {
                    if ((volt.node_a == n_curr && volt.node_b == n_next) ||
                        (volt.node_a == n_next && volt.node_b == n_curr)) {
                        if (n_curr == volt.node_b && n_next == volt.node_a) {
                            v(j) += volt.value;
                        } else if (n_curr == volt.node_a && n_next == volt.node_b) {
                            v(j) -= volt.value;
                        }
                    }
                }
            }
            
			 // matrice di incidenza B (entrata +1 se il verso di percorrenza della maglia coincide con l'orientamento del componente):
            for (size_t i = 0; i < num_resistors; ++i) {
                int r_u = resistors[i].node_a;
                int r_v = resistors[i].node_b;
                int r_start = std::min(r_u, r_v);
                int r_end = std::max(r_u, r_v);

                for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                    int n_curr = loop_nodes[k];
                    int n_next = loop_nodes[k + 1];

                    if (n_curr == r_start && n_next == r_end) {
                        B(i, j) += 1.0;
                    } else if (n_curr == r_end && n_next == r_start) {
                        B(i, j) -= 1.0;
                    }  
                }
            }
        }

        Eigen::MatrixXd A = B.transpose() * R * B;
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(num_loops);
        double toll = 1.0e-10;
        int max_iter = 100;
        
        Eigen::VectorXd x = gradiente_coniugato(A, v, x0, toll, max_iter);
        Eigen::VectorXd V_R = R * B * x;

        std::cout << "Risultati delle tensioni sui resistori tramite DFS:\n";
        for (size_t i = 0; i < num_resistors; ++i) {
            std::cout << resistors[i].name << ": V = " << V_R(i) << " Volts\n";
        }
    }



    // SECONDA ALTERNATIVA: ALGORITMO DI DE PINA
    void solve_circuit_depina() {
        if (resistors.empty()) {
            std::cout << "Nessun resistore nel circuito.\n";
            return;
        }

        // albero di copertura iniziale T come per DFS:
        int source_node = *G.all_nodes().begin();
        fifo<int> f;
        unidirected_graph T = graph_visit(G, source_node, f);

        // coalbero C come per DFS:
        unidirected_graph C = G - T;
        auto cotree_edges = C.all_edges();

        size_t num_resistors = resistors.size();
        size_t num_loops = cotree_edges.size();
        
		std::cout << "\n";
        std::cout << "------ ESECUZIONE ALGORITMO DE PINA ------\n";
		std::cout << "\n";
        std::cout << "Numero di resistori (m): " << num_resistors << "\n";
        std::cout << "Numero di maglie individuate (n): " << num_loops << "\n";

        // stesse inizializzazioni e stessa matrice diagonale delle resistenze R:
        Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistors, num_loops);
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistors, num_resistors);
        Eigen::VectorXd v = Eigen::VectorXd::Zero(num_loops);

        for (size_t i = 0; i < num_resistors; ++i) {
            R(i, i) = resistors[i].value;
        }


        // vettori di supporto S_i su F_2 (base canonica). Li inizializzo con una struttura vettori di vettori (cioè una matrice bidimensionale)
		// in cui ogni riga corrisponde ad un arco del coalbero:
        std::vector<std::vector<int>> support_vectors(num_loops, std::vector<int>(num_loops, 0));  // due parametri: dimensione e valore iniziale
        for (size_t i = 0; i < num_loops; ++i) {
            support_vectors[i][i] = 1; 
        }

        std::vector<std::vector<int>> final_loops(num_loops);

        // loop principale di De Pina:
        for (size_t i = 0; i < num_loops; ++i) {
            
            // grafo ausiliario formato da T + archi del coalbero abilitati da S_i (quelli che valgono 1) per assicurare ortogonalità:
            unidirected_graph aux_graph = T;
            for (size_t k = 0; k < num_loops; ++k) {
                if (support_vectors[i][k] == 1) {
                    aux_graph.add_edges(cotree_edges[k].from(), cotree_edges[k].to());
                }
            }

            int u = cotree_edges[i].from();
            int v_node = cotree_edges[i].to();

            // grafo senza l'arco e_i:
            unidirected_graph aux_clean;
            for (const auto& edge : aux_graph.all_edges()) {
                if (!same_edge(edge, u, v_node)) {
                    aux_clean.add_edges(edge.from(), edge.to());
                }
            }

            // Dijkstra pesato per trovare il cammino minimo tra v_node e u:
            std::vector<int> path;
            if (!dijkstra(aux_clean, v_node, u, path)) {
                // (su BFS se Dijkstra fallisce in casi limite)
                path_in_tree(aux_clean, v_node, u, path);
            }

            // ricostruzione maglia chiusa:
            std::vector<int> loop_nodes;
            loop_nodes.push_back(u);
            for (int node : path) {
                loop_nodes.push_back(node);
            }
            final_loops[i] = loop_nodes;

            // aggiornamento ortogonale su F_2 dei vettori S_j (j > i):
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
                           dot_product ^= 1;  // somma mod 2
                        }
                    }
                }

                if (dot_product == 1) {
                    for (size_t k = 0; k < num_loops; ++k) {
                        support_vectors[j][k] ^= support_vectors[i][k];
                    }
                }
            }
        }


        // costruzione matrice d'Incidenza B e vettore tensioni v come prima con DFS:
        for (size_t j = 0; j < num_loops; ++j) {
            const auto& loop_nodes = final_loops[j];

            for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                int n_curr = loop_nodes[k];
                int n_next = loop_nodes[k + 1];

                for (const auto& volt : voltages) {
                    if ((volt.node_a == n_curr && volt.node_b == n_next) ||
                        (volt.node_a == n_next && volt.node_b == n_curr)) {
                        
                        if (n_curr == volt.node_b && n_next == volt.node_a) {
                            v(j) += volt.value;
                        } else if (n_curr == volt.node_a && n_next == volt.node_b) {
                            v(j) -= volt.value;
                        }
                    }
                }
            }

            for (size_t i = 0; i < num_resistors; ++i) {
                int r_u = resistors[i].node_a;
                int r_v = resistors[i].node_b;
                
                int r_start = std::min(r_u, r_v);
                int r_end = std::max(r_u, r_v);

                for (size_t k = 0; k < loop_nodes.size() - 1; ++k) {
                    int n_curr = loop_nodes[k];
                    int n_next = loop_nodes[k + 1];

                    if (n_curr == r_start && n_next == r_end) {
                        B(i, j) += 1.0;
                    } else if (n_curr == r_end && n_next == r_start) {
                        B(i, j) -= 1.0;
                    }  
                }
            }
        }

        
        Eigen::MatrixXd A = B.transpose() * R * B;
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(num_loops);
        double toll = 1.0e-10;
        int max_iter = 100;
        
        Eigen::VectorXd x = gradiente_coniugato(A, v, x0, toll, max_iter);
        Eigen::VectorXd V_R = R * B * x;

        std::cout << "Risultati delle tensioni sui resistori tramite De Pina:\n";
        for (size_t i = 0; i < num_resistors; ++i) {
            std::cout << resistors[i].name << ": V = " << V_R(i) << " Volts\n";
        }
    }
};