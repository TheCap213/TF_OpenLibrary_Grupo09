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
	
	string serializar() {
		return id + "," + titulo + "," + autor + "," + genero + "," + to_string(stock);
	}

	void deserializar(string linea) {
		size_t pos = 0;
		int campo = 0;
		string token;
		while ((pos = linea.find(',')) != string::npos) {
			token = linea.substr(0, pos);
			if (campo == 0) id = token;
			else if (campo == 1) titulo = token;
			else if (campo == 2) autor = token;
			else if (campo == 3) genero = token;
			else if (campo == 4) stock = stoi(token);
			linea.erase(0, pos + 1);
			campo++;
		}
	}

	string getId() const { return id; }
	string getTitulo() const { return titulo; }
	string getAutor() const { return autor; }
	string getGenero() const { return genero; }
	int getStock() const { return stock; }

};

int Libro::idCounter = 0; // Inicializar el contador de IDs