#pragma once

#include "GlobalVars.h"
#include "IConectar.h"
#include "Entidades.h"
#include "Repositorios.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include <string>

class LibroRepositorio;
class PrestamoRepositorio;
class UsuarioRepositorio;
class ListaNegraRepositorio;

struct NodoLibro;
struct NodoUsuario;
struct NodoPrestamo;
struct NodoListaNegra;
struct NodoPrestamoLibroUsuario;

class LibroRepositorio : public IConectar<NodoLibro, string> {
private:
	string updateIncreaseStockQuery;
	string updateDecreaseStockQuery;
	string searchTitleQuery;
	string searchAuthorQuery;
	string searchGenreQuery;

public:
	LibroRepositorio(Conexion openConexion);
	bool registrar(NodoLibro* filaNueva) const override;
	NodoLibro* obtenerPorId(string isbn) const override;
	NodoLibro* obtenerTodos() const override;
	virtual bool actualizar(NodoLibro* filaActualizada) const override;
	virtual bool eliminar(string id) const override;
	bool aumentarStockPorIsbn(string isbn);
	bool reducirStockDisponiblePorIsbn(string isbn);
	NodoLibro* obtenerPorTitulo(string titulo);
	NodoLibro* obtenerPorAutor(string autor);
	NodoLibro* obtenerPorGenero(string genero);
};

class PrestamoRepositorio : public IConectar<NodoPrestamo, int> {
private:
	string getQuantityBorrowsQuery;
	string searchHibridPrestamoUsuarioLibro;

public:
	PrestamoRepositorio(Conexion openConexion);
	bool registrar(NodoPrestamo* filaNueva) const override;
	NodoPrestamo* obtenerPorId(int id) const override;
	NodoPrestamo* obtenerTodos() const override;
	bool actualizar(NodoPrestamo* filaActualizada) const override;
	bool eliminar(int id) const override;
	int obtenerCantidadPrestamos(int id);
	NodoPrestamoLibroUsuario* obtenerHistorialPrestamos();
};

class UsuarioRepositorio : public IConectar<NodoUsuario, int> {
private:
	string searchNameQuery;

public:
	UsuarioRepositorio(Conexion openConexion);
	bool registrar(NodoUsuario* filaNueva) const override;
	NodoUsuario* obtenerPorId(int id) const override;
	NodoUsuario* obtenerTodos() const override;
	NodoUsuario* obtenerPorNombres(string nombres);
	bool actualizar(NodoUsuario* filaActualizada) const override;
	bool eliminar(int id) const override;
};

class ListaNegraRepositorio : public IConectar<NodoListaNegra, int> {
private:
	string searchDNIQuery;

public:
	ListaNegraRepositorio(Conexion openConexion);
	bool registrar(NodoListaNegra* filaNueva) const override;
	NodoListaNegra* obtenerPorId(int id) const override;
	NodoListaNegra* obtenerTodos() const override;
	bool actualizar(NodoListaNegra* filaActualizada) const override;
	bool eliminar(int id) const override;
	bool verificarBaneado(string dni);
};