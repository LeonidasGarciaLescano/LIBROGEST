#include "tabular.h"

Table generarTablaLibros(NodoLibro* lista) {
	
	int tam = 0;
	Table tablaLibros = plantillaTablaLibros();

	while (lista != NULL) {
		tablaLibros.add_row({ lista->isbn, lista->titulo, lista->autor, lista->genero, to_string(lista->stockDisponible), to_string(lista->stockTotal) });
		lista = lista->sgte;
	}

	tablaLibros.format().width(19);

	return tablaLibros;
}

Table generarTablaPrestamos(NodoPrestamoLibroUsuario* lista) {

	int tam = 0;
	Table tablaPrestamos = plantillaTablaPrestamos();

	while (lista != NULL) {
		tablaPrestamos.add_row({ 
			to_string(lista->idPrestamo), 
			lista->isbn, 
			lista->titulo, 
			to_string(lista->idBiblio), 
			lista->nombres, 
			lista->contacto, 
			lista->fechaPrestamo, 
			lista->fechaDevolucion });
		lista = lista->sgte;
	}

	tablaPrestamos.format().width(15);

	return tablaPrestamos;
}


Table plantillaTablaLibros() {
	Table tablaLibros;

	tablaLibros.add_row({ "ISBN", "Titulo", "Autor", "Genero", "Stock Disponible", "Stock Total" });

	return tablaLibros;
}

Table plantillaTablaPrestamos() {
	Table tablaPrestamos;

	tablaPrestamos.add_row({"ID del prestamo", "ISBN", "Titulo", "ID de biblioteca", "Nombres", "Contacto", "Fecha de prestamo", "Fecha de devolución"});

	return tablaPrestamos;
}