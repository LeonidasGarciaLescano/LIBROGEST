#include "Entidades.h"

NodoPrestamoLibroUsuario::NodoPrestamoLibroUsuario() {
	this->sgte = NULL;
}

NodoPrestamoLibroUsuario::NodoPrestamoLibroUsuario(int idPrestamo, string isbn, string titulo, int idBiblio, string nombres, string contacto, string fechaPrestamo, string fechaDevolucion) {
	this->idPrestamo = idPrestamo;
	this->isbn = isbn;
	this->titulo = titulo;
	this->idBiblio = idBiblio;
	this->nombres = nombres;
	this->contacto = contacto;
	this->fechaPrestamo = fechaPrestamo;
	this->fechaDevolucion = fechaDevolucion;
	this->sgte = NULL;
}