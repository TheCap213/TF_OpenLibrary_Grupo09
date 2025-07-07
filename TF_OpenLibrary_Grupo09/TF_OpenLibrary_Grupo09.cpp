#include "MenuFuncionalidad.hpp"
#include "Libro.hpp"
#include "DVD.hpp"

int DVD::idCounter = 0;
int Libro::idCounter = 0;

//En caso no compile eliminar esto (solo para el tamaño del programa)
void bloquearResize() {
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
}

int main() {
    //En caso no compile eliminar estas 2 funciones.
    system("mode con: cols=128 lines=37");
    bloquearResize();

    //parte princiapl
	menuPrincipal();

	_getch();
	return 0;
}