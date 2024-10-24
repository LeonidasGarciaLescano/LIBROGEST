#include "Entidades.h"

NodoLibro::NodoLibro() {
	this->sgte = NULL;
}

NodoLibro::NodoLibro(string isbn, string titulo, string autor, string genero, int stockDisponible, int stockTotal) {
	this->isbn = isbn;
	this->titulo = titulo;
	this->autor = autor;
	this->genero = genero;
	this->stockDisponible = stockDisponible;
	this->stockTotal = stockTotal;
	this->sgte = NULL;
}

//VALIDA SI EL NODO ESTA APTO PARA REGISTRO EN LA BD
bool NodoLibro::validarRegistro() {
	trimCampos();
	if (validarIsbn() &&
		validarTitulo() &&
		validarAutor() &&
		validarGenero() &&
		validarStockDisponible() &&
		validarStockTotal()) return true;
	return false;
} 

void NodoLibro::trimCampos() {
	isbn = trim(isbn);
	titulo = trim(titulo);
	autor = trim(autor);
	genero = trim(genero);
}

bool NodoLibro::validarGenero() {
	if (this->genero == "Ciencia ficcion" ||
		this->genero == "Fantasia" ||
		this->genero == "Misterio" ||
		this->genero == "Romance" ||
		this->genero == "Biografia" ||
		this->genero == "Horror") return true;
	errorGlobal = "Genero no valido";
	return false;
}

bool NodoLibro::validarIsbn() {
	if (this->isbn.size() == 10) if (validarSoloDigitosEnCadena(this->isbn)) return true; 
	errorGlobal = "ISBN no valido";
	return false;
}

bool NodoLibro::validarTitulo() {
	if (!validarSoloEspaciosEnBlanco(this->titulo)) if (!validarSoloDigitosEnCadena(this->titulo)) return true;
	errorGlobal = "Titulo no valido";
	return false;
}

bool NodoLibro::validarAutor() {
	if (!validarSoloEspaciosEnBlanco(this->autor)) if (!validarSoloDigitosEnCadena(this->autor)) return true;
	errorGlobal = "Autor no valido";
	return false;
}

bool NodoLibro::validarStockDisponible() {
	if (stockDisponible > 0) return true;
	errorGlobal = "Stock disponible no valido";
	return false;
}

bool NodoLibro::validarStockTotal() {
	if (stockTotal > 0) return true;
	errorGlobal = "Stock total no valido";
	return false;
}

//Métodos estaticos

bool NodoLibro::validarGenero(string genero) {
	if (genero == "Ciencia ficcion" ||
		genero == "Fantasia" ||
		genero == "Misterio" ||
		genero == "Romance" ||
		genero == "Biografia" ||
		genero == "Horror") return true;
	errorGlobal = "Genero no valido";
	return false;
}

bool NodoLibro::validarIsbn(string isbn) {
	if (isbn.size() == 10) if (validarSoloDigitosEnCadena(isbn)) return true;
	errorGlobal = "ISBN no valido";
	return false;
}

bool NodoLibro::validarTitulo(string titulo) {
	if (!validarSoloEspaciosEnBlanco(titulo)) return true;
	errorGlobal = "Titulo no valido";
	return false;
}

bool NodoLibro::validarAutor(string autor) {
	if (!validarSoloEspaciosEnBlanco(autor)) return true;
	errorGlobal = "Autor no valido";
	return false;
}

bool NodoLibro::validarStockDisponible(int stockDisponible) {
	if (stockDisponible > 0) return true;
	errorGlobal = "Stock disponible no valido";
	return false;
}

bool NodoLibro::validarStockTotal(int stockTotal) {
	if (stockTotal > 0) return true;
	errorGlobal = "Stock total no valido";
	return false;
}