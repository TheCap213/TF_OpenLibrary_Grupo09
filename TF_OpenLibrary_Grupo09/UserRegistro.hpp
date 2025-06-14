#pragma once
#include "ListaUsuarios.hpp"
#include "Autentificador.hpp"
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>

template <typename T>
class UserRegistro {
private: 
	ListaUsuarios<T> listaUser; 
	T* userLogueado = nullptr;
	
public: 
	UserRegistro() {
		listaUser.abrirDesdeArchivo("usuarios.txt");
	}
	~UserRegistro() {
		listaUser.guardarEnArchivo("usuarios.txt");
	}

	void registrarUsuario() {
		system("cls");
		system("title Open Library - Register");
		dibujarBordes("#b3b3b3");
		mostrarCursor();

		int edad, user;
		string dni, nombre, correo, password;
		tituloRegistro(33, 4);

		textColor("#ffffff");
		posicion(29, 11); cout << "Bienvenido a Open Library!!!, Porfavor ingrese correctamente sus datos";
		posicion(29, 12); cout << "para evitar problemas en su registro al sistema.";


		backgroundColor("#f3fc83");
		textColor("#000000");
		posicion(37, 15); cout << "|.............. FORMULARIO DE REGISTRO ..............|";
		resetColor();

		textColor("#ffffff");
		posicion(42, 17); cout << "-> DNI: "; cin >> dni; cin.ignore();
		if (!Autentificador<T>::validarDNI(dni)) {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(50, 17); cout << "DNI invalido, intente de nuevo.";
			Sleep(numRandom() * 600);
			registrarUsuario();
		}
		if (listaUser.buscarPorDNI(dni)) {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(50, 17); cout << "Ya existe un usuraio con ese DNI.";
			Sleep(numRandom() * 600);
			registrarUsuario();
		}

		posicion(42, 19); cout << "-> Nombre: "; getline(cin, nombre);
		posicion(42, 21); cout << "-> Edad: "; cin >> edad; cin.ignore();
		if (!Autentificador<T>::validarEdad(edad)) {
			ocultarCursor(); 
			textColor("#fa6f09");
			posicion(51, 21); cout << "Edad fuera de rango permintido";
			Sleep(numRandom() * 800);
			registrarUsuario();
		}

		posicion(42, 23); cout << "-> Correo electronico: "; getline(cin, correo);
		if (!Autentificador<T>::validarCorreo(correo)) {	
			ocultarCursor();
			textColor("#fa6f09");
			posicion(65, 23); cout << "Correo invalido, intente de nuevo.";
			Sleep(numRandom() * 800);
			registrarUsuario();
		}

		posicion(42, 25); cout << "-> Contrasenia (min 5 caracteres): "; getline(cin, password);
		if (!Autentificador<T>::validarPassword(password)) {
			ocultarCursor();
			textColor("#fa6f09");
			posicion(77, 25); cout << "Contrasenia poco segura, intete de nuevo.";
			Sleep(numRandom() * 800);
			registrarUsuario();
		}

		posicion(42, 27); cout << "-> Tipo de usuario (1:User | 2:admin): "; cin >> user;
		Rol rolElegido = (user == 2) ? ADMIN : USER;

		T nuevoUser(dni, nombre, edad, correo, password, rolElegido);
		listaUser.agregarUsuario(nuevoUser);
		listaUser.guardarEnArchivo("usuarios.txt");

		ocultarCursor();
		posicion(54, 29); cout << "Registro exitoso!!!";
		resetColor();
		Sleep(numRandom() * 650);

		iniciarSesion();
	}

	void iniciarSesion() {
		system("cls");
		system("title Open Library - Login");
		dibujarBordes("#b3b3b3");
		mostrarCursor();

		string dni, password;
		tituloLogin(17, 3);

		textColor("#ffffff");
		posicion(36, 11); cout << "Bienvenido!!!, Gracias por formar parte de OpenLibrary";
		posicion(36, 12); cout << "por favor inicie sesion para acceder al sistema.";

		backgroundColor("#62e6e8");
		textColor("#000000");
		posicion(36, 15); cout << "|.......... FORMULARIO DE INICIO DE SESION ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(38, 17); cout << "DNI: "; cin >> dni; cin.ignore();
		if (!Autentificador<T>::validarDNI(dni)) {
			ocultarCursor();
			textColor("#147ceb");
			posicion(43, 17); cout << "DNI invalido, intente nuevamente.";
			Sleep(numRandom() * 600);
			iniciarSesion();
		}

		posicion(38, 19); cout << "Contrasenia: "; getline(cin, password); resetColor();
		if (!Autentificador<T>::validarPassword(password)) {
			ocultarCursor();
			textColor("#147ceb");
			posicion(51, 19); cout << "Contrasenia incorrecta, intente nuevamente.";
			Sleep(numRandom() * 600);
			iniciarSesion();
		}

		T* encontrado = Autentificador<T>::autenticar(listaUser, dni, password);
		if (!encontrado) {
			ocultarCursor();
			textColor("#147ceb");
			posicion(40, 21); cout << "Usuario no encontrado.";
			Sleep(numRandom() * 600);
			system("cls");
			return;
		}

		userLogueado = encontrado;
		textColor("#29ffef");
		posicion(40, 21); cout << "Sesion iniciada. Bienvenido " << userLogueado->getNombre() << "!!!";
		resetColor();
		ocultarCursor();
		Sleep(numRandom() * 600);
		system("cls");
	}

	T* getUserLogueado() { return userLogueado; }


};