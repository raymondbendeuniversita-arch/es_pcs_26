#pragma once
#include <string>

enum class ComponentType { RESISTOR, VOLTAGE_SOURCE }; // tipo di dato personalizzato e sicuro per vincolare il compilatore ad accettare solo RESISTOR o VOLTAGE_SOURCE, evitando errori di inserimento.

struct Component {
    std::string name;
    ComponentType type;
    double value; // Ohm per resistori, Volt per generatori
    int node_a;   // primo nodo specificato (terminale positivo per i generatori)
    int node_b;   // secondo nodo specificato (terminale negativo per i generatori)
};