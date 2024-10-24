#pragma once

#include "Repositorios.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "CommonFunctions.h"

//FORWARD DECLARATION DE LAS CLASES (PARA EVITAR ERRORES DE COMPILACION)
class LibroRepositorio;
class PrestamoRepositorio;
class UsuarioRepositorio;
class ListaNegraRepositorio;

//ERROR GLOBAL
extern string errorGlobal;
string mostrarErrorGlobal();

//Tipos personalizados
typedef sql::Connection* Conexion;
typedef sql::ResultSet* Respuesta;
typedef sql::Statement* Consulta;
typedef sql::PreparedStatement* PSTMT;

//Conexion con la base de datos
extern Conexion conectar();
extern Conexion openConexion;
extern void desconectar(Conexion& openConexion);

//FUNCIÓN DE INICIALIZACION DE LOS DRIVERS DE REPOSITORIO
void definirDrivers();

//Repositorios instanciados
extern LibroRepositorio*libroDriver;
extern PrestamoRepositorio*prestamoDriver;
extern UsuarioRepositorio*usuarioDriver;
extern ListaNegraRepositorio*listaNegraDriver;