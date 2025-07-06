#pragma once
#include "NodoReserva.hpp"
#include "Reserva.hpp"
#include "Colores.hpp"
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

    void agregarReserva(T reserva) {
        NodoReserva<T>* nuevo = new NodoReserva<T>(reserva);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    void mostrarReservas() {
        NodoReserva<T>* actual = cabeza;
        int y = 13;
        if (!actual) {
            posicion(47, y); cout << "No hay reservas.";
            _getch();
            return;
        }

        backgroundColor("#f05252");
        textColor("#000000");
        posicion(63, 11); cout << "|.......... RESERVAS ..........|";
        resetColor();

        while (actual) {
            posicion(47, y++);
            cout << actual->reserva.toString();
            actual = actual->siguiente;
        }
        _getch();
    }
};
