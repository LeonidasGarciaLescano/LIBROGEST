#include "Libro.h"

bool registrarLibro(NodoLibro* &libro) {

	bool result = false;

	if (libro->validarRegistro()) { 
		result = libroDriver->registrar(libro);
		delete libro;
		return result;
	}
	return result;
}

bool aumentarStockLibro(NodoLibro* & libro) {

	bool result = false;

	if (libro->validarIsbn()) {
		result = libroDriver->aumentarStockPorIsbn(libro->isbn);
		delete libro;
		return result;
	}
	return result;
}

NodoLibro* buscarPorTitulo(string titulo, NodoLibro*& libros) {

	NodoLibro* librosEncontrados = NULL;

	if (NodoLibro::validarTitulo(titulo)) {
		NodoLibro* t = libros;
		while (t != NULL) {

			if (t->titulo == titulo) {
				NodoLibro* coincidencia = new NodoLibro(
					t->isbn,
					t->titulo,
					t->autor,
					t->genero,
					t->stockDisponible,
					t->stockTotal);

				if (librosEncontrados != NULL) {
					coincidencia->sgte = librosEncontrados;
					librosEncontrados = coincidencia;
				}
				else {
					librosEncontrados = coincidencia;
				}
				return librosEncontrados;
			}

			t = t->sgte;
		}

	}
	errorGlobal = "Ningun titulo coincide con el ingresado";
	return NULL;
}

//BUENO IA NO TENGO Q EXPLICAR ESTOS PQ SON IGUALES AL DE TITULO
NodoLibro* buscarPorAutor(string autor, NodoLibro*& libros) {

	NodoLibro* librosEncontrados = NULL;

	if (NodoLibro::validarAutor(autor)) {
		NodoLibro* t = libros;
		while (t != NULL) {

			if (t->autor == autor) {
				NodoLibro* coincidencia = new NodoLibro(
					t->isbn,
					t->titulo,
					t->autor,
					t->genero,
					t->stockDisponible,
					t->stockTotal);

				if (librosEncontrados != NULL) {
					coincidencia->sgte = librosEncontrados;
					librosEncontrados = coincidencia;
				}
				else {
					librosEncontrados = coincidencia;
				}
			}

			t = t->sgte;
		}

		return librosEncontrados;

	}
	return NULL;
}

NodoLibro* buscarPorGenero(string genero, NodoLibro*& libros) {
	NodoLibro* librosEncontrados = NULL;

	if (NodoLibro::validarGenero(genero)) {
		NodoLibro* t = libros;
		while (t != NULL) {

			if (t->genero == genero) {
				NodoLibro* coincidencia = new NodoLibro(
					t->isbn,
					t->titulo,
					t->autor,
					t->genero,
					t->stockDisponible,
					t->stockTotal);

				if (librosEncontrados != NULL) {
					coincidencia->sgte = librosEncontrados;
					librosEncontrados = coincidencia;
				}
				else {
					librosEncontrados = coincidencia;
				}
			}

			t = t->sgte;
		}

		return librosEncontrados;

	}
	return NULL;
}

NodoLibro* buscarPorISBN(string isbn, NodoLibro*& libros) {
	NodoLibro* librosEncontrados = NULL;

	if (NodoLibro::validarIsbn(isbn)) {
		NodoLibro* t = libros;
		while (t != NULL) {

			if (t->isbn == isbn) {
				NodoLibro* coincidencia = new NodoLibro(
					t->isbn,
					t->titulo,
					t->autor,
					t->genero,
					t->stockDisponible,
					t->stockTotal);

				if (librosEncontrados != NULL) {
					coincidencia->sgte = librosEncontrados;
					librosEncontrados = coincidencia;
				}
				else {
					librosEncontrados = coincidencia;
				}
				return librosEncontrados;
			}

			t = t->sgte;
		}

	}
	return NULL;
}