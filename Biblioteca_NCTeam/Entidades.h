#pragma once

#include "GlobalVars.h"
#include <string>
using namespace std;

struct NodoLibro;
struct NodoPrestamo;
struct NodoUsuario;
struct NodoListaNegra;
struct NodoPrestamoLibroUsuario;

struct NodoLibro {
	string isbn = "", titulo = "", autor = "", genero = "";
	int stockDisponible = 0, stockTotal = 0;
	NodoLibro* sgte;

	NodoLibro();
	NodoLibro(string isbn, string titulo, string autor, string genero, int stockDisponible, int stockTotal);

	//Métodos propios
	void trimCampos();
	bool validarRegistro();
	bool validarIsbn();
	bool validarTitulo();
	bool validarAutor();
	bool validarGenero();
	bool validarStockDisponible();
	bool validarStockTotal();

	//Estáticos
	static bool validarIsbn(string isbn);
	static bool validarTitulo(string titulo);
	static bool validarAutor(string autor);
	static bool validarGenero(string genero);
	static bool validarStockDisponible(int stockDisponible);
	static bool validarStockTotal(int validarStockTotal);

};

struct NodoPrestamo {
	int idPrestamo = 1, idBiblio;
	string isbn, fechaPrestamo = "2024-10-22", fechaDevolucion;
	NodoPrestamo* sgte;

	NodoPrestamo();
	NodoPrestamo(int idPrestamo, string isbn, int idBiblio, string fechaPrestamo, string fechaDevolucion);

	//METODOS PROPIOS
	void trimCampos();
	bool validarRegistro(NodoLibro* libro, NodoUsuario* usuario);
	bool validarIdPrestamo();
	bool validarIsbn();
	bool validarIdBiblio();
	bool validarFechaPrestamo();
	bool validarFechaDevolucion();

	//ESTATICOS DE VALIDACION
	static bool validarIdPrestamo(int idPrestamo);
	static bool validarIsbn(string isbn);
	static bool validarIdBiblio(int idBiblio);
	static bool validarFechaPrestamo(string fechaPrestamo);
	static bool valiarFechaDevolucion(string fechaPrestamo);

};

struct NodoUsuario {
	int idBiblio = 1;
	string nombres = "", numTel = "", dni = "";
	NodoUsuario* sgte;

	NodoUsuario();
	NodoUsuario(int idBiblio, string nombres, string numTel, string dni);

	//METODOS PROPIOS
	void trimCampos();
	bool validarRegistro();
	bool validarIdBiblio();
	bool validarNombres();
	bool validarNumTel();
	bool validarDni();

	//METODOS ESTATICOS
	static bool validarIdBiblio(int idBiblio);
	static bool validarNombres(string nombres);
	static bool validarNumTel(string numTel);
	static bool validarDni(string dni);

};

struct NodoListaNegra {
	int idListaNegra = 0;
	string nombres = "", dni = "";
	NodoListaNegra* sgte;

	NodoListaNegra();
	NodoListaNegra(int idListaNegra, string nombres, string dni);

	bool validarIdListaNegra();
	bool validarNombres();
	bool validarDni();

};

struct NodoPrestamoLibroUsuario {
	int idPrestamo, idBiblio;
	string isbn, titulo, nombres, contacto, fechaPrestamo, fechaDevolucion;
	NodoPrestamoLibroUsuario* sgte = NULL;

	NodoPrestamoLibroUsuario();
	NodoPrestamoLibroUsuario(int idPrestamo, string isbn, string titulo, int idBiblio, string nombres, string contacto, string fechaPrestamo, string fechaDevolucion);
};