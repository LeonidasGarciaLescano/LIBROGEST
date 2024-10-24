#define _CRT_SECURE_NO_WARNINGS
#include "Prestamo.h"

bool registrarPrestamo(NodoLibro*& libro, NodoUsuario*& usuario) {
    bool result = false;

    NodoPrestamo* prestamo = new NodoPrestamo;
    prestamo->isbn = libro->isbn;
    prestamo->idBiblio = usuario->idBiblio;
    prestamo->fechaDevolucion = obtenerFechaDevolucion(25);

    if (prestamo->validarRegistro(libro, usuario)) {
        result = prestamoDriver->registrar(prestamo);
        delete libro;
        delete usuario;
        if (result == true) {
            libroDriver->reducirStockDisponiblePorIsbn(prestamo->isbn);
            delete prestamo;
            return true;
        }
        else {
            errorGlobal = "La BD no admitio esta operacion";
            delete prestamo;
            return false;
        }
    }
    delete libro;
    delete usuario;
    delete prestamo;
    return result;
}

bool eliminarPrestamo(NodoPrestamo*& prestamo) {
    if (prestamo->validarIdPrestamo()) {
        int idPrestamo = prestamo->idPrestamo;
        delete prestamo;
        prestamo = prestamoDriver->obtenerPorId(idPrestamo);
        if (prestamoDriver->eliminar(prestamo->idPrestamo)) {
            libroDriver->aumentarStockPorIsbn(prestamo->isbn);
            delete prestamo;
            return true;
        }
        else {
            errorGlobal = "La base de datos rechazo esta operacion";
            delete prestamo;
            return false;
        }
    }
    return false;
}