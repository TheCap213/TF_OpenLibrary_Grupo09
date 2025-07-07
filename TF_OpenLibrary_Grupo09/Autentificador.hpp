#pragma once
#include <algorithm>
#include "ListaUsuarios.hpp"

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

	//TENEMOS 6 LAMBDAS AQUI
	
	static bool validarRol(int rol) {
		return rol == 1 || rol == 2;
	}

	static bool validarNombre(const string& nombre) {
		if (nombre.empty()) return false; // Debe tener al menos 1 caracter y no espacios
		for (char c : nombre) {
			if (!isalpha(c)) return false; // Solo letras
		}
		return true;
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
		auto  validarEdad = [](int e) {return e >= 10 && e <= 100; };
		return validarEdad(edad);
	}
	
	static bool validarCorreo(string correo) {
		auto validarCorreo = [](string c) {return c.find('@') != string::npos && c.find('.') != string::npos; };
		return validarCorreo(correo);
	}
};