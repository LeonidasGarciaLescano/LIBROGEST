#include "OperacionesNodo.h"

void limpiarNodoLibro(NodoLibro*& libros) {
	
	NodoLibro* t = NULL;

	while (libros != NULL) {
		t = libros;
		libros = libros->sgte;
		delete t;
	}
}

void limpiarNodoUsuario(NodoUsuario*& usuarios) {
	NodoUsuario* t = NULL;

	while (usuarios != NULL) {
		t = usuarios;
		usuarios = usuarios->sgte;
		delete t;
	}
}

void limpiarNodoPrestamo(NodoPrestamo*& prestamos) {
	NodoPrestamo* t = NULL;

	while (prestamos != NULL) {
		t = prestamos;
		prestamos = prestamos->sgte;
		delete t;
	}
}

void limpiarNodoPrestamoLibroUsuario(NodoPrestamoLibroUsuario*& prestamos) {
	NodoPrestamoLibroUsuario* t = NULL;

	while (prestamos != NULL) {
		t = prestamos;
		prestamos = prestamos->sgte;
		delete t;
	}
}