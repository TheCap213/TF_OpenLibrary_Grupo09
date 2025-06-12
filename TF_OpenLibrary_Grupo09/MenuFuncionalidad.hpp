#pragma once
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>

int numRandom() {
	srand(time(0));
	int tiempoAleatorio = rand() % 3 + 1;
	return tiempoAleatorio;
}

void registrarUsuario();
void iniciarSesion();
void menuUsuario();

void menuPrincipal() {
	system("cls");
	mostrarCursor();
	int opcion; 
	
	system("title Open Library");
	dibujarBordes("#b3b3b3");
	tituloOpenLibrary(5, 6); 
	birrete(20, 15);
	birrete(93, 15);
	libroMenu(31, 26);
	
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
		registrarUsuario();
		break; 

	case 2:
		ocultarCursor();
		textColor("#62e6e8");
		posicion(47, 24); cout << "Accediendo al modulo de login...";
		Sleep(numRandom() * 600);
		iniciarSesion();
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

}

void registrarUsuario() {
	system("cls"); 
	system("title Open Library - Register");
	dibujarBordes("#b3b3b3");
	mostrarCursor();

	int edad, user;
	string dni, nombre, correo, pass; 
	tituloRegistro(33, 4);

	textColor("#ffffff");
	posicion(29, 11); cout << "Bienvenido a Open Library!!!, Porfavor ingrese correctamente sus datos";
	posicion(29, 12); cout << "para evitar problemas en su registro al sistema.";
	

	backgroundColor("#f3fc83");
	textColor("#000000");
	posicion(37, 15); cout << "|.............. FORMULARIO DE REGISTRO ..............|";
	resetColor();

	textColor("#ffffff");
	posicion(42, 17); cout << "-> DNI: ";
	cin >> dni;
	cin.ignore();

	posicion(42, 19); cout << "-> Nombre: ";
	getline(cin, nombre);

	posicion(42, 21); cout << "-> Edad: ";
	cin >> edad;
	cin.ignore();

	posicion(42, 23); cout << "-> Correo electronico: ";
	getline(cin, correo);

	posicion(42, 25); cout << "-> Contrasenia (min 5 caracteres): ";
	getline(cin, pass);

	posicion(42, 27); cout << "-> Tipo de usuario (user/admin): ";
	cin >> user;
	
	posicion(54, 29); cout << "Registro exitoso!!!";

	/*
	* AGREGAR UNA FUNCION QUE VERIFIQUE SI EL REGISTRO FUE CORRECTO
	* PARA QUE LO LLEVE A INICAR SESION AUTOMATICAMENTE Y EN CASO 
	* NO SE PUDO REGISTRAR BIEN, SE RESETEE REGSITRAR USUARIO
	*/

	resetColor();

	iniciarSesion();
}

void iniciarSesion() {
	system("cls");
	system("title Open Library - Login");
	dibujarBordes("#b3b3b3");
	mostrarCursor();

	string dni, pass;
	tituloLogin(17, 3);

	textColor("#ffffff");
	posicion(36, 11); cout << "Bienvenido!!!, Gracias por formar parte de OpenLibrary";
	posicion(36, 12); cout << "por favor inicie sesion para acceder al sistema.";

	backgroundColor("#62e6e8");
	textColor("#000000");
	posicion(36, 15); cout << "|.......... FORMULARIO DE INICIO DE SESION ..........|";
	resetColor();

	textColor("#ffffff"); 
	posicion(38, 17); cout << "DNI: ";
	cin >> dni;
	cin.ignore();
	
	posicion(38, 19); cout << "Contrasenia: ";
	getline(cin, pass);
	resetColor();

	menuUsuario();

	/*
	* AGREAGAR UNA FUNCION QUE IDENTIFIQUE SI EL INCIO DE SESION ESTUBO MAL 
	* PARA QUE SE RECARGUE DE NUEVO INICIAR SESION Y EN CASO SI LO LLEVE 
	* AUTOMATICAMENTE A SU MENU (USUARIO O ADMINISTRADOR)
	*/

}

void menuUsuario() {
	system("cls");
	system("title Open Library - User");
	dibujarBordes("#b3b3b3");
	mostrarCursor();
	int opcion;

	tituloOpenLibrary(5, 6);
	backgroundColor("#41b68f");
	textColor("#000000");
	posicion(42, 15); cout << "|............. MENU PRINCIPAL .............|";
	resetColor();

	textColor("#ffffff");
	posicion(36, 13); cout << "Bienvenido USUARIO, que desesas hacer hoy?";

	posicion(45, 17); cout << "[1] Ver todos los libros";
	posicion(45, 18); cout << "[2] Buscar libros";
	posicion(45, 19); cout << "[3] Reservar libro";
	posicion(45, 20); cout << "[4] Ver mis reservas";
	posicion(45, 21); cout << "[5] Devolver libro";
	posicion(45, 22); cout << "[6] Ver comunicados";
	posicion(45, 23); cout << "[7] Soporte";
	posicion(45, 24); cout << "[8] Cerrar sesion";
	posicion(42, 26); cout << "> Ingrese una opcion: ";
	cin >> opcion;

}

void menuAdmin() {
	system("cls");
	system("title Open Library - Owner");
	dibujarBordes("#b3b3b3");
	mostrarCursor();
	int opcion;

	tituloOpenLibrary(5, 6);
	backgroundColor("#41b68f");
	textColor("#000000");
	posicion(42, 15); cout << "|............. MENU PRINCIPAL .............|";
	resetColor();

	textColor("#ffffff");
	posicion(36, 13); cout << "Bienvenido USUARIO, que desesas hacer hoy?";

	posicion(45, 17); cout << "[1] Agregar libro";
	posicion(45, 18); cout << "[2] Buscar libro";
	posicion(45, 19); cout << "[3] Ver todos los libros";
	posicion(45, 20); cout << "[4] Gestionar Foro de Anuncios";
	posicion(45, 21); cout << "[5] Ver todos los usuarios";
	posicion(45, 23); cout << "[6] Soporte (PENDIENTE)";
	posicion(45, 24); cout << "[7] Cerrar Sesion";
	posicion(42, 26); cout << "> Ingrese una opcion: ";
	cin >> opcion;

}