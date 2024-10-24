#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include <string>
#include <iostream>
using namespace std;

typedef sql::Connection* Conexion;
typedef sql::ResultSet* Respuesta;
typedef sql::Statement* Consulta;
typedef sql::PreparedStatement* PSTMT;

template<typename T, typename I>
class IConectar {
protected:
	Conexion conexion;
	string insertQuery, searchIDQuery, searchAllQuery, updateRowQuery, deleteRowQuery;

public:

	IConectar(Conexion& openConexion) {
		this->conexion = openConexion;
	}

	virtual bool registrar(T* filaNueva) const = 0;
	virtual T* obtenerPorId(I id) const = 0;
	virtual T* obtenerTodos() const = 0;
	virtual bool actualizar(T* filaActualizada) const = 0;
	virtual bool eliminar(I id) const = 0;
};

