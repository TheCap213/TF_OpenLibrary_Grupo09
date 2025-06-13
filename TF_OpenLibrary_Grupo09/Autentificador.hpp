#pragma once
#include <algorithm>
#include "ListaUsuarios.hpp"

template <class T>
class Autentificador {
public: 
	
	T* autenticar(ListaUsuarios<T>& lista, string dni, string password) {
		Nodo<T>* temp = lista.getCabeza();
		while (temp) {
			if (temp->dato.getDni() == dni && temp->dato.getPassword() == password) {
				return &(temp->dato);
			}
			temp = temp->siguiente;
		}
		return nullptr;
	}

	bool validarDNI(string dni) {
		auto esDigito = [](char c) {return c >= '0' && c <= '9'; };
		return dni.length() == 8 && all_of(dni.begin(), dni.end(), esDigito);
	}

	bool validarPassword(string password) {
		auto longitud = [](string p) {return p.length() >= 5; };
		return longitud(password);

	}

	bool validarEdad(string edad) {
		auto  validarEdad = [](string e) {return edad >= 15 && edad <= 150; };
		return validarEdad(edad);
	}

	bool validarCorreo(string correo) {
		auto validarCorreo = [](string c) {return c.find('@') != string::npos && c.find('.') != string::npos; };
		return validarCorreo(correo);
	}



};