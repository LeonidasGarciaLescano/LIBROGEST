#include "Entidades.h"

NodoPrestamo::NodoPrestamo() {
	this->sgte = NULL;
}

NodoPrestamo::NodoPrestamo(int idPrestamo, string isbn, int idBiblio, string fechaPrestamo, string fechaDevolucion) {
	this->idPrestamo = idPrestamo;
	this->isbn = isbn;
	this->idBiblio = idBiblio;
	this->fechaPrestamo = fechaPrestamo;
	this->fechaDevolucion = fechaDevolucion;
	this->sgte = NULL;
}

//VALIDA SI EL NODO ESTA APTO PARA SER REGISTRADO EN LA BD
bool NodoPrestamo::validarRegistro(NodoLibro* libro, NodoUsuario* usuario) {
	trimCampos();
	libro->trimCampos();
	usuario->trimCampos();
	if (validarIdPrestamo() &&
		validarIsbn() &&
		validarIdBiblio() &&
		validarFechaDevolucion()) {
		if (usuarioDriver->obtenerPorId(usuario->idBiblio) == NULL){
			errorGlobal = "El usuario no existe";
			return false;
		} else if (listaNegraDriver->verificarBaneado(usuario->dni) == true){
			errorGlobal = "El usuario esta en la lista negra";
			return false;
		} else if (prestamoDriver->obtenerCantidadPrestamos(usuario->idBiblio) >= 2){
			errorGlobal = "El usuario ya tiene 2 los prestamos";
			return false;
		} else if (libro->stockDisponible == 0){
			errorGlobal = "No hay stock disponible del libro";
			return false;
		}
		return true;
	}
	return false;
}

void NodoPrestamo::trimCampos() {
	isbn = trim(isbn);
	fechaPrestamo = trim(fechaPrestamo);
	fechaDevolucion = trim(fechaDevolucion);
}

bool NodoPrestamo::validarIdPrestamo() {
	if (this->idPrestamo > 0) return true;
	errorGlobal = "Id de prestamo no valido";
	return false;
}

bool NodoPrestamo::validarIsbn() {
	return NodoLibro::validarIsbn(this->isbn);
	errorGlobal = "ISBN no valido";
}

bool NodoPrestamo::validarIdBiblio() {
	if (this->idBiblio > 0) return true;
	errorGlobal = "Id de biblioteca no valido";
	return false;
}

bool NodoPrestamo::validarFechaPrestamo() {
	if (validarFecha(this->fechaPrestamo)) return true;
	errorGlobal = "Fecha de prestamo incorrecta o invalida";
	return false;
}

bool NodoPrestamo::validarFechaDevolucion() {
	if (validarFecha(this->fechaDevolucion)) return true;
	errorGlobal = "Fecha de devolucion incorrecta o invalida";
	return false;
}

//ESTATICOS DE VALIDACION
bool NodoPrestamo::validarIdPrestamo(int idPrestamo) {
	if (idPrestamo > 0) return true;
	errorGlobal = "Id de prestamo no valido";
	return false;
}
bool NodoPrestamo::validarIsbn(string isbn) {
	if (NodoLibro::validarIsbn(isbn)) return true;
	errorGlobal = "El isbn ingresado no es valido";
	return false;
}

bool NodoPrestamo::validarIdBiblio(int idBiblio) {
	if (idBiblio > 0) return true;
	errorGlobal = "Id de biblioteca no valido";
	return false;
}

bool NodoPrestamo::validarFechaPrestamo(string fechaPrestamo) {
	if (validarFecha(fechaPrestamo)) return true;
	errorGlobal = "Fecha de prestamo incorrecta o invalida";
	return false;
}

bool NodoPrestamo::valiarFechaDevolucion(string fechaDevolucion) {
	if (validarFecha(fechaDevolucion)) return true;
	errorGlobal = "Fecha de devolucion incorrecta o invalida";
	return false;
}