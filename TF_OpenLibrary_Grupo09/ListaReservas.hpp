#pragma once
#include "NodoReserva.hpp"
#include "Reserva.hpp"
#include "FigurasMenu.hpp"
#include <iostream>
#include <conio.h>
using namespace std;

template <typename T>
class ListaReservas {
private:
    NodoReserva<T>* cabeza;

public:
    ListaReservas() : cabeza(nullptr) {}

    NodoReserva<T>* getCabeza() {
        return cabeza;
    }

    void agregarReserva(T reserva) {
        NodoReserva<T>* nuevo = new NodoReserva<T>(reserva);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void mostrarReservas() {
        NodoReserva<T>* actual = cabeza;
        vector<T> reservas;

        while (actual) {
            reservas.push_back(actual->reserva);
            actual = actual->siguiente;
        }

        if (reservas.empty()) {
            ocultarCursor();
            backgroundColor("#9665ff");
            textColor("#000000");
            posicion(63, 11); cout << "|.......... LISTA DE RESERVAS ..........|";
            resetColor();
            textColor("#ffffff");
            posicion(47, 13); cout << "No hay reservas.";
            resetColor();
            Sleep(numRandom() * 600);
            return;
        }

        const int porPagina = 20;
        int pagina = 0;
        int total = reservas.size();
        char tecla;

        do {
            ocultarCursor();

            //Limpia area
            for (int y = 13; y <= 35; ++y) {
                posicion(47, y);
                cout << string(79, ' ');
            }

            backgroundColor("#9665ff");
            textColor("#000000");
            posicion(63, 11); cout << "|.......... LISTA DE RESERVAS ..........|";
            resetColor();

            int start = pagina * porPagina;
            int end = min(start + porPagina, total);

            int y = 13;
            for (int i = start; i < end; ++i) {
                posicion(47, y++);
                cout << reservas[i].toString();
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
