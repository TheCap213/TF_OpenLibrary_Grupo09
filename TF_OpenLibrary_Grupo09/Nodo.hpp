#pragma once

template <typename T>
class Nodo {
public: 
	T dato;
	Nodo<T>* siguiente;
	Nodo(T dato, Nodo<T>* sig) : dato(dato), siguiente(sig) {}
};