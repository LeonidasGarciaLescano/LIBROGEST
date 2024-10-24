#include "Entidades.h"

NodoUsuario::NodoUsuario() {
	this->sgte = NULL;
}

NodoUsuario::NodoUsuario(int idBiblio, string nombres, string numTel, string dni) {
	this->idBiblio = idBiblio;
	this->nombres = nombres;
	this->numTel = numTel;
	this->dni = dni;
	this->sgte = NULL;
}

void NodoUsuario::trimCampos() {
	nombres = trim(nombres);
	numTel = trim(numTel);
	dni = trim(dni);
}

bool NodoUsuario::validarRegistro() {
	trimCampos();
	if (validarIdBiblio() &&
		validarNombres() &&
		validarNumTel() &&
		validarDni()) 
	{
		if (usuarioDriver->obtenerPorNombres(this->nombres) == NULL) {
			return true;
		}
		else {
			errorGlobal = "El usuario ya existe en la BD";
		}
	}
	return false;
}


//METODOS PROPIOS
bool NodoUsuario::validarIdBiblio() {
	if (NodoPrestamo::validarIdBiblio(this->idBiblio)) {
		return true;
	}
	errorGlobal = "Id de biblioteca no valido";
	return false;

}

bool NodoUsuario::validarNombres() {
	if (NodoLibro::validarAutor(this->nombres)) {
		return true;
	}
	errorGlobal = "Nombres no validos";
	return false;
}

bool NodoUsuario::validarNumTel() {
	if (this->numTel.size() == 15 || this->numTel.size() == 9) if (validarSoloDigitosEnCadena(this->numTel)) return true;
	errorGlobal = "El numero de telefono debe poseer entre 9 y 15 caracteres.";
	return false;
}

bool NodoUsuario::validarDni() {
	if (this->dni.size() == 8) if (validarSoloDigitosEnCadena(this->dni)) return true;
	errorGlobal = "El dni ingresado tiene mas de 8 caracteres o posee caracteres invalidos";
	return false;
}

//METODOS ESTATICOS
bool NodoUsuario::validarIdBiblio(int idBiblio) {
	if (NodoPrestamo::validarIdBiblio(idBiblio)) {
		return true;
	}
	errorGlobal = "Id de biblioteca no valido";
	return false;
}

bool NodoUsuario::validarNombres(string nombres) {
	if (NodoLibro::validarAutor(nombres)) {
		return true;
	}
	errorGlobal = "Nombres no validos";
	return false;
}

bool NodoUsuario::validarNumTel(string numTel) {
	if (numTel.size() == 15 || numTel.size() == 9) if (validarSoloDigitosEnCadena(numTel)) return true;
	errorGlobal = "El numero de telefono debe poseer entre 9 y 15 caracteres.";
	return false;
}

bool NodoUsuario::validarDni(string dni) {
	if (dni.size() == 8) if (validarSoloDigitosEnCadena(dni)) return true;
	errorGlobal = "El dni ingresado tiene mas de 8 caracteres o posee caracteres invalidos";
	return false;
}