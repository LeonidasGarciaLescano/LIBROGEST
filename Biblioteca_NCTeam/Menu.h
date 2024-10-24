#pragma once

#include "GlobalVars.h"
#include "Usuario.h"
#include "Prestamo.h"
#include "Libro.h"
#include "OperacionesNodo.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;

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

// FUNCIONES LÓGICAS
void registroDeLibros();

void seleccionGenero(int& opcionGeneroSeleccionada);
void registroUsuario(NodoLibro*& libro);
void confirmacionDatos(NodoLibro*& libro, NodoUsuario*& usuario);
void prestamoDeLibros(NodoLibro*& libro);
void busquedaDeLibros();


void devolucionDeLibros();
void historialDePrestamos();

void nuevoUsuario();

void estadisticasDePrestamos(); //xd

void menuPrincipal();

// FUNCIONES TÉCNICAS
void limpiarEspacio(int x, int y, int ancho, int alto);
void dibujarCuadro(int x, int y, int ancho, int alto, bool selected);
void tamanoConsola();
void setConsoleColor(int text, int background);
void gotoxy(int x, int y);
int menu();