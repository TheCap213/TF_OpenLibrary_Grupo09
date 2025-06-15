#pragma once
#include "LibroArbol.hpp"
#include "Autentificador.hpp"
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
class LibroRegistro {
private:
	LibroArbol<Libro> arbolLibros;

public:
    LibroRegistro()
        : arbolLibros(
            // Comparador por ID
            [](Libro a, Libro b) { return a.getId().compare(b.getId()); },
            // Procesar: imprimir serialized
            [](Libro libro) { cout << libro.serializar() << endl; }
        )
    {
        arbolLibros.abrirDesdeArchivo("libros.txt");
    }

    // Guarda al destruir
    ~LibroRegistro() {
        arbolLibros.guardarEnArchivo("libros.txt");
    }

	void registrarLibro() {
		string id, titulo, autor, genero;
		int stock;
		
		posicion(47, 11); cout << "Ingrese el ID del libro: ";
		cin >> id; cin.ignore();

		posicion(47, 13); cout << "Ingrese el titulo del libro: ";
		getline(cin, titulo);

		posicion(47, 15); cout << "Ingrese el autor del libro: ";
		getline(cin, autor);

		posicion(47, 17); cout << "Ingrese el genero del libro: ";
		getline(cin, genero);

		posicion(47, 19); cout << "Ingrese el stock del libro: ";
		cin >> stock; cin.ignore();

		Libro nuevoLibro(titulo, autor, genero, stock);
		if (arbolLibros.insertarLibro(nuevoLibro)) {

			arbolLibros.guardarEnArchivo("libros.txt");
			ocultarCursor();
			textColor("#07e092");
			posicion(47, 21); cout << "Libro registrado exitosamente!";
			Sleep(numRandom() * 600);
		}
		else {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(47, 21); cout << "Error al registrar el libro, intente de nuevo.";
			Sleep(numRandom() * 600);
		}


	}

};