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

    NodoPrestamo* prestamo = new NodoPrestamo();
    prestamo->idPrestamo = 39;

    if (openConexion != NULL) {
        menu();
    }
    else cout << "Oh sielos, la base de datos NOOOOOOOO!" << endl;

    system("pause");
}