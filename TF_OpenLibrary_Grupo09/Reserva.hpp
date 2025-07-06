#pragma once
#include <string>
using namespace std;

class Reserva {
private:
    string dniUser;
    string idRecurso;
    string tipoRecurso; // LIBRO o DVD
    string fechaReserva;

public:
    Reserva(string dniUser, string idRecurso, string tipoRecurso, string fechaReserva)
        : dniUser(dniUser), idRecurso(idRecurso), tipoRecurso(tipoRecurso), fechaReserva(fechaReserva) {
    }

    string getDniUser() const { return dniUser; }
    string getIdRecurso() const { return idRecurso; }
    string getTipoRecurso() const { return tipoRecurso; }
    string getFecha() const { return fechaReserva; }

    string toString() const {
        return "DNI: " + dniUser + " | " + tipoRecurso + " ID: " + idRecurso + " | Fecha: " + fechaReserva;
    }
};
