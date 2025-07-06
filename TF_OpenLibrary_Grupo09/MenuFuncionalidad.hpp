#pragma once
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include "UserRegistro.hpp"
#include "RegistroDVD.hpp"
#include "LibroRegistro.hpp"
#include "ListaReservas.hpp"
#include "LibroHashTable.hpp"
#include <ctime>
using namespace std;

UserRegistro<Usuario> registro;
LibroRegistro<Libro> registroLibros;
RegistroDVD<DVD> registroDVDs;
ListaReservas<Reserva> listaReservasLibros;
ListaReservas<Reserva> listaReservasDVDs;



void menuUsuario();
void menuAdmin();

void menuPrincipal() {
	system("cls");
	mostrarCursor();
	int opcion; 
	
	do {
		system("title Open Library");
		dibujarBordes("#b3b3b3");
		tituloOpenLibrary(5, 6, "#07e092");
		birrete(20, 15);
		birrete(93, 15);
		libroMenu(31, 26);
		mostrarCursor();

		backgroundColor("#41b68f");
		textColor("#000000");
		posicion(47, 14); cout << "|.......... BIENVENIDO ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(50, 16); cout << "[1] Resgistrar nuevo usuario";
		posicion(50, 18); cout << "[2] Iniciar sesion";
		posicion(50, 20); cout << "[3] Salir";
		posicion(47, 22); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;

		// POR SI UN CHISTOSO SE LE OCURRE INGRESAR UN CARACTER xd
		try {
			opcion = stoi(entrada); //Convierte el texto a int
		}
		catch (...) {
			opcion = -1; // si no es un numero le asigna -1 predeterminadamente
		}
		resetColor();

		switch (opcion) {
		case 1 :
			ocultarCursor();
			textColor("#e8e036");
			posicion(47, 24); cout << "Accediendo al modulo de registro..."; 
			Sleep(numRandom() * 600); 
			registro.registrarUsuario();
			break; 

		case 2:
			ocultarCursor();
			textColor("#62e6e8");
			posicion(47, 24); cout << "Accediendo al modulo de login...";
			Sleep(numRandom() * 600);
			registro.iniciarSesion();
			if (registro.getUserLogueado()) {
				if (registro.getUserLogueado()->getRol() == USER) {
					menuUsuario();
				}
				else {
					menuAdmin();
				}
			}
			break;

		case 3: 
			ocultarCursor();
			textColor("#e12874");
			posicion(47, 24); cout << "Cerrando Sesion...";
			Sleep(numRandom() * 600);
			system("cls");  
			exit(0);
			break;

		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(47, 24); cout << "Eliga una opcion valida.";
			Sleep(numRandom() * 600);
			menuPrincipal();
			break;
		}

	} while (opcion != 3);

}

void menuUsuario() {
	int opcion;
	
	do {
		system("cls");
		mostrarCursor();
		system("title Open Library - User");
		dibujarBordes("#b3b3b3");
		dibujarLineaHorizontal(9, 1, 126, "#b3b3b3");
		dibujarLineaVertical(44, 10, 35, "#b3b3b3");
		tituloOpenLibrary(7, 2, "#07e092");
		backgroundColor("#41b68f");
		textColor("#000000");
		posicion(3, 11); cout << "|........... MENU PRINCIPAL ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(5, 13); cout << "Hola " << registro.getUserLogueado()->getNombre() << ", que desesas hacer hoy?";

		posicion(7, 16); cout << "[1] Ver todos los libros";
		posicion(7, 18); cout << "[2] Buscar libros";
		posicion(7, 20); cout << "[3] Reservar libro";
		posicion(7, 22); cout << "[4] Ver mis reservas de Libros";
		posicion(7, 24); cout << "[5] Ver todos los DVDs";
		posicion(7, 26); cout << "[6] Reservar DVD";
		posicion(7, 28); cout << "[7] Ver mis reservas de DVDs";
		posicion(7, 30); cout << "[8] Cerrar sesión";;
		posicion(5, 32); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;
		try {
			opcion = stoi(entrada);
		}
		catch (...) {
			opcion = -1; 
		}

		switch (opcion) {
		case 1:
			registroLibros.mostrarLibros();
			break;
		case 2:
			registroLibros.buscarLibro();
			break;
		case 8:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 34); cout << "Cerrando sesion...";
			resetColor();
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			system("cls");
			return;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 34); cout << "Opcion invalida, intente de nuevo.";
			resetColor();
			Sleep(numRandom() * 600);
			break;
		}

	} while (true);
}

void menuAdmin() {
	int opcion;
	
	do {
		system("cls");
		mostrarCursor();
		system("title Open Library - Owner");
		dibujarBordes("#ffffff");
		dibujarLineaHorizontal(9, 1, 126, "#ffffff");
		dibujarLineaVertical(44, 10, 35, "#ffffff");
		tituloOpenLibrary(7, 2, "#f05252");
		mostrarCursor();
		backgroundColor("#f05252");
		textColor("#000000");
		posicion(3, 11); cout << "|........ MENU ADMINISTRATIVO ........|";
		resetColor();

		textColor("#ffffff");
		posicion(5, 13); cout << "Hola " << registro.getUserLogueado()->getNombre() << ", que desesas hacer hoy?";

		posicion(7, 15); cout << "[1] Generar Libros (500)";
		posicion(7, 17); cout << "[2] Ver todos los libros";
		posicion(7, 19); cout << "[3] Buscar libro";
		posicion(7, 21); cout << "[4] Gestionar HashTable de Libros";
		posicion(7, 23); cout << "[5] Generar DVDs (500)";
		posicion(7, 25); cout << "[6] Ver todos los DVDs";
		posicion(7, 27); cout << "[7] Buscar DVD";
		posicion(7, 29); cout << "[8] Ver todos los usuarios";
		posicion(7, 31); cout << "[9] Cerrar sesion";
		posicion(5, 33); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;

		try {
			opcion = stoi(entrada);
		}
		catch (...) {
			opcion = -1; // Forzar default
		}

		switch (opcion) {
		case 1: 
			registroLibros.generarLibros(500); //LIMITE DE GENERACION SON 433 en BST
			break;
		case 2:
			registroLibros.mostrarLibros();
			break;
		case 3: 
			registroLibros.buscarLibro();
			break;
		case 4: {
				LibroHashTable hash;
				vector<Libro> libros;
				registroLibros.getArbol().enOrdenVector(libros);
				hash.gestionarHashTable(libros);
			}
			break;
		case 5: 
			registroDVDs.generarDVDs(100);
			break;
		case 6:
			registroDVDs.mostrarDVDs();
			break;
		case 7: { // ARREGLAR PRESENTACION (PENDIENTE)
			string id;
			posicion(47, 13); cout << "Ingrese ID del DVD: ";
			getline(cin >> ws, id);

			DVD* dvd = registroDVDs.getArbol().buscarPorId(id);

			if (!dvd) {
				posicion(47, 15); cout << "DVD no encontrado.";
				Sleep(600);
			}
			else {
				posicion(47, 15); cout << dvd->toString();
				_getch();
			}
			break;
		}
		case 8:
			registro.mostrarUsuarios();
			break;
		case 9:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 33); cout << "Cerrando sesion...";
			resetColor();
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			system("cls");
			return;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 33); cout << "Opcion invalida, intente de nuevo.";
			resetColor();
			Sleep(numRandom() * 600);
			break;
		}

	} while (true);
}


