#include "pch.h"
#include <iostream>
#include <string>
#include <queue>
using namespace System;
using namespace std;

const int max_nodos = 9;

class Grafo {
public:
    int nodos;
    int aristas[max_nodos][max_nodos];

    Grafo(int nodos) {
        this->nodos = nodos;
        for (int i = 0; i < nodos; i++) {
            for (int j = 0; j < nodos; j++) {
                aristas[i][j] = 0; // Inicializa la matriz de adyacencia con 0 en todas las entradas
            }
        }
    }

    void addEdge(int u, int v) {
        aristas[u][v] = 1;
        aristas[v][u] = 1;
    }

    void BFS(int nodo_inicio, int distancias[], int padres[]) {
        for (int i = 0; i < nodos; i++) {
            distancias[i] = -1; // Inicializa las distancias como -1 (no visitado)
            padres[i] = -1; // Inicializa los padres como -1 (no asignado)
        }
        queue<int> cola;
        cola.push(nodo_inicio);
        distancias[nodo_inicio] = 0;

        while (!cola.empty()) {
            int nodo_actual = cola.front();
            cola.pop();

            for (int i = 0; i < nodos; i++) {
                if (aristas[nodo_actual][i] && distancias[i] == -1) {
                    cola.push(i);
                    distancias[i] = distancias[nodo_actual] + 1;
                    padres[i] = nodo_actual;
                }
            }
        }
    }

    void imprimirCamino(int nodo_a, int nodo_b, string ciudades[]) {
        int distancias[max_nodos];
        int padres[max_nodos];
        BFS(nodo_a, distancias, padres);
        int nodo_actual = nodo_b;

        cout << "Camino entre " << ciudades[nodo_a] << " y " << ciudades[nodo_b] << ": " << endl;
        while (nodo_actual != -1) {
            cout << ciudades[nodo_actual];
            if (nodo_actual != nodo_a) {
                cout << " <- ";
            }
            nodo_actual = padres[nodo_actual];
        }
        cout << endl;
    }

    bool DFS(int nodo_actual, int nodo_destino, int aristas_actuales, int max_aristas, int padres[], bool visitados[]) {
        visitados[nodo_actual] = true;
        bool encontrado = false;

        if (nodo_actual == nodo_destino && aristas_actuales == max_aristas) {
            encontrado = true;
        }
        else if (aristas_actuales < max_aristas) {
            for (int i = 0; i < nodos; i++) {
                if (aristas[nodo_actual][i] && !visitados[i]) {
                    padres[i] = nodo_actual;
                    encontrado = DFS(i, nodo_destino, aristas_actuales + 1, max_aristas, padres, visitados);
                    if (encontrado) {
                        break;
                    }
                }
            }
        }

        visitados[nodo_actual] = false;
        return encontrado;
    }

    void imprimirCaminoDFS(int nodo_a, int nodo_b, string ciudades[], int max_aristas) {
        int padres[max_nodos];
        bool visitados[max_nodos];
        for (int i = 0; i < nodos; i++) {
            padres[i] = -1;
            visitados[i] = false;
        }
        bool encontrado = DFS(nodo_a, nodo_b, 0, max_aristas, padres, visitados);

        if (encontrado) {
            cout << "Camino con " << max_aristas << " aristas entre " << ciudades[nodo_a] << " y " << ciudades[nodo_b] << ": " << endl;
            int nodo_actual = nodo_b;
            while (nodo_actual != -1) {
                cout << ciudades[nodo_actual];
                if (nodo_actual != nodo_a) {
                    cout << " <- ";
                }
                nodo_actual = padres[nodo_actual];
            }
            cout << endl;
        }
        else {
            cout << "No se encontró un camino con " << max_aristas << " aristas entre " << ciudades[nodo_a] << " y " << ciudades[nodo_b] << endl;
        }
    }   
};

int main() {    
    int nodos = 9;
    string ciudades[9] = { "LIMA","PIURA","CHICLAYO","TRUJILLO","IQUITOS","CUZCO","PUERTO_MALDONADO","JULIACA","AREQUIPA" };

    Grafo* g = new Grafo(nodos);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(0, 3);
    g->addEdge(0, 4);
    g->addEdge(0, 5);
    g->addEdge(0, 7);
    g->addEdge(0, 8);

    g->addEdge(5, 6);
    g->addEdge(8, 5);

    int nodo_a = 3; 
    int nodo_b = 6; 

    //g->imprimirCamino(nodo_a, nodo_b, ciudades);

    g->imprimirCaminoDFS(nodo_a, nodo_b, ciudades, 1); // Camino con 1 arista
    g->imprimirCaminoDFS(nodo_a, nodo_b, ciudades, 2); // Camino con 2 aristas
    g->imprimirCaminoDFS(nodo_a, nodo_b, ciudades, 3); // Camino con 3 aristas

    system("pause>0");
    return 0;
}