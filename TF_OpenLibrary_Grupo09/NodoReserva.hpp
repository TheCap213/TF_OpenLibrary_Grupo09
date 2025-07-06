#pragma once

template <typename T>
class NodoReserva {
public:
    T reserva;
    NodoReserva* siguiente;

    NodoReserva(T reserva) : reserva(reserva), siguiente(nullptr) {}
};
