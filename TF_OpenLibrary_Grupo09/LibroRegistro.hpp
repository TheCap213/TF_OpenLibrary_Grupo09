#pragma once
#include "LibroAVL.hpp"
#include "Colores.hpp"
#include <ctime>

using namespace std;

template <typename T>
class LibroRegistro {
private:
	LibroAVL<Libro> arbolLibros; 

public:
	LibroRegistro()
		: arbolLibros(
			[](Libro a, Libro b) {
				if (a.getId() == b.getId()) return 0;
				return a.getId() < b.getId() ? -1 : 1;
			},
			[](Libro libro) { cout << libro.toString() << endl; }
		) {
	}

	~LibroRegistro() {}

	LibroAVL<Libro>& getArbol() { return arbolLibros; }

	//DATA SET
	void generarLibros(int cantidad = 500) {

		Libro::idCounter = 0; 

		//TENEMOS 2 LAMBAS AQUI XDXDXDXDXDXDXDXDXDXDXDXDXD
		arbolLibros = LibroAVL<Libro>(
			[](Libro a, Libro b) {
				if (a.getId() == b.getId()) return 0;
				return a.getId() < b.getId() ? -1 : 1;
			},
			[](Libro libro) { cout << libro.toString() << endl; }
		);

		string titulos[] = {
		  "Hobbit", "Quijote", "Aztecas", "Lovecraft", "Orwell",
		  "Inferno", "Atlantis", "Odisea", "Utopias", "Fausto",
		  "Miseros", "Prometeo", "Candide", "Emma", "Madame",
		  "Zorro", "Cumbres", "Persuade", "Siddharta", "Demian",
		  "Crimen", "Bartleby", "Hamlet", "Macbeth", "Lear",
		  "Galileo", "Newton", "Tesla", "Darwin", "Huxley"
		};

		string autores[] = {
		  "Cervantes", "Orwell", "Lovecraft", "Allende", "Garcia",
		  "Hemingway", "Kafka", "Faulkner", "Camus", "Proust",
		  "Dumas", "Flaubert", "Voltaire", "Austen", "Zola",
		  "Poe", "Byron", "Shelley", "Milton", "Joyce",
		  "Homer", "Ovidio", "Platon", "Aristot", "Newton",
		  "Tesla", "Darwin", "Galileo", "Huxley", "Hesse"
		};

		string generos[] = {
		  "Ficcion", "Drama", "Clasico", "Aventura",
		  "Misterio", "Ensayo", "Poesia", "Fabulas",
		  "Leyendas", "Mitologia"
		};

		srand(time(nullptr));

		for (int i = 0; i < cantidad; ++i) {
			string titulo = titulos[rand() % 30];
			string autor = autores[rand() % 30];
			string genero = generos[rand() % 10];
			int stock = rand() % 50 + 1;

			Libro libro(titulo, autor, genero, stock);
			arbolLibros.insertarLibro(libro);
		}

		ocultarCursor();
		textColor("#07e092");
		posicion(50, 15); cout << cantidad << " libros generados correctamente!";
		resetColor();
		Sleep(1000);
	}

	void mostrarLibros() {
		vector<Libro> libros;
		arbolLibros.enOrdenVector(libros);
		if (libros.empty()) {
			textColor("#fa6f09");
			posicion(63, 22); cout << "No hay libros registrados.";
			Sleep(numRandom() * 600);
			return;
		}

		const int porPagina = 20;
		int pagina = 0; 
		int total = libros.size();
		int tecla; 

		do {
			ocultarCursor();
			
			//Limpia area
			for (int y = 13; y <= 35; ++y) {
				posicion(47, y);
				cout << string(79, ' ');
			}

			backgroundColor("#f05252");
			textColor("#000000");
			posicion(63, 11); cout << "|.......... LISTA DE LIBROS DISPONIBLES ..........|";
			resetColor();

			int start = pagina * porPagina;
			int end = min(start + porPagina, total);

			int y = 13;
			for (int i = start; i < end; ++i) {
				posicion(47, y++);
				cout << libros[i].toString();
			}

			posicion(47, y + 1); cout << "[A] Anterior | [D] Siguiente | [S] Salir";

			tecla = _getch();

			if (tecla == 'A' || tecla == 'a') {
				if (pagina > 0) pagina--;
			}
			else if (tecla == 'D' || tecla == 'd') {
				if (end < total) pagina++;
			}
			else if (tecla == 'S' || tecla == 's') {
				break;
			}
		} while (true);

	}

	void buscarLibro() {
		string id; 
		backgroundColor("#ffd795");
		textColor("#000000");
		posicion(63, 11); cout << "|.......... BUSCAR LIBRO ..........|";
		resetColor();
		textColor("#ffffff");
		posicion(47, 13); cout << "Ingrese el ID completo del libro. Ejem (LB-0001)";
		posicion(47, 15); cout << "Ingresar ID: ";
		getline(cin >> ws, id);

		Libro* encontrado = arbolLibros.buscarPorId(id);

		if (!encontrado) {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(63, 17); cout << "Libro no encontrado.";
			Sleep(numRandom() * 400);
			return;
		}
		else {
			ocultarCursor();
			textColor("#d0ff3f");
			posicion(47, 17); cout << "El libro que estas buescando es el siguiente: ";
			textColor("#ffffff");
			posicion(47, 19); cout << encontrado->toString();
			_getch();
		}
	}

};


