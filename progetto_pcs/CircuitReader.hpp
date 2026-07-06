#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>



#include "graph.hpp"
#include "CircuitComponents.hpp"


//Definiamo uan struct componente per memorizzare i vari tipi di dati presenti nel file netlist.txt
class CircuitReader {
private:
    unidirected_graph G;  //grafo utilizzando quello delle scorse esrcitazioni
    std::vector<Component> components;  //vettore che memorizza tutti i componenti del gruppo

public:
    CircuitReader() {}  //costruttore di default
    

    bool read_file(const std::string& filename) {
        components.clear();
        G = unidirected_graph();
        std::ifstream file(filename);

        //controllo per verificare la corretta apertura del file
        if (!file.is_open()) {
            std::cout <<"Errore: impossibile aprire il file" << std::endl;
            return false;
        }

        Component comp;
        std::string comp_name;
        double comp_value;
        int n_a, n_b;


        //ciclo while che usa >> per saltare gli spazi e si ferma alla fine del file
        while (file>>comp_name>>comp_value>>n_a>>n_b) {
            
            comp.name = comp_name;
            comp.value = comp_value;
            comp.node_a = n_a;
            comp.node_b = n_b;
            
            //Prende la  prima lettera dal nome per capirne il tipo es: "R1"  "V1". prenderà 'R' oopure 'V'
            if (comp.name[0] == 'R' || comp.name[0] == 'r') {
                comp.type = ComponentType::RESISTOR;
            } else if (comp.name[0] == 'V' || comp.name[0] == 'v') {
                comp.type = ComponentType::VOLTAGE_SOURCE;
            }
            
            components.push_back(comp); //viene salvata la "struct" dentro il vettore componenti
            
            G.add_edges(comp.node_a, comp.node_b); //inserisco i nodi nel grafo G
        }

        file.close();
        return true; //Vero se la lettura è andata a buon fine
    }


    const std::vector<Component>& getComponents() const { 
        return components; 
    }

    const unidirected_graph& getGraph() const { 
        return G; 
    }



};