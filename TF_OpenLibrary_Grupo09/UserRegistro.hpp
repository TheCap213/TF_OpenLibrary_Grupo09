#pragma once
#include "ListaUsuarios.hpp"
#include "Autentificador.hpp"
#include "Colores.hpp"
#include "FigurasMenu.hpp"
#include <ctime>
#include <vector>

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
		while (true) {
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
				continue;
			}
			if (listaUser.buscarPorDNI(dni)) {
				ocultarCursor();
				textColor("#fa6f09");
				posicion(50, 17); cout << "Ya existe un usuraio con ese DNI.";
				Sleep(numRandom() * 600);
				continue;
			}

			posicion(42, 19); cout << "-> Nombre: "; getline(cin, nombre);
			posicion(42, 21); cout << "-> Edad: "; cin >> edad; cin.ignore();
			if (!Autentificador<T>::validarEdad(edad)) {
				ocultarCursor(); 
				textColor("#fa6f09");
				posicion(51, 21); cout << "Edad fuera de rango permintido";
				Sleep(numRandom() * 800);
				continue;
			}

			posicion(42, 23); cout << "-> Correo electronico: "; getline(cin, correo);
			if (!Autentificador<T>::validarCorreo(correo)) {	
				ocultarCursor();
				textColor("#fa6f09");
				posicion(65, 23); cout << "Correo invalido, intente de nuevo.";
				Sleep(numRandom() * 800);
				continue;
			}

			posicion(42, 25); cout << "-> Contrasenia (min 5 caracteres): "; getline(cin, password);
			if (!Autentificador<T>::validarPassword(password)) {
				ocultarCursor();
				textColor("#fa6f09");
				posicion(77, 25); cout << "Contrasenia poco segura, intete de nuevo.";
				Sleep(numRandom() * 800);
				continue;
			}

			posicion(42, 27); cout << "-> Tipo de usuario (1:User | 2:admin): "; cin >> user; cin.ignore();
			Rol rolElegido = (user == 2) ? ADMIN : USER;

			T nuevoUser(dni, nombre, edad, correo, password, rolElegido);
			listaUser.agregarUsuario(nuevoUser);
			listaUser.guardarEnArchivo("usuarios.txt");

			ocultarCursor();
			posicion(54, 29); cout << "Registro exitoso!!!";
			resetColor();
			Sleep(numRandom() * 650);
			system("cls");
			return;

		}
	}

	void iniciarSesion() {
		while (true) {
			system("cls");
			system("title Open Library - Login");
			dibujarBordes("#b3b3b3");
			mostrarCursor();

			tituloLogin(17, 3);

			textColor("#ffffff");
			posicion(36, 11); cout << "Bienvenido!!!, Gracias por formar parte de OpenLibrary";
			posicion(36, 12); cout << "por favor inicie sesion para acceder al sistema.";

			backgroundColor("#62e6e8");
			textColor("#000000");
			posicion(36, 15); cout << "|.......... FORMULARIO DE INICIO DE SESION ..........|";
			resetColor();

			string dni; 
			textColor("#ffffff");
			posicion(38, 17); cout << "DNI: "; cin >> dni; cin.ignore();
			if (!Autentificador<T>::validarDNI(dni)) {
				ocultarCursor();
				textColor("#147ceb");
				posicion(43, 17); cout << "DNI invalido, intente nuevamente.";
				Sleep(numRandom() * 600);
				continue;
			}

			string password;
			posicion(38, 19); cout << "Contrasenia: "; getline(cin, password); resetColor();
			if (!Autentificador<T>::validarPassword(password)) {
				ocultarCursor();
				textColor("#147ceb");
				posicion(51, 19); cout << "Contrasenia incorrecta, intente nuevamente.";
				Sleep(numRandom() * 600);
				continue;
			}
			
			T* encontrado = Autentificador<T>::autenticar(listaUser, dni, password);
			if (!encontrado) {
				ocultarCursor();
				textColor("#147ceb");
				posicion(40, 21); cout << "Usuario no encontrado, pruebe otra vez.";
				resetColor();
				Sleep(numRandom() * 600);
				continue; 
			}

			userLogueado = encontrado;
			textColor("#29ffef");
			posicion(40, 21); cout << "Sesion iniciada. Bienvenido " << userLogueado->getNombre() << "!!!";
			resetColor();
			ocultarCursor();
			Sleep(numRandom() * 600);
			system("cls");
			return;

		}
	}

	T* getUserLogueado() { return userLogueado; }

	void cerrarSesion() {
		userLogueado = nullptr;
	}

	void mostrarUsuarios() {
		vector<T> usuarios;
		Nodo<T>* temp = listaUser.getCabeza();
		while (temp) {
			usuarios.push_back(temp->dato);
			temp = temp->siguiente;
		}
		if (usuarios.empty()) {
			posicion(50, 20); cout << "No hay usuarios registrados.";
			_getch();
			return;
		}
		int index = 0;
		int total = (int)usuarios.size();
		int tecla; 

		do {
			ocultarCursor();
			T& usuario = usuarios[index];
			backgroundColor("#f05252");
			textColor("#000000");
			posicion(50, 11); cout << "|.......... LISTA DE USUARIOS REGISTRADOS ..........|";
			resetColor();
			textColor("#ffffff");
			posicion(47, 13); cout << "DNI: " << usuario.getDni();
			posicion(47, 15); cout << "Nombre: " << usuario.getNombre();
			posicion(47, 17); cout << "Edad: " << usuario.getEdad();
			posicion(47, 19); cout << "Correo: " << usuario.getCorreo();
			posicion(47, 21); cout << "Rol: " << (usuario.getRol() == USER ? "Usuario" : "Administrador");
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
};