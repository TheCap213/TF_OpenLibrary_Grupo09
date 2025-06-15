#pragma once
#include "Colores.hpp"


// MENU PRINCIPAL
void tituloOpenLibrary(int x, int y, const string& hexcolor) {
    textColor(hexcolor); 
    SetConsoleOutputCP(CP_UTF8); 

    const char* titulo[] = {

        u8"██╗ ██╗       ██████╗ ██████╗ ███████╗███╗   ██╗    ██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗   ██╗      ██╗ ██╗",
        u8"╚██╗╚██╗     ██╔═══██╗██╔══██╗██╔════╝████╗  ██║    ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝     ██╔╝██╔╝",
        u8" ╚██╗╚██╗    ██║   ██║██████╔╝█████╗  ██╔██╗ ██║    ██║     ██║██████╔╝██████╔╝███████║██████╔╝ ╚████╔╝     ██╔╝██╔╝ ",
        u8" ██╔╝██╔╝    ██║   ██║██╔═══╝ ██╔══╝  ██║╚██╗██║    ██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗  ╚██╔╝      ╚██╗╚██╗ ",
        u8"██╔╝██╔╝     ╚██████╔╝██║     ███████╗██║ ╚████║    ███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║   ██║        ╚██╗╚██╗",
        u8"╚═╝ ╚═╝       ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═══╝    ╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝         ╚═╝ ╚═╝"

    };

    for (int i = 0; i < 6; ++i) {
        posicion(x, y + i);
        cout << titulo[i];
    }

    resetColor();
}

void birrete(int x, int y) {
    textColor("#07e092"); 
    SetConsoleOutputCP(CP_UTF8); 
    const char* simbolo[] = {
        u8"   _.-'`'-._",
        u8".-'    _    '-.",
        u8" `-.__  `\\_.-'",
        u8"   |  `-``\\|",
        u8"   `-.....-|",
        u8"           |",
        u8"           #"
    };

    for (int i = 0; i < 7; ++i) {
        posicion(x, y + i); 
        cout << simbolo[i];
    }
    resetColor();
}

void libroMenu(int x, int y) {
    textColor("#07e092");
    SetConsoleOutputCP(CP_UTF8);
    const char* simbolo[] = {
    u8"                .-~~~~~~~~~-._       _.-~~~~~~~~~-.",
    u8"            __.'              ~.   .~              `.__",
    u8"          .'//                  \\./                  \\\\`.",
    u8"        .'//                     |                     \\\\`.",
    u8"      .'// .-~\"\"\"\"\"\"\"~~~~-._     |     _,-~~~~\"\"\"\"\"\"\"~-. \\\\`.",
    u8"    .'//.-\"                 `-.  |  .-'                 \"-.\\\\`.",
    u8"  .'//______.============-..   \\ | /   ..-============.______\\\\`.",
    u8".'______________________________\\|/______________________________`."
    };

    for (int i = 0; i < 8; ++i) {
        posicion(x, y + i);
        cout << simbolo[i];
    }
    resetColor();
}

void tituloMenu(int x, int y) {
    textColor("#07e092");
    SetConsoleOutputCP(CP_UTF8);

    const char* titulo[] = {

        u8"███╗   ███╗███████╗███╗   ██╗██╗   ██╗", 
        u8"████╗ ████║██╔════╝████╗  ██║██║   ██║", 
        u8"██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║", 
        u8"██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║", 
        u8"██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝", 
        u8"╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ "

    };
    for (int i = 0; i < 6; ++i) {
        posicion(x, y + i);
        cout << titulo[i];
    }

    resetColor();
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

void dibujarLineaVertical(int x, int yInicio, int yFin, const string& hexColor) {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO infoConsola;
    GetConsoleScreenBufferInfo(consola, &infoConsola);

    string bloque = u8"█"; // O cualquier otro carácter que desees
    textColor(hexColor);

    // Dibujar la línea vertical
    for (int y = yInicio; y <= yFin; ++y) {
        COORD coordenada = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(consola, coordenada);
        cout << bloque;
    }

    resetColor();
}

void dibujarLineaHorizontal(int y, int xInicio, int xFin, const string& hexColor) {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO infoConsola;
    GetConsoleScreenBufferInfo(consola, &infoConsola);

    string bloque = u8"█"; // O cualquier otro carácter que desees
    textColor(hexColor);

    // Dibujar la línea horizontal
    for (int x = xInicio; x <= xFin; ++x) {
        COORD coordenada = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(consola, coordenada);
        cout << bloque;
    }

    resetColor();
}

void tituloRegistro(int x, int y) {
    textColor("#dbea2c");
    SetConsoleOutputCP(CP_UTF8);

    const char* titulo[] = {

        u8"██████╗ ███████╗ ██████╗ ██╗███████╗████████╗██████╗  ██████╗ ",
        u8"██╔══██╗██╔════╝██╔════╝ ██║██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗",
        u8"██████╔╝█████╗  ██║  ███╗██║███████╗   ██║   ██████╔╝██║   ██║",
        u8"██╔══██╗██╔══╝  ██║   ██║██║╚════██║   ██║   ██╔══██╗██║   ██║",
        u8"██║  ██║███████╗╚██████╔╝██║███████║   ██║   ██║  ██║╚██████╔╝",
        u8"╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ "

    };
    for (int i = 0; i < 6; ++i) {
        posicion(x, y + i);
        cout << titulo[i];
    }

    resetColor();
}

void tituloLogin(int x, int y) {
    textColor("#62e6e8");
    SetConsoleOutputCP(CP_UTF8);

    const char* titulo[] = {

        u8"██╗███╗   ██╗██╗ ██████╗██╗ █████╗ ██████╗     ███████╗███████╗███████╗██╗ ██████╗ ███╗   ██╗",
        u8"██║████╗  ██║██║██╔════╝██║██╔══██╗██╔══██╗    ██╔════╝██╔════╝██╔════╝██║██╔═══██╗████╗  ██║",
        u8"██║██╔██╗ ██║██║██║     ██║███████║██████╔╝    ███████╗█████╗  ███████╗██║██║   ██║██╔██╗ ██║",
        u8"██║██║╚██╗██║██║██║     ██║██╔══██║██╔══██╗    ╚════██║██╔══╝  ╚════██║██║██║   ██║██║╚██╗██║",
        u8"██║██║ ╚████║██║╚██████╗██║██║  ██║██║  ██║    ███████║███████╗███████║██║╚██████╔╝██║ ╚████║",
        u8"╚═╝╚═╝  ╚═══╝╚═╝ ╚═════╝╚═╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚══════╝╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝"

    };
    for (int i = 0; i < 6; ++i) {
        posicion(x, y + i);
        cout << titulo[i];
    }

    resetColor();
}