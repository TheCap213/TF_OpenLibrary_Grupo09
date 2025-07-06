#pragma once
#include "Libro.hpp"
#include <iostream>
#include <vector>
using namespace std; 

#define MAX 500 

class LibroHashTable {
private:
    Libro tabla[MAX];
    vector<Libro> colisiones;  // Cambiar de arreglo fijo a vector dinámico
    bool ocupado[MAX] = { false };

    int funcionHash(string clave) {
        int suma = 0;
        for (char c : clave) suma += c * 3 + 7;
        return suma % MAX;
    }

public:
    void gestionarHashTable(vector<Libro>& libros) {
        colisiones.clear();
        fill(begin(ocupado), end(ocupado), false);

        for (Libro& libro : libros) {
            int pos = funcionHash(libro.getId());
            if (!ocupado[pos]) {
                tabla[pos] = libro;
                ocupado[pos] = true;
            }
            else {
                colisiones.push_back(libro);
            }
        }

        mostrarColisiones();
    }

    void mostrarColisiones() {
        if (colisiones.empty()) {
            posicion(63, 22); cout << "No hay colisiones!";
            Sleep(600);
            return;
        }

        const int porPagina = 20;
        int pagina = 0;
        int total = colisiones.size();
        char tecla;

        do {
            ocultarCursor();

            //Limpia area
            for (int y = 13; y <= 35; ++y) {
                posicion(47, y);
                cout << string(79, ' ');
            }

            backgroundColor("#2cf19a");
            textColor("#000000");
            posicion(63, 11); cout << "|.......... COLISIONES EN HASHTABLE ..........|";
            resetColor();

            int start = pagina * porPagina;
            int end = min(start + porPagina, total);

            int y = 13;
            for (int i = start; i < end; ++i) {
                posicion(47, y++);
                cout << colisiones[i].toString();
            }

            posicion(47, y + 1); cout << "[A] Anterior | [D] Siguiente | [S] Salir";

            tecla = _getch();

            if (tecla == 'A' || tecla == 'a') {
                if (pagina > 0) pagina--;
            }
            else if (tecla == 'D' || tecla == 'd') {
                if (end < total) pagina++;
            }
            else if (tecla == 'S' || tecla == 's') {
                break;
            }
        } while (true);
    }
};
