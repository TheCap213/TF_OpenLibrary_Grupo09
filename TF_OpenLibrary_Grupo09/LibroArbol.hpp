#pragma once
#include "NodoLibro.hpp"
#include "Libro.hpp"
#include <functional>
#include <iostream>
#include <string>

template <class T>
class LibroArbol {
	typedef function<int(T, T)> Comp; 

	NodoLibro<T>* raiz;
	void (*procesar)(T);

	Comp comparar;

private:

	NodoLibro<T>* _insertarLibro(NodoLibro<T>* nodo, T libro) {
		if (nodo == nullptr) {
			return new NodoLibro<T>(libro);
		}
		int resultado = comparar(nodo->raiz, libro);
		if (resultado > 0) {
			nodo->izquierda = _insertarLibro(nodo->izquierda, libro);
		}
		else if (resultado < 0) {
			nodo->derecha = _insertarLibro(nodo->derecha, libro);
		}
		return nodo;
	}
	bool _buscarLibro(NodoLibro<T>* nodo, T libro) {
		if (nodo == nullptr) return false;
		int r = comparar(nodo->raiz, libro);
		if (r == 0) return true;
		if (r < 0) return _buscarLibro(nodo->derecha, libro);
		else       return _buscarLibro(nodo->izquierda, libro);
	}
	void _enOrden(NodoLibro<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izquierda);
		procesar(nodo->raiz);
		_enOrden(nodo->derecha);
	}

	bool _eliminarLibro(NodoLibro<T>*& nodo, T e) {
		if (nodo == nullptr) return false;

		int r = comparar(nodo->raiz, e);
		if (r < 0) {
			return _eliminarLibro(nodo->derecha, e);
		}
		else if (r > 0) {
			return _eliminarLibro(nodo->izquierda, e);
		}
		else {
			if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
				delete nodo; 
				nodo = nullptr; 
			}
			else if (nodo->izquierda == nullptr) {
				NodoLibro<T>* temp = nodo;
				nodo = nodo->derecha;
				delete temp;
			}
			else if (nodo->derecha == nullptr) {
				NodoLibro<T>* temp = nodo;
				nodo = nodo->izquierda;
				delete temp;
			}
			else {
				NodoLibro<T>* temp = nodo->derecha;
				while (temp->izquierda != nullptr) {
					temp = temp->izquierda;
				}
				nodo->raiz = temp->raiz;
				_eliminarLibro(nodo->derecha, temp->raiz);
			}
			return true;
		}
	}
	void _guardarEnArchivo(NodoLibro<T>* nodo, ofstream& f) {
		if (nodo == nullptr) return;
		_guardarEnArchivo(nodo->izquierda, f);
		f << nodo->raiz.serializar() << endl;
		_guardarEnArchivo(nodo->derecha, f);
	}

public:

	LibroArbol(Comp comparar, void (*procesar)(T)) 
		: raiz(nullptr), comparar(comparar), procesar(procesar) {}

	bool insertarLibro(T libro) {
		raiz = _insertarLibro(raiz, libro);
		return true;
	}

	bool buscarLibro(T libro) {
		return _buscarLibro(raiz, libro);
	}

	void enOrden() {
		_enOrden(raiz);
	}

	bool eliminarLibro(T libro) {
		return _eliminarLibro(raiz, libro);
	}
	void abrirDesdeArchivo(string nombreArchivo) {
		ifstream f(nombreArchivo);
		string linea;
		int maxId = 0;
		while (getline(f, linea)) {
			T lib;
			lib.deserializar(linea);
			insertarLibro(lib);
			string id = lib.getId();
			size_t pos = id.find('-');
			if (pos != string::npos) {
				int num = stoi(id.substr(pos + 1));
				if (num > maxId) maxId = num;
			}
		}
		T::idCounter = maxId;
	}	
	void guardarEnArchivo(string nombreArchivo) {
		ofstream f(nombreArchivo);
		_guardarEnArchivo(raiz, f);
	}
};