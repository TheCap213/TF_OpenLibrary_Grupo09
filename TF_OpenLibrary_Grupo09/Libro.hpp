#pragma once
#include <string>

using namespace std;

class Libro {
private:
	int id;
	string titulo;
	string autor;
	string genero;
	int stock; 

public:
	Libro() : id(0), titulo(""), autor(""), genero(""), stock(0) {}
	Libro(int id, string titulo, string autor, string genero, int stock)
		: id(id), titulo(titulo), autor(autor), genero(genero), stock(stock) {
	}
	string serializar() {
		return to_string(id) + "," + titulo + "," + autor + "," + genero + "," + to_string(stock);
	}
	void deserializar(string linea) {
		size_t pos = 0;
		int campo = 0;
		string token;
		while ((pos = linea.find(',')) != string::npos) {
			token = linea.substr(0, pos);
			if (campo == 0) id = stoi(token);
			else if (campo == 1) titulo = token;
			else if (campo == 2) autor = token;
			else if (campo == 3) genero = token;
			else if (campo == 4) stock = stoi(token);
			linea.erase(0, pos + 1);
			campo++;
		}
	}
	int getId() { return id; }
	string getTitulo() { return titulo; }
	string getAutor() { return autor; }
	string getGenero() { return genero; }
	int getStock() { return stock; }

};