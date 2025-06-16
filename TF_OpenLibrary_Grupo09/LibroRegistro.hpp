#pragma once
#include "LibroArbol.hpp"
#include "Autentificador.hpp"
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

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
		string titulo, autor, genero;
		int stock;

		backgroundColor("#f05252");
		textColor("#000000");
		posicion(63, 11); cout << "|.......... AGREGANDO NUEVO LIBRO ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(47, 13); cout << "Ingrese el titulo del libro: ";
		getline(cin >> ws, titulo);

		posicion(47, 15); cout << "Ingrese el autor del libro: ";
		getline(cin, autor);

		posicion(47, 17); cout << "Ingrese el genero del libro: ";
		getline(cin, genero);

		posicion(47, 19); cout << "Ingrese el stock del libro: ";
		cin >> stock; cin.ignore();

		Libro nuevoLibro(titulo, autor, genero, stock);

		if (arbolLibros.insertarLibro(nuevoLibro)) {

			ocultarCursor();
			textColor("#ffffff");
			posicion(47, 21); cout << "ID del generada para el libro: " << nuevoLibro.getId();
			textColor("#07e092");
			posicion(63, 23); cout << "Libro registrado exitosamente!";

			arbolLibros.guardarEnArchivo("libros.txt");
			Sleep(numRandom() * 600);
		}
		else {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(63, 22); cout << "Error al registrar el libro, intente de nuevo.";
			Sleep(numRandom() * 600);
		}
	}

	void mostarLibros() {
		vector<Libro> libros;
		arbolLibros.enOrdenVector(libros);
		if (libros.empty()) {
			textColor("#fa6f09");
			posicion(63, 22); cout << "No hay libros registrados.";
			Sleep(numRandom() * 600);
			return;
		}
		int index = 0; 
		int total = (int)libros.size();
		int tecla; 

		do {
			ocultarCursor();
			Libro& libro = libros[index];
			backgroundColor("#f05252");
			textColor("#000000");
			posicion(63, 11); cout << "|.......... LISTA DE LIBROS DISPONIBLES ..........|";
			resetColor();

			textColor("#ffffff");
			posicion(47, 13); cout << "ID: " << libro.getId();
			posicion(47, 15); cout << "Titulo: " << libro.getTitulo();
			posicion(47, 17); cout << "Autor: " << libro.getAutor();
			posicion(47, 19); cout << "Genero: " << libro.getGenero();
			posicion(47, 21); cout << "Stock: " << libro.getStock();
			
			posicion(47, 23); cout << "[1] Anterior   [2] Siguiente   [3] Salir";

			tecla = _getch() - '0'; // Convertir a entero
			if (tecla == 1 && index > 0) index--;
			else if (tecla == 2 && index < total - 1) index++;
			else if (tecla == 3) break; // Salir
			else {
				textColor("#fa6f09");
				posicion(63, 25); cout << "Opcion invalida, intente de nuevo.";
				Sleep(numRandom() * 600);
			}
		} while (tecla != 3);

	}

	void buscarLibro() {
		string id; 
		posicion(63, 11); cout << "|.......... BUSCAR LIBRO ..........|";
		textColor("#ffffff");
		posicion(47, 13); cout << "Ingrese el ID completo del libro a buscar: ";
		getline(cin >> ws, id);

		Libro* encontrado = arbolLibros.buscarPorId(id);

		if (!encontrado) {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(63, 15); cout << "Libro no encontrado.";
			Sleep(numRandom() * 400);
			return;
		}
		else {
			ocultarCursor();
			resetColor();
			textColor("#ffffff");
			posicion(47, 13); cout << "ID: " << encontrado->getId();
			posicion(47, 15); cout << "Titulo: " << encontrado->getTitulo();
			posicion(47, 17); cout << "Autor: " << encontrado->getAutor();
			posicion(47, 19); cout << "Genero: " << encontrado->getGenero();
			posicion(47, 21); cout << "Stock: " << encontrado->getStock();
		}
		_getch();
	}

};