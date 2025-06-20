﻿#pragma once
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include "UserRegistro.hpp"
#include "LibroRegistro.hpp"
#include "LibroArbol.hpp" //pendiente a quitar
#include <ctime>
using namespace std;

UserRegistro<Usuario> registro;
LibroRegistro<Libro> registroLibros;

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
		cin >> opcion;
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
	mostrarCursor();
	int opcion;
	
	do {
		system("cls");
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
		posicion(7, 22); cout << "[4] Ver mis reservas";
		posicion(7, 24); cout << "[5] Devolver libro";
		posicion(7, 26); cout << "[6] Ver comunicados";
		posicion(7, 28); cout << "[7] Soporte";
		posicion(7, 30); cout << "[8] Cerrar sesion";
		posicion(5, 32); cout << "> Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			registroLibros.mostrarLibros();
			menuUsuario();
			break;
		case 2:
			registroLibros.buscarLibro();
			menuUsuario();
			break;
		case 8:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 34); cout << "Cerrando sesion...";
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			menuPrincipal();
			break;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 34); cout << "Opcion invalida, intente de nuevo.";
			Sleep(numRandom() * 600);
			menuUsuario();
			break;
		}

	} while (opcion < 1 || opcion > 8);
}

void menuAdmin() {
	mostrarCursor();
	int opcion;
	
	do {
		system("cls");
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

		posicion(7, 16); cout << "[1] Agregar libro";
		posicion(7, 18); cout << "[2] Buscar libro";
		posicion(7, 20); cout << "[3] Ver todos los libros";
		posicion(7, 22); cout << "[4] Gestionar Foro de Anuncios";
		posicion(7, 24); cout << "[5] Ver todos los usuarios";
		posicion(7, 26); cout << "[6] Soporte (PENDIENTE)";
		posicion(7, 28); cout << "[7] Cerrar Sesion";
		posicion(5, 31); cout << "> Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1: 
			registroLibros.registrarLibro();
			menuAdmin();
			break;
		case 2:
			registroLibros.buscarLibro();
			menuAdmin();
			break;
		case 3: 
			registroLibros.mostrarLibros();
			menuAdmin();
			break;
		case 5: 
			registro.mostrarUsuarios();
			menuAdmin();
			break;
		case 7:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 33); cout << "Cerrando sesion...";
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			menuPrincipal();
			break;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 33); cout << "Opcion invalida, intente de nuevo.";
			Sleep(numRandom() * 600);
			menuAdmin();
			break;
		}

	} while (opcion < 1 || opcion > 7);
}


