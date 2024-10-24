#include "Entidades.h"

NodoListaNegra::NodoListaNegra() {
	this->sgte = NULL;
}

NodoListaNegra::NodoListaNegra(int idListaNegra, string nombres, string dni) {
	this->idListaNegra = idListaNegra;
	this->nombres = nombres;
	this->dni = dni;
	this->sgte = NULL;
}
