#pragma once
#include "Colores.hpp"
#include "FigurasMenu.hpp"

void menuPrincipal() {
    
	int opcion;

	do {
	system("title OpenLibrary");	//Titulo de la consola
	//system("color fb");
	
	//Diseño del menu principal.
	textColor("#b3b3b3");
	dibujarBordes();
	resetColor();

    tituloMenu(20, 6);
	birrete(16, 15);
	birrete(88, 15);
	libroMenu(27, 26);

	backgroundColor("#41b68f");
	textColor("#000000");
	posicion(43, 15); cout << "|.......... BIENVENIDO ..........|";
	resetColor();

	textColor("#ffffff");
	posicion(45, 17); cout << "> 1. Resgistrar nuevo usuario";
	posicion(45, 19); cout << "> 2. Iniciar sesion";
	posicion(45, 21); cout << "> 3. Salir";
	posicion(43, 23); cout << "> Seleccione una opcion: ";
	posicion(68, 23); cin >> opcion;
	resetColor();


	} while (opcion != 3);



}

void MenuInicioSesion() {
	

}