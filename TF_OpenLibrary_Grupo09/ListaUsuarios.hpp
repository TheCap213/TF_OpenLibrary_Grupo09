#pragma once
#include "Usuario.hpp"
#include "Nodo.hpp"
#include <iostream>
#include <fstream>
using namespace std; 

template <typename T>
class ListaUsuarios {
private: 
	Nodo<T>* cabeza;

public: 
	ListaUsuarios() {
		cabeza = nullptr;
	}

	void agregarUsuario(T nuevo) {
		Nodo<T>* nodo = new Nodo<T>(nuevo);
		if (!cabeza) {
			cabeza = nodo; 
		}
		else {
			Nodo<T>* temp = cabeza; 
			while (temp->siguiente) {
				temp = temp->siguiente;
			}
			temp->siguiente = nodo;
		}
	}

	void guardarEnArchivo(string nombreArchivo) {
		ofstream archivo(nombreArchivo);
		Nodo<T>* temp = cabeza; 
		while (temp) {
			archivo << temp->dato.serializar() << endl; 
			temp = temp->siguiente; 
		}
		archivo.close();
	}

	void abrirDesdeArchivo(string nombreArchivo) {
		ifstream archivo(nombreArchivo);
		string linea; 
		while (getline(archivo, linea)) {
			T elem; 
			elem.deserializar(linea);
			agregarUsuario(elem);
		}
		archivo.close();
	}

	Nodo<T>* getCabeza() {
		return cabeza;
	}

	bool estaVacia() {
		return cabeza == nullptr;
	}
};