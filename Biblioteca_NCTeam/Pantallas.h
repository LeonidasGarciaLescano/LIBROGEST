#pragma once

#include "GlobalVars.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <sstream>

using namespace std;

// FUNCIONES TÉCNICAS
void limpiarEspacio(int x, int y, int ancho, int alto);
void dibujarCuadro(int x, int y, int ancho, int alto, bool selected);
void tamanoConsola();
void setConsoleColor(int text, int background);
void gotoxy(int x, int y);

// PANTALLAS
void pantallaPrestamoDeLibros(int opcionSeleccionada);
void pantallaRegistroDeLibros();
void pantallaDevolucionDeLibros(int opcionSeleccionada);
void pantallaHistorialDePrestamos();
void pantallaBusquedaDeLibros(int opcionSeleccionada, string generoSeleccionado);
void pantallaPrincipal(int opcionSeleccionada);
void pantallaRegistroUsuario(int opcionSeleccionada);
void pantallaNuevoUsuario(int opcionSeleccionada);
void pantallaConfirmacionDatos();