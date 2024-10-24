#pragma once

#include "GlobalVars.h"
#include "tabulate/table.hpp"
using namespace tabulate;

Table plantillaTablaLibros();
Table plantillaTablaPrestamos();

Table generarTablaPrestamos(NodoPrestamoLibroUsuario* lista);
Table generarTablaLibros(NodoLibro* lista);
