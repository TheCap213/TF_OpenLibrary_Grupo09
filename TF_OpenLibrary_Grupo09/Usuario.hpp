#pragma once
#include <string>
using namespace std; 

enum Rol {
	USER, 
	ADMIN
};

class Usuario {
private: 
	string dni;
	string nombre; 
	int edad; 
	string correo; 
	string password; 
	Rol rol;

public: 

	Usuario() {}

	Usuario(string dni, string nombre, int edad, string correo, string password, Rol rol) {
		this->dni = dni; 
		this->nombre = nombre; 
		this->edad = edad; 
		this->correo = correo; 
		this->password = password; 
		this->rol = rol;
	}

	string serializar() {
		return dni + "," + nombre + "," + to_string(edad) + "," + correo + "," + password + "," + to_string(rol);
	}

	void deserializar(string linea) {
		size_t pos = 0;
		int campo = 0; 
		string tokem;

		while ((pos = linea.find(',')) != string::npos) {
			tokem = linea.substr(0, pos);
			if (campo == 0) dni = tokem;
			else if (campo == 1) nombre = tokem;
			else if (campo == 2) edad = stoi(tokem);
			else if (campo == 3) correo = tokem;
			else if (campo == 4) password = tokem;
			else if (campo == 5) rol = static_cast<Rol>(stoi(tokem));
			linea.erase(0, pos + 1);
			campo++;
		}	
	}

	string getDni() { return dni; }
	string getNombre() { return nombre; }
	int getEdad() { return edad; }
	string getCorreo() { return correo; }
	string getPassword() { return password; }
	Rol getRol() { return rol; }

};