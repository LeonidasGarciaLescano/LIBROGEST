#pragma once 

#include "GlobalVars.h"
#include <string>
#include <chrono>
using namespace std;

bool registrarPrestamo(NodoLibro*& libro, NodoUsuario*& usuario);
bool eliminarPrestamo(NodoPrestamo*& prestamo);