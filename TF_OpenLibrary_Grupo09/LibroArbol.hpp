#pragma once
#include "NodoLibro.hpp"
#include "Libro.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

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
	NodoLibro<T>* _buscarPorIdRec(NodoLibro<T>* nodo, const string& id) {
		if (!nodo) return nullptr;
		if (nodo->raiz.getId() == id) return nodo;
		if (id < nodo->raiz.getId()) return _buscarPorIdRec(nodo->izquierda, id);
		return _buscarPorIdRec(nodo->derecha, id);
	}
	void _enOrden(NodoLibro<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izquierda);
		procesar(nodo->raiz);
		_enOrden(nodo->derecha);
	}
	void _enOrdenVectorRec(NodoLibro<T>* nodo, vector<T>& libros) {
		if (nodo == nullptr) return;
		_enOrdenVectorRec(nodo->izquierda, libros);
		libros.push_back(nodo->raiz);
		_enOrdenVectorRec(nodo->derecha, libros);
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
	T* buscarPorId(const string& id) {
		NodoLibro<T>* nodo = _buscarPorIdRec(raiz, id);
		return nodo ? &nodo->raiz : nullptr;
	}	
	void enOrden() {
		_enOrden(raiz);
	}

	void enOrdenVector(vector<T>& libros) {
		_enOrdenVectorRec(raiz, libros);
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