#pragma once
#include <string>
using namespace std;

class Reserva {
private:
    string dniUser;
    string idRecurso;
    string titulo;
    string genero;
    int cantidad;
    string tipoRecurso; // LIBRO o DVD

public:
    Reserva(string dniUser, string idRecurso, string titulo, string genero, int cantidad, string tipoRecurso)
        : dniUser(dniUser), idRecurso(idRecurso), titulo(titulo), genero(genero), cantidad(cantidad), tipoRecurso(tipoRecurso) {
    }

    string getDniUser() const { return dniUser; }
    string getIdRecurso() const { return idRecurso; }
    string getTitulo() const { return titulo; }
    string getGenero() const { return genero; }
    int getCantidad() const { return cantidad; }
    string getTipoRecurso() const { return tipoRecurso; }

    string toString() const {
        stringstream ss;
        ss << left
            << "ID: " << setw(2) << idRecurso
            << " | Titulo: " << setw(9) << titulo
            << " | Genero: " << setw(9) << genero
            << " | Cantidad: " << setw(2) << cantidad
            << "| Tipo: " << setw(6) << tipoRecurso;
        return ss.str();
    }
};
