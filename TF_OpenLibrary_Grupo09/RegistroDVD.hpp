#pragma once
#include "DVDAVL.hpp"
#include "FigurasMenu.hpp"
#include <ctime>

using namespace std;

template <typename T>
class RegistroDVD {
private:
    DVDAVL<DVD> arbolDVDs;

public:

    // USO DE 2 LAMBDAS AQUI TAMBIEN
    RegistroDVD()
        : arbolDVDs(
            // LAMBDA #1: compara dos DVDs por ID
            [](DVD a, DVD b) { if (a.getId() == b.getId()) return 0; return a.getId() < b.getId() ? -1 : 1; },
            // LAMBDA #2: procesa cada DVD (lo muestra)
            [](DVD dvd) { cout << dvd.toString() << endl; }
        ) {
    }

    ~RegistroDVD() {}

    DVDAVL<DVD>& getArbol() { return arbolDVDs; }

    // DATASET - GENERADOR DE DVDs

    void generarDVDs(int cantidad = 100) {
        string titulos[] = { "Matrix", "Avatar", "Gladiator", "Titanic", "Godzilla",
                             "Rocky", "Rambo", "Shrek", "MadMax", "Blade" };
        string directores[] = { "Cameron", "Nolan", "Spielberg", "Scott", "Jackson" };
        string generos[] = { "Accion", "Drama", "SciFi", "Historia", "Comedia" };

        srand(time(nullptr)); 

        // Reinicia ID si quieres empezar desde DV-0001 cada vez:
        DVD::idCounter = 0;

        // Reinicio del arbol - USO DE 2 LAMBDAS IGUALES QUE EL COSNTRUCTOR

        arbolDVDs = DVDAVL<DVD>(
            // LAMBDA #1: compara dos DVDs por ID
            [](DVD a, DVD b) {
                if (a.getId() == b.getId()) return 0;
                return a.getId() < b.getId() ? -1 : 1;
            },
            // LAMBDA #2: procesa cada DVD (lo muestra)
            [](DVD dvd) { cout << dvd.toString() << endl; }
        );

        for (int i = 0; i < cantidad; ++i) {
            string titulo = titulos[rand() % 10];
            string director = directores[rand() % 5];
            string genero = generos[rand() % 5];
            int stock = rand() % 30 + 1;

            DVD dvd(titulo, director, genero, stock);
            arbolDVDs.insertarDVD(dvd);
        }

        ocultarCursor();
        textColor("#07e092");
        posicion(50, 15); cout << cantidad << " DVDs generados!";
        resetColor();
        Sleep(1000);
    }

    // Sistema de paginacion para los libros
    void mostrarDVDs() {
        vector<DVD> dvds;
        arbolDVDs.enOrdenVector(dvds);

        if (dvds.empty()) {
            ocultarCursor();
            backgroundColor("#5afffc");
            textColor("#000000");
            posicion(63, 11); cout << "|.......... LISTA DE DVDs ..........|";
            resetColor();
            textColor("#ffffff");
            posicion(47, 13); cout << "No hay reservas.";
            resetColor();
            Sleep(numRandom() * 600);
            return;
        }

        const int porPagina = 20;
        int pagina = 0;
        int total = dvds.size();
        char tecla;

        do {
            ocultarCursor();

            //Limpia area
            for (int y = 13; y <= 35; ++y) {
                posicion(47, y);
                cout << string(79, ' ');
            }

            backgroundColor("#5afffc");
            textColor("#000000");
            posicion(63, 11); cout << "|.......... LISTA DE DVDs ..........|";
            resetColor();

            int start = pagina * porPagina;
            int end = min(start + porPagina, total);

            int y = 13;
            for (int i = start; i < end; ++i) {
                posicion(47, y++);
                cout << dvds[i].toString();
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

    void buscarDVD() {
        string id;
        backgroundColor("#ffd795");
        textColor("#000000");
        posicion(63, 11); cout << "|.......... BUSCAR DVD ..........|";
        resetColor();

        textColor("#ffffff");
        posicion(47, 13); cout << "Ingrese el ID completo del DVD. Ejem (DV-0001)";
        posicion(47, 15); cout << "Ingresar ID: ";
        getline(cin >> ws, id);

        DVD* encontrado = arbolDVDs.buscarPorId(id);

        if (!encontrado) {
            ocultarCursor();
            textColor("#fa6f09");
            posicion(63, 17); cout << "DVD no encontrado.";
            Sleep(numRandom() * 400);
            return;
        }
        else {
            ocultarCursor();
            textColor("#d0ff3f");
            posicion(47, 17); cout << "El DVD que estas buscando es el siguiente:";
            textColor("#ffffff");
            posicion(47, 19); cout << encontrado->toString();
            _getch();
        }
    }

};
