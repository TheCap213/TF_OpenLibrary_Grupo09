#include "MenuFuncionalidad.hpp"
#include "Libro.hpp"
#include "DVD.hpp"

int DVD::idCounter = 0;
int Libro::idCounter = 0;

int main() {
	//system("color fd");

	menuPrincipal();

	_getch();
	return 0;
}