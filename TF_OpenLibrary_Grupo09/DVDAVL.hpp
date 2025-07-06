#pragma once
#include "DVD.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class DVDAVL {
    typedef function<int(T, T)> Comp;

    struct NodoAVL {
        T raiz;
        NodoAVL* izquierda;
        NodoAVL* derecha;
        int altura;

        NodoAVL(T dvd) : raiz(dvd), izquierda(nullptr), derecha(nullptr), altura(1) {}
    };

    NodoAVL* raiz;
    void (*procesar)(T);
    Comp comparar;

    int getAltura(NodoAVL* nodo) { return nodo ? nodo->altura : 0; }
    int getBalance(NodoAVL* nodo) { return nodo ? getAltura(nodo->izquierda) - getAltura(nodo->derecha) : 0; }

    NodoAVL* rightRotate(NodoAVL* y) {
        NodoAVL* x = y->izquierda;
        NodoAVL* T2 = x->derecha;

        x->derecha = y;
        y->izquierda = T2;

        y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;
        x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;

        return x;
    }

    NodoAVL* leftRotate(NodoAVL* x) {
        NodoAVL* y = x->derecha;
        NodoAVL* T2 = y->izquierda;

        y->izquierda = x;
        x->derecha = T2;

        x->altura = max(getAltura(x->izquierda), getAltura(x->derecha)) + 1;
        y->altura = max(getAltura(y->izquierda), getAltura(y->derecha)) + 1;

        return y;
    }

    NodoAVL* _insertar(NodoAVL* nodo, T dvd) {
        if (nodo == nullptr) return new NodoAVL(dvd);

        int resultado = comparar(dvd, nodo->raiz);

        if (resultado < 0) nodo->izquierda = _insertar(nodo->izquierda, dvd);
        else if (resultado > 0) nodo->derecha = _insertar(nodo->derecha, dvd);
        else return nodo;

        nodo->altura = 1 + max(getAltura(nodo->izquierda), getAltura(nodo->derecha));

        int balance = getBalance(nodo);

        if (balance > 1 && comparar(dvd, nodo->izquierda->raiz) < 0) return rightRotate(nodo);
        if (balance < -1 && comparar(dvd, nodo->derecha->raiz) > 0) return leftRotate(nodo);
        if (balance > 1 && comparar(dvd, nodo->izquierda->raiz) > 0) {
            nodo->izquierda = leftRotate(nodo->izquierda);
            return rightRotate(nodo);
        }
        if (balance < -1 && comparar(dvd, nodo->derecha->raiz) < 0) {
            nodo->derecha = rightRotate(nodo->derecha);
            return leftRotate(nodo);
        }

        return nodo;
    }

    NodoAVL* _buscar(NodoAVL* nodo, const string& id) {
        if (!nodo) return nullptr;
        if (nodo->raiz.getId() == id) return nodo;
        if (id < nodo->raiz.getId()) return _buscar(nodo->izquierda, id);
        return _buscar(nodo->derecha, id);
    }

    void _enOrden(NodoAVL* nodo) {
        if (!nodo) return;
        _enOrden(nodo->izquierda);
        procesar(nodo->raiz);
        _enOrden(nodo->derecha);
    }

    void _enOrdenVectorRec(NodoAVL* nodo, vector<T>& dvds) {
        if (!nodo) return;
        _enOrdenVectorRec(nodo->izquierda, dvds);
        dvds.push_back(nodo->raiz);
        _enOrdenVectorRec(nodo->derecha, dvds);
    }

public:
    DVDAVL(Comp comparar, void (*procesar)(T))
        : raiz(nullptr), comparar(comparar), procesar(procesar) {
    }

    bool insertarDVD(T dvd) { raiz = _insertar(raiz, dvd); return true; }

    T* buscarPorId(const string& id) {
        NodoAVL* nodo = _buscar(raiz, id);
        return nodo ? &nodo->raiz : nullptr;
    }

    void enOrden() { _enOrden(raiz); }

    void enOrdenVector(vector<T>& dvds) { _enOrdenVectorRec(raiz, dvds); }
};
