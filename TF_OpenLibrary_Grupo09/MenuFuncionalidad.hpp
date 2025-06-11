#pragma once
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>

void leerOpcionValida(int& opcion, int min, int max);
int numRandom();

void menuPrincipal() {
	system("cls");
	int opcion; 
	
	system("tittle Open Library");
	dibujarBordes("#b3b3b3");
	tituloMenu(20, 6); 
	birrete(16, 15);
	birrete(88, 15);
	libroMenu(27, 27);
	
	backgroundColor("#41b68f");
	textColor("#000000");
	posicion(43, 15); cout << "|.......... BIENVENIDO ..........|";
	resetColor();

	textColor("#ffffff");
	posicion(45, 17); cout << "1. Resgistrar nuevo usuario";
	posicion(45, 19); cout << "2. Iniciar sesion";
	posicion(45, 21); cout << "3. Salir";
	posicion(43, 23); cout << "> Ingrese una opcion: ";
	posicion(65, 23); cin >> opcion;
	resetColor();


	switch (opcion) {
	case 1 :
		posicion(43, 25); cout << "Accediendo al modulo de registro..."; 
		Sleep(numRandom() * 1000); 
		//COLOCAR LA FUNCION REGISTRO Xd
		break; 

	case 2: 
		posicion(43, 25); cout << "Accediendo al modulo de inicio de sesion...";
		Sleep(numRandom() * 1000);
		//COLOCAR LA FUNCION INICIO DE SESION
		break;

	case 3: 
		posicion(43, 25); cout << "Cerrando Sesion...";
		Sleep(numRandom() * 1000);
		break;

	default:
		posicion(43, 25); cout << "Eliga una opcion valida.";
		Sleep(numRandom() * 500);
		menuPrincipal();
		break;
	}

}

// Pendiente su retiro de esta cosa xd
void leerOpcionValida(int& opcion, int min, int max) {
	while (cin.fail() || opcion < min || opcion > max) {
		cin.clear();
		cin.ignore(1000, '\n'); 
		posicion(43, 25); cout << "Opcion no valida, Intente nuevamente";
		cin >> opcion;
	}
}

int numRandom() {
	srand(time(0)); 
	int tiempoAleatorio = rand() % 3 + 1;
	return tiempoAleatorio;
}

