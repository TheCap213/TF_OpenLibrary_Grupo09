#pragma once
#include "NodoLibro.hpp"
#include "Libro.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class LibroAVL {
	typedef function<int(T, T)> Comp;

	struct NodoAVL {
		T raiz;
		NodoAVL* izquierda;
		NodoAVL* derecha;
		int altura;

		NodoAVL(T libro) : raiz(libro), izquierda(nullptr), derecha(nullptr), altura(1) {}
	};

	NodoAVL* raiz;
	void (*procesar)(T);
	Comp comparar;

	// Devuelve la altura de un nodo
	int getAltura(NodoAVL* nodo) {
		return nodo ? nodo->altura : 0;
	}

	// Calcula factor de balance
	int getBalance(NodoAVL* nodo) {
		return nodo ? getAltura(nodo->izquierda) - getAltura(nodo->derecha) : 0;
	}

	// Rotación derecha
	NodoAVL* rightRotate(NodoAVL* y) {
		NodoAVL* x = y->izquierda;
		NodoAVL* T2 = x->derecha;

		x->derecha = y;
		y->izquierda = T2;

		y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;
		x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;

		return x;
	}

	// Rotación izquierda
	NodoAVL* leftRotate(NodoAVL* x) {
		NodoAVL* y = x->derecha;
		NodoAVL* T2 = y->izquierda;

		y->izquierda = x;
		x->derecha = T2;

		x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;
		y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;

		return y;
	}

	// Inserta y balancea
	NodoAVL* _insertar(NodoAVL* nodo, T libro) {
		if (nodo == nullptr) return new NodoAVL(libro);

		int resultado = comparar(libro, nodo->raiz);

		if (resultado < 0)
			nodo->izquierda = _insertar(nodo->izquierda, libro);
		else if (resultado > 0)
			nodo->derecha = _insertar(nodo->derecha, libro);
		else
			return nodo; // Duplicate ID -> NO insert

		// Actualizar altura
		nodo->altura = 1 + max(getAltura(nodo->izquierda), getAltura(nodo->derecha));

		// Balancear
		int balance = getBalance(nodo);

		// 4 casos

		// Left Left
		if (balance > 1 && comparar(libro, nodo->izquierda->raiz) < 0)
			return rightRotate(nodo);

		// Right Right
		if (balance < -1 && comparar(libro, nodo->derecha->raiz) > 0)
			return leftRotate(nodo);

		// Left Right
		if (balance > 1 && comparar(libro, nodo->izquierda->raiz) > 0) {
			nodo->izquierda = leftRotate(nodo->izquierda);
			return rightRotate(nodo);
		}

		// Right Left
		if (balance < -1 && comparar(libro, nodo->derecha->raiz) < 0) {
			nodo->derecha = rightRotate(nodo->derecha);
			return leftRotate(nodo);
		}

		return nodo;
	}

	// Búsqueda por ID
	NodoAVL* _buscar(NodoAVL* nodo, const string& id) {
		if (!nodo) return nullptr;
		if (nodo->raiz.getId() == id) return nodo;
		if (id < nodo->raiz.getId()) return _buscar(nodo->izquierda, id);
		return _buscar(nodo->derecha, id);
	}

	// Recorrido inorden
	void _enOrden(NodoAVL* nodo) {
		if (!nodo) return;
		_enOrden(nodo->izquierda);
		procesar(nodo->raiz);
		_enOrden(nodo->derecha);
	}

	void _enOrdenVectorRec(NodoAVL* nodo, vector<T>& libros) {
		if (!nodo) return;
		_enOrdenVectorRec(nodo->izquierda, libros);
		libros.push_back(nodo->raiz);
		_enOrdenVectorRec(nodo->derecha, libros);
	}

public:

	LibroAVL(Comp comparar, void (*procesar)(T))
		: raiz(nullptr), comparar(comparar), procesar(procesar) {
	}

	bool insertarLibro(T libro) {
		raiz = _insertar(raiz, libro);
		return true;
	}

	T* buscarPorId(const string& id) {
		NodoAVL* nodo = _buscar(raiz, id);
		return nodo ? &nodo->raiz : nullptr;
	}

	void enOrden() {
		_enOrden(raiz);
	}

	void enOrdenVector(vector<T>& libros) {
		_enOrdenVectorRec(raiz, libros);
	}
};
