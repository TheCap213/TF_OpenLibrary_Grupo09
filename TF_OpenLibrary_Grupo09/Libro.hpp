#pragma once 
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Libro {
private:
	string id;
	string titulo;
	string autor;
	string genero;
	int stock; 

public:

	static int idCounter;

	Libro() : id(""), titulo(""), autor(""), genero(""), stock(0) {}

	Libro(string titulo, string autor, string genero, int stock) {
		stringstream ss;
		ss << "LB-" << setw(4) << setfill('0') << ++idCounter;
		this->id = ss.str();
		this->titulo = titulo;
		this->autor = autor;
		this->genero = genero;
		this->stock = stock;
	}
	
	string toString() const {
		stringstream ss;
		ss << left
			<< setw(8) << id
			<< "| Titulo: " << setw(10) << titulo
			<< "| Autor: " << setw(10) << autor
			<< "| Genero: " << setw(10) << genero
			<< "| Stock: " << setw(3) << stock;
		return ss.str();
	}

	string getId() const { return id; }
	string getTitulo() const { return titulo; }
	string getAutor() const { return autor; }
	string getGenero() const { return genero; }
	int getStock() const { return stock; }

};

