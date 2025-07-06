#pragma once
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class DVD {
private:
    string id;
    string titulo;
    string director;
    string genero;
    int stock;

public:
    static int idCounter;

    DVD() : id(""), titulo(""), director(""), genero(""), stock(0) {}

    DVD(string titulo, string director, string genero, int stock) {
        stringstream ss;
        ss << "DV-" << setw(4) << setfill('0') << ++idCounter;
        this->id = ss.str();
        this->titulo = titulo;
        this->director = director;
        this->genero = genero;
        this->stock = stock;
    }

    string toString() const {
        stringstream ss;
        ss << left
            << setw(8) << id
            << "| Titulo: " << setw(9) << titulo
            << "| Director: " << setw(9) << director
            << "| Genero: " << setw(9) << genero
            << "| Stock: " << setw(3) << stock;
        return ss.str();
    }

    string getId() const { return id; }
    string getTitulo() const { return titulo; }
    string getDirector() const { return director; }
    string getGenero() const { return genero; }
    int getStock() const { return stock; }
    void setStock(int s) { stock = s; }

};
