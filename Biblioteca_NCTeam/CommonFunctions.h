#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <algorithm>
#include <regex>
#include <chrono>
using namespace std;

string trim(const string& str);
bool validarSoloDigitosEnCadena(const string& str);
bool validarSoloEspaciosEnBlanco(const string& str);
bool validarFecha(const string& fecha);
string obtenerFechaDevolucion(int dias);
string obtenerFechaActual();
bool esFechaMayor(string fecha1, string fecha2);