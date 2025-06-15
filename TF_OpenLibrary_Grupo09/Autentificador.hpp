#pragma once
#include <algorithm>
#include "ListaUsuarios.hpp"
#include "LibroArbol.hpp"

template <class T>
class Autentificador {
public: 
	
	static T* autenticar(ListaUsuarios<T>& lista, string dni, string password) {
		Nodo<T>* temp = lista.getCabeza();
		while (temp) {
			if (temp->dato.getDni() == dni && temp->dato.getPassword() == password) {
				return &(temp->dato);
			}
			temp = temp->siguiente;
		}
		return nullptr;
	}

	static bool validarDNI(string dni) {
		auto esDigito = [](char c) {return c >= '0' && c <= '9'; };
		return dni.length() == 8 && all_of(dni.begin(), dni.end(), esDigito);
	}

	static bool validarPassword(string password) {
		auto longitud = [](string p) {return p.length() >= 5; };
		return longitud(password);

	}

	static bool validarEdad(int edad) {
		auto  validarEdad = [](int e) {return e >= 15 && e <= 150; };
		return validarEdad(edad);
	}
	
	static bool validarCorreo(string correo) {
		auto validarCorreo = [](string c) {return c.find('@') != string::npos && c.find('.') != string::npos; };
		return validarCorreo(correo);
	}

	//Falta agregar autentificadores a los libros, pendiente agregacion.

};