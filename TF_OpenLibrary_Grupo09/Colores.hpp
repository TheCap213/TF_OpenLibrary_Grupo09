#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

void activarModoColoresRGB() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	dwMode |= 0x004;
	SetConsoleMode(hOut, dwMode);
}

void resetColor() {
	cout << "\x1b[0m";
}

void textColor(const string& hex) {
	if (hex.length() != 7 || hex[0] != '#')return;
	int r = stoi(hex.substr(1, 2), nullptr, 16);
	int g = stoi(hex.substr(3, 2), nullptr, 16);
	int b = stoi(hex.substr(5, 2), nullptr, 16);
	cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m";
}

void backgroundColor(const string& hex) {
	if (hex.length() != 7 || hex[0] != '#')return;
	int r = stoi(hex.substr(1, 2), nullptr, 16);
	int g = stoi(hex.substr(3, 2), nullptr, 16);
	int b = stoi(hex.substr(5, 2), nullptr, 16);
	cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
}

void clearBackground(int r, int g, int b, int alto = 25, int ancho = 80) {
	cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
	for (int i = 0; i < alto; ++i) {
		for (int j = 0; j < ancho; ++j) cout << " ";
		cout << "\n";
	}
	cout << "\x1b[" << alto << "A"; // Subir cursor
}

void dibujarBordes(const string& hexColor) {
	SetConsoleOutputCP(CP_UTF8);
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO infoConsola;
	GetConsoleScreenBufferInfo(consola, &infoConsola);

	int ancho = infoConsola.srWindow.Right - infoConsola.srWindow.Left + 1;
	int alto = infoConsola.srWindow.Bottom - infoConsola.srWindow.Top + 1;

	string bloque = u8"█"; // Unicode block
	textColor(hexColor);

	COORD cursorOriginal = infoConsola.dwCursorPosition;

	COORD filaSuperior = { 0, infoConsola.srWindow.Top };
	SetConsoleCursorPosition(consola, filaSuperior);
	for (int i = 0; i < ancho; ++i) cout << bloque;

	for (int fila = infoConsola.srWindow.Top + 1; fila < infoConsola.srWindow.Bottom; ++fila) {
		COORD izquierda = { 0, (SHORT)fila };
		COORD derecha = { (SHORT)(ancho - 1), (SHORT)fila };

		SetConsoleCursorPosition(consola, izquierda); cout << bloque;
		SetConsoleCursorPosition(consola, derecha);   cout << bloque;
	}

	COORD filaInferior = { 0, infoConsola.srWindow.Bottom };
	SetConsoleCursorPosition(consola, filaInferior);
	for (int i = 0; i < ancho; ++i) cout << bloque;

	SetConsoleCursorPosition(consola, cursorOriginal);
	resetColor();
}

void posicion(int x, int y) {
	COORD posicion;
	posicion.X = x;
	posicion.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicion);
}
