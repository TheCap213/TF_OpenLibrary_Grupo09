#pragma once
#include "FigurasMenu.hpp"
#include "UserRegistro.hpp"
#include "RegistroDVD.hpp"
#include "LibroRegistro.hpp"
#include "ListaReservas.hpp"
#include "LibroHashTable.hpp"
#include <ctime>
using namespace std;

UserRegistro<Usuario> registro;
LibroRegistro<Libro> registroLibros;
RegistroDVD<DVD> registroDVDs;
ListaReservas<Reserva> listaReservasLibros;
ListaReservas<Reserva> listaReservasDVDs;

void menuUsuario();
void menuAdmin();
void reservarRecurso();
void reservarLibrosAleatorios(int cantidad);
void reservarDVDsAleatorios(int cantidad);
void reservarRecursoManual(string tipo);
void ordenarReservasLibros_Merge();
void ordenarReservasDVDs_Quick();
void ordenarReservasLibros_Heap();

void menuPrincipal() {
	system("cls");
	mostrarCursor();
	int opcion; 
	
	do {
		system("title Open Library");
		dibujarBordes("#b3b3b3");
		tituloOpenLibrary(5, 6, "#07e092");
		birrete(20, 15);
		birrete(93, 15);
		libroMenu(31, 26);
		mostrarCursor();

		backgroundColor("#41b68f");
		textColor("#000000");
		posicion(47, 14); cout << "|.......... BIENVENIDO ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(50, 16); cout << "[1] Resgistrar nuevo usuario";
		posicion(50, 18); cout << "[2] Iniciar sesion";
		posicion(50, 20); cout << "[3] Salir";
		posicion(47, 22); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;

		// POR SI UN CHISTOSO SE LE OCURRE INGRESAR UN CARACTER xd
		try {
			opcion = stoi(entrada); //Convierte el texto a int
		}
		catch (...) {
			opcion = -1; // si no es un numero le asigna -1 predeterminadamente
		}
		resetColor();

		switch (opcion) {
		case 1 :
			ocultarCursor();
			textColor("#e8e036");
			posicion(47, 24); cout << "Accediendo al modulo de registro..."; 
			Sleep(numRandom() * 600); 
			registro.registrarUsuario();
			break; 

		case 2:
			ocultarCursor();
			textColor("#62e6e8");
			posicion(47, 24); cout << "Accediendo al modulo de login...";
			Sleep(numRandom() * 600);
			registro.iniciarSesion();
			if (registro.getUserLogueado()) {
				if (registro.getUserLogueado()->getRol() == USER) {
					menuUsuario();
				}
				else {
					menuAdmin();
				}
			}
			break;

		case 3: 
			ocultarCursor();
			textColor("#e12874");
			posicion(47, 24); cout << "Cerrando Sesion...";
			Sleep(numRandom() * 600);
			system("cls");  
			exit(0);
			break;

		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(47, 24); cout << "Eliga una opcion valida.";
			Sleep(numRandom() * 600);
			menuPrincipal();
			break;
		}

	} while (true);

}

void menuUsuario() {
	int opcion;
	
	do {
		system("cls");
		mostrarCursor();
		system("title Open Library - User");
		dibujarBordes("#b3b3b3");
		dibujarLineaHorizontal(9, 1, 126, "#b3b3b3");
		dibujarLineaVertical(44, 10, 35, "#b3b3b3");
		tituloOpenLibrary(7, 2, "#07e092");
		backgroundColor("#41b68f");
		textColor("#000000");
		posicion(3, 11); cout << "|........... MENU PRINCIPAL ..........|";
		resetColor();

		textColor("#ffffff");
		posicion(3, 13); cout << "Hola " << registro.getUserLogueado()->getNombre() << ", que desesas hacer hoy?";

		posicion(5, 15); cout << "[1] Ver todos los libros";
		posicion(5, 17); cout << "[2] Ver mis reservas de Libros";
		posicion(5, 19); cout << "[3] Ver todos los DVDs";
		posicion(5, 21); cout << "[4] Ver mis reservas de DVDs";
		posicion(5, 23); cout << "[5] Reservar Rercursos (Libro/DVD)";
		posicion(5, 25); cout << "[6] MergeSort Reservas (Titulo libros)";
		posicion(5, 27); cout << "[7] QuickSort Reservas (Genero DVDs)";
		posicion(5, 29); cout << "[8] HeapSort Reservas (ID - libros)";
		posicion(5, 31); cout << "[9] Cerrar sesion";
		posicion(3, 33); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;
		try {
			opcion = stoi(entrada);
		}
		catch (...) {
			opcion = -1; 
		}

		switch (opcion) {
		case 1:
			registroLibros.mostrarLibros();
			break;
		case 2:
			listaReservasLibros.mostrarReservas();
			break;
		case 3:
			registroDVDs.mostrarDVDs();
			break;
		case 4:
			listaReservasDVDs.mostrarReservas();
			break; 
		case 5:
			reservarRecurso();
			break;
		case 6:
			ordenarReservasLibros_Merge(); 
			break;
		case 7:
			ordenarReservasDVDs_Quick(); 
			break;
		case 8: 
			ordenarReservasLibros_Heap(); 
			break;
		case 9:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 34); cout << "Cerrando sesion...";
			resetColor();
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			system("cls");
			return;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 34); cout << "Opcion invalida, intente de nuevo.";
			resetColor();
			Sleep(numRandom() * 600);
			break;
		}

	} while (true);
}

void menuAdmin() {
	int opcion;
	
	do {
		system("cls");
		mostrarCursor();
		system("title Open Library - Owner");
		dibujarBordes("#ffffff");
		dibujarLineaHorizontal(9, 1, 126, "#ffffff");
		dibujarLineaVertical(44, 10, 35, "#ffffff");
		tituloOpenLibrary(7, 2, "#f05252");
		mostrarCursor();
		backgroundColor("#f05252");
		textColor("#000000");
		posicion(3, 11); cout << "|........ MENU ADMINISTRATIVO ........|";
		resetColor();

		textColor("#ffffff");
		posicion(5, 13); cout << "Hola " << registro.getUserLogueado()->getNombre() << ", que desesas hacer hoy?";

		posicion(7, 15); cout << "[1] Generar Libros (1000)";
		posicion(7, 17); cout << "[2] Ver todos los libros";
		posicion(7, 19); cout << "[3] Buscar libro";
		posicion(7, 21); cout << "[4] Gestionar HashTable de Libros";
		posicion(7, 23); cout << "[5] Generar DVDs (1000)";
		posicion(7, 25); cout << "[6] Ver todos los DVDs";
		posicion(7, 27); cout << "[7] Buscar DVD";
		posicion(7, 29); cout << "[8] Ver todos los usuarios";
		posicion(7, 31); cout << "[9] Cerrar sesion";
		posicion(5, 33); cout << "> Ingrese una opcion: ";
		
		string entrada;
		cin >> entrada;

		try {
			opcion = stoi(entrada);
		}
		catch (...) {
			opcion = -1; 
		}

		switch (opcion) {
		case 1: 
			//Limite de generacion son 43 casos en BST pero en un AVL el limite es mayor
			registroLibros.generarLibros(1000); 
			break;
		case 2:
			registroLibros.mostrarLibros();
			break;
		case 3: 
			registroLibros.buscarLibro();
			break;
		case 4: {
				LibroHashTable hash;
				vector<Libro> libros;
				registroLibros.getArbol().enOrdenVector(libros);
				hash.gestionarHashTable(libros);
			}
			break;
		case 5: 
			registroDVDs.generarDVDs(1000);
			break;
		case 6:
			registroDVDs.mostrarDVDs();
			break;
		case 7: 
			registroDVDs.buscarDVD();
			break;
		case 8:
			registro.mostrarUsuarios();
			break;
		case 9:
			ocultarCursor();
			textColor("#e8e036");
			posicion(5, 34); cout << "Cerrando sesion...";
			resetColor();
			Sleep(numRandom() * 600);
			registro.cerrarSesion();
			system("cls");
			return;
		default:
			ocultarCursor();
			textColor("#df2b2b");
			posicion(5, 34); cout << "Opcion invalida, intente de nuevo.";
			resetColor();
			Sleep(numRandom() * 600);
			break;
		}

	} while (true);
}

void reservarLibrosAleatorios(int cantidad) {
	vector<Libro> libros;
	registroLibros.getArbol().enOrdenVector(libros);

	srand(time(nullptr));
	int creadas = 0;

	while (creadas < cantidad && !libros.empty()) {
		int idx = rand() % libros.size();

		if (libros[idx].getStock() > 0) {
			libros[idx].setStock(libros[idx].getStock() - 1);

			Reserva nuevaReserva(
				registro.getUserLogueado()->getDni(),
				libros[idx].getId(),
				libros[idx].getTitulo(),
				libros[idx].getGenero(),
				1,
				"LIBRO"
			);

			listaReservasLibros.agregarReserva(nuevaReserva);
			++creadas;
		}

		if (libros[idx].getStock() <= 0) {
			libros.erase(libros.begin() + idx);
		}
	}

	posicion(47, 25); cout << creadas << " reservas aleatorias de LIBROS creadas!";
	Sleep(800);
}

void reservarDVDsAleatorios(int cantidad) {
	vector<DVD> dvds;
	registroDVDs.getArbol().enOrdenVector(dvds);

	srand(time(nullptr));
	int creadas = 0;

	while (creadas < cantidad && !dvds.empty()) {
		int idx = rand() % dvds.size();

		if (dvds[idx].getStock() > 0) {
			dvds[idx].setStock(dvds[idx].getStock() - 1);

			Reserva nuevaReserva(
				registro.getUserLogueado()->getDni(),
				dvds[idx].getId(),
				dvds[idx].getTitulo(),
				dvds[idx].getGenero(),
				1,
				"DVD"
			);

			listaReservasDVDs.agregarReserva(nuevaReserva);
			++creadas;
		}

		if (dvds[idx].getStock() <= 0) {
			dvds.erase(dvds.begin() + idx);
		}
	}

	posicion(47, 25); cout << creadas << " reservas aleatorias de DVDs creadas!";
	Sleep(800);
}

void reservarRecurso() {
	backgroundColor("#ffd795");
	textColor("#000000");
	posicion(63, 11); cout << "|.......... RESERVAR RECURSO ..........|";
	resetColor();

	textColor("#ffffff");
	posicion(47, 13); cout << "[1] Reservar LIBRO";
	posicion(47, 15); cout << "[2] Reservar DVD";
	posicion(47, 17); cout << "[3] Reservar 100 LIBROS Aleatorios";
	posicion(47, 19); cout << "[4] Reservar 100 DVDs Aleatorios";
	posicion(47, 21); cout << "Seleccione opcion: ";

	string opcion;
	cin >> opcion;

	if (opcion == "1") {
		reservarRecursoManual("LIBRO");
	}
	else if (opcion == "2") {
		reservarRecursoManual("DVD");
	}
	else if (opcion == "3") {
		reservarLibrosAleatorios(100);
	}
	else if (opcion == "4") {
		reservarDVDsAleatorios(100);
	}
	else {
		posicion(47, 23); cout << "Opcion invalida."; Sleep(500);
	}
}

void reservarRecursoManual(string tipo) {
	string id;
	if (tipo == "LIBRO") {
		posicion(47, 23); cout << "Ingrese ID del LIBRO: ";
		getline(cin >> ws, id);

		Libro* libro = registroLibros.getArbol().buscarPorId(id);

		if (!libro) {
			posicion(47, 25); cout << "Libro no encontrado."; Sleep(600);
			return;
		}

		if (libro->getStock() <= 0) {
			posicion(47, 25); cout << "Sin stock disponible para este libro!";
			Sleep(600);
			return;
		}

		libro->setStock(libro->getStock() - 1);

		Reserva nuevaReserva(registro.getUserLogueado()->getDni(), libro->getId(), libro->getTitulo(), libro->getGenero(), 1, "LIBRO");
		listaReservasLibros.agregarReserva(nuevaReserva);

		posicion(47, 25); cout << "Reserva de LIBRO creada!";
		Sleep(800);
	}
	else if (tipo == "DVD") {
		posicion(47, 23); cout << "Ingrese ID del DVD: ";
		getline(cin >> ws, id);

		DVD* dvd = registroDVDs.getArbol().buscarPorId(id);
		if (!dvd) {
			posicion(47, 25); cout << "DVD no encontrado."; Sleep(600);
			return;
		}

		if (dvd->getStock() <= 0) {
			posicion(47, 25); cout << "Sin stock disponible para este DVD!";
			Sleep(600);
			return;
		}

		dvd->setStock(dvd->getStock() - 1);

		Reserva nuevaReserva(registro.getUserLogueado()->getDni(), dvd->getId(), dvd->getTitulo(), dvd->getGenero(), 1, "DVD");
		listaReservasDVDs.agregarReserva(nuevaReserva);

		posicion(47, 25); cout << "Reserva de DVD creada!";
		Sleep(800);
	}
}

// ---------------- MERGESORT PARA LOS TITULOS DE LAS RESERVAS DE LIBROS ----------------
void merge(vector<Reserva>& v, int l, int m, int r) {
	int n1 = m - l + 1, n2 = r - m;
	vector<Reserva> L(v.begin() + l, v.begin() + m + 1);
	vector<Reserva> R(v.begin() + m + 1, v.begin() + r + 1);

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i].getTitulo() <= R[j].getTitulo()) v[k++] = L[i++];
		else v[k++] = R[j++];
	}
	while (i < n1) v[k++] = L[i++];
	while (j < n2) v[k++] = R[j++];
}

void mergeSort(vector<Reserva>& v, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(v, l, m);
		mergeSort(v, m + 1, r);
		merge(v, l, m, r);
	}
}

void ordenarReservasLibros_Merge() {
	NodoReserva<Reserva>* actual = listaReservasLibros.getCabeza();
	vector<Reserva> reservas;

	while (actual) {
		reservas.push_back(actual->reserva);
		actual = actual->siguiente;
	}

	if (reservas.empty()) {
		ocultarCursor();
		backgroundColor("#ca9bff");
		textColor("#000000");
		posicion(49, 11); cout << "|.......... RESERVAS DE LIBROS ORDENADOS POR TITULO (Merge) ..........|";
		resetColor();
		textColor("#ffffff");
		posicion(47, 13); cout << "No hay reservas.";
		resetColor();
		Sleep(numRandom() * 600);
		return;
	}

	mergeSort(reservas, 0, reservas.size() - 1);

	// Mostrar ordenado (mismo patrón)
	const int porPagina = 20;
	int pagina = 0, total = reservas.size();
	char tecla;

	do {
		//Limpia area
		for (int y = 13; y <= 35; ++y) {
			posicion(47, y);
			cout << string(79, ' ');
		}

		backgroundColor("#ca9bff");
		textColor("#000000");
		posicion(49, 11); cout << "|.......... RESERVAS DE LIBROS ORDENADOS POR TITULO (Merge) ..........|";
		resetColor();

		int start = pagina * porPagina, end = min(start + porPagina, total);
		int y = 13;
		for (int i = start; i < end; ++i) {
			posicion(47, y++); cout << reservas[i].toString();
		}

		posicion(47, y + 1); cout << "[A] Anterior | [D] Siguiente | [S] Salir";

		tecla = _getch();
		if (tecla == 'A' || tecla == 'a') {
			if (pagina > 0) pagina--;
		}
		else if (tecla == 'D' || tecla == 'd') {
			if (end < total) pagina++;
		}
		else if (tecla == 'S' || tecla == 's') {
			break;
		}

	} while (true);
}

// ---------------- QUICKSORT PARA LOS GENEROS DE LAS RESERVAS DE DVDs ----------------
int partition(vector<Reserva>& v, int low, int high) {
	string pivot = v[high].getGenero();
	int i = low - 1;

	for (int j = low; j < high; ++j) {
		if (v[j].getGenero() <= pivot) {
			++i;
			swap(v[i], v[j]);
		}
	}
	swap(v[i + 1], v[high]);
	return i + 1;
}

void quickSort(vector<Reserva>& v, int low, int high) {
	if (low < high) {
		int pi = partition(v, low, high);
		quickSort(v, low, pi - 1);
		quickSort(v, pi + 1, high);
	}
}
void ordenarReservasDVDs_Quick() {
	NodoReserva<Reserva>* actual = listaReservasDVDs.getCabeza();
	vector<Reserva> reservas;

	while (actual) {
		reservas.push_back(actual->reserva);
		actual = actual->siguiente;
	}

	if (reservas.empty()) {
		ocultarCursor();
		backgroundColor("#a7b3db");
		textColor("#000000");
		posicion(51, 11); cout << "|.......... RESERVAS DE DVDs ORDENADAS POR GENERO (Quick) ..........|";
		resetColor();
		textColor("#ffffff");
		posicion(47, 13); cout << "No hay reservas.";
		resetColor();
		Sleep(numRandom() * 600);
		return;
	}

	quickSort(reservas, 0, reservas.size() - 1);

	const int porPagina = 20;
	int pagina = 0, total = reservas.size();
	char tecla;

	do {
		//limpia area
		for (int y = 13; y <= 35; ++y) {
			posicion(47, y); 
			cout << string(79, ' ');
		}

		backgroundColor("#a7b3db");
		textColor("#000000");
		posicion(51, 11); cout << "|.......... RESERVAS DE DVDs ORDENADAS POR GENERO (Quick) ..........|";
		resetColor();

		int start = pagina * porPagina, end = min(start + porPagina, total);
		int y = 13;
		for (int i = start; i < end; ++i) {
			posicion(47, y++); cout << reservas[i].toString();
		}

		posicion(47, y + 1); cout << "[A] Anterior | [D] Siguiente | [S] Salir";

		tecla = _getch();
		if (tecla == 'A' || tecla == 'a') {
			if (pagina > 0) pagina--;
		}
		else if (tecla == 'D' || tecla == 'd') {
			if (end < total) pagina++;
		}
		else if (tecla == 'S' || tecla == 's') {
			break;
		}

	} while (true);
}

// ---------------- HEAPSORT PARA LOS IDs DE LAS RESERVAS DE LIBROS ----------------
void heapify(vector<Reserva>& v, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && v[l].getIdRecurso() > v[largest].getIdRecurso())
		largest = l;

	if (r < n && v[r].getIdRecurso() > v[largest].getIdRecurso())
		largest = r;

	if (largest != i) {
		swap(v[i], v[largest]);
		heapify(v, n, largest);
	}
}

void heapSort(vector<Reserva>& v) {
	int n = v.size();

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i);

	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}

void ordenarReservasLibros_Heap() {
	NodoReserva<Reserva>* actual = listaReservasLibros.getCabeza();
	vector<Reserva> reservas;

	while (actual) {
		reservas.push_back(actual->reserva);
		actual = actual->siguiente;
	}

	if (reservas.empty()) {
		ocultarCursor();
		backgroundColor("#e7d262");
		textColor("#000000");
		posicion(53, 11); cout << "|.......... RESERVAS DE LIBROS ORDENADAS POR IDs (Heap) ..........|";
		resetColor();
		textColor("#ffffff");
		posicion(47, 13); cout << "No hay reservas.";
		resetColor();
		Sleep(numRandom() * 600);
		return;
	}

	heapSort(reservas); 

	const int porPagina = 20;
	int pagina = 0, total = reservas.size();
	char tecla;

	do {
		for (int y = 13; y <= 35; ++y) {
			posicion(47, y); cout << string(79, ' ');
		}

		backgroundColor("#e7d262");
		textColor("#000000");
		posicion(53, 11); cout << "|.......... RESERVAS DE LIBROS ORDENADAS POR IDs (Heap) ..........|";
		resetColor();

		int start = pagina * porPagina, end = min(start + porPagina, total);
		int y = 13;
		for (int i = start; i < end; ++i) {
			posicion(47, y++); cout << reservas[i].toString();
		}

		posicion(47, y + 1); cout << "[A] Anterior | [D] Siguiente | [S] Salir";

		tecla = _getch();
		if (tecla == 'A' || tecla == 'a') {
			if (pagina > 0) pagina--;
		}
		else if (tecla == 'D' || tecla == 'd') {
			if (end < total) pagina++;
		}
		else if (tecla == 'S' || tecla == 's') {
			break;
		}

	} while (true);
}
