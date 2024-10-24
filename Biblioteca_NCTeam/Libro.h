#pragma once

#include "GlobalVars.h"
#include <string>
using namespace std;

bool registrarLibro(NodoLibro*& libro);
bool aumentarStockLibro(NodoLibro*& libro);

NodoLibro* buscarPorTitulo(string titulo, NodoLibro*& libros);
NodoLibro* buscarPorAutor(string autor, NodoLibro*& libros);
NodoLibro* buscarPorGenero(string genero, NodoLibro*& libros);
NodoLibro* buscarPorISBN(string isbn, NodoLibro*& libros);