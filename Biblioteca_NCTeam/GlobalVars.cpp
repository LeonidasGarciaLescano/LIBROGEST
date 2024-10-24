#include "GlobalVars.h"

Conexion conectar() {
    try {
        sql::mysql::MySQL_Driver* driver;
        driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://autorack.proxy.rlwy.net:52141", "root", "CkizulelGYEWmOANSxMNudMttSYVGANi");
        con->setSchema("railway");
        return con;

    }
    catch (sql::SQLException&) {
        sql::Connection* con = NULL;
        return con;
    }
}

Conexion openConexion = conectar();

void desconectar(Conexion& con) {
    delete con;
}

string errorGlobal = "";

string mostrarErrorGlobal() {
    string error = errorGlobal;
    errorGlobal = "";
    return error;
}

void definirDrivers() {
    libroDriver = new LibroRepositorio(openConexion);
    prestamoDriver = new PrestamoRepositorio(openConexion);
    usuarioDriver = new UsuarioRepositorio(openConexion);
    listaNegraDriver = new ListaNegraRepositorio(openConexion);
}

LibroRepositorio* libroDriver = NULL;
PrestamoRepositorio* prestamoDriver = NULL;
UsuarioRepositorio* usuarioDriver = NULL;
ListaNegraRepositorio* listaNegraDriver = NULL;