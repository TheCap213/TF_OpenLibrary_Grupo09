#pragma once

template <class T>
class NodoLibro {
public:
	T raiz;
	NodoLibro* izquierda;
	NodoLibro* derecha;
	NodoLibro(T libro) : raiz(libro), izquierda(nullptr), derecha(nullptr) {}
};
