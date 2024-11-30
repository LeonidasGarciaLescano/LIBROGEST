#include "Repositorios.h"
#include "GlobalVars.h"
#include "menu.h"
#include "Libro.h"
#include "Tabular.h"
#include "Usuario.h"
#include "Prestamo.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace tabulate;

int main() {

    definirDrivers();

    if (openConexion != NULL) {
        menu();
    }
    else cout << "No se pudo establecer la conexion inicial con la base de datos" << endl;
    
    system("pause");
}