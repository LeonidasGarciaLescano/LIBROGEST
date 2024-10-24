#include "Repositorios.h"

//Metodos de Prestamo
PrestamoRepositorio::PrestamoRepositorio(Conexion openConexion) : IConectar(openConexion) {
	this->insertQuery = "INSERT INTO prestamos (isbn, idBiblio, fechaDevolucion) VALUES (?, ?, ?)";
	this->searchIDQuery = "SELECT * FROM prestamos WHERE idPrestamo = ?";
	this->searchAllQuery = "SELECT * FROM prestamos";
	this->updateRowQuery = "UPDATE prestamos SET isbn = ?, idBiblio = ? fechaDevolucion = ? WHERE idPrestamo = ?";
	this->deleteRowQuery = "DELETE FROM prestamos WHERE idPrestamo = ?";
	this->getQuantityBorrowsQuery = "SELECT count(*) as conteo FROM prestamos WHERE idBiblio = ?";
	this->searchHibridPrestamoUsuarioLibro = "SELECT idPrestamo, (SELECT isbn FROM libros l WHERE l.isbn = p.isbn) as isbn, (SELECT titulo FROM libros l WHERE l.isbn = p.isbn) as titulo, idBiblio, (SELECT nombres FROM usuarios u WHERE u.idBiblio = p.idBiblio) as nombres, (SELECT numTel FROM usuarios u WHERE u.idBiblio = p.idBiblio) as contacto, fechaPrestamo, fechaDevolucion FROM prestamos p";
}

bool PrestamoRepositorio::registrar(NodoPrestamo* filaNueva) const {
	try
	{
		PSTMT pst = conexion->prepareStatement(insertQuery);

		pst->setString(1, filaNueva->isbn);
		pst->setInt(2, filaNueva->idBiblio);
		pst->setString(3, filaNueva->fechaDevolucion);

		pst->executeUpdate();

		pst->close();

		return true;

	}
	catch (sql::SQLException& e)
	{
		return false;
	}
}

NodoPrestamo* PrestamoRepositorio::obtenerPorId(int id) const {
	NodoPrestamo* encontrado = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchIDQuery);
		pst->setInt(1, id);
		rs = pst->executeQuery();
		if (rs->next()) {
			encontrado = new NodoPrestamo();
			encontrado->idPrestamo = rs->getInt("idPrestamo");
			encontrado->isbn = rs->getString("isbn");
			encontrado->idBiblio = rs->getInt("idBiblio");
			encontrado->fechaPrestamo = rs->getString("fechaPrestamo");
			encontrado->fechaDevolucion = rs->getString("fechaDevolucion");
		}

		rs->close();

		return encontrado;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el prestamo: " << e.what() << endl;
		return encontrado;
	}

}

NodoPrestamo* PrestamoRepositorio::obtenerTodos() const {
	NodoPrestamo* prestamos = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchAllQuery);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoPrestamo* prestamo = new NodoPrestamo(rs->getInt("idPrestamo"), rs->getString("isbn"), rs->getInt("idBiblio"), rs->getString("fechaPrestamo"), rs->getString("fechaDevolucion"));
			if (prestamos == NULL) prestamos = prestamo;
			else {
				prestamo->sgte = prestamos;
				prestamos = prestamo;
			}
		}

		cout << "Prestamos recolectados" << endl;
		rs->close();
	}
	catch (sql::SQLException& e) {
		cout << "Error al recopilar los prestamos: " << e.what() << endl;

	}

	return prestamos;
}

bool PrestamoRepositorio::actualizar(NodoPrestamo* filaActualizada) const {
	try {
		PSTMT pst = conexion->prepareStatement(updateRowQuery);
		pst->setString(1, filaActualizada->isbn);
		pst->setInt(2, filaActualizada->idBiblio);
		pst->setString(3, filaActualizada->fechaDevolucion);
		pst->setInt(4, filaActualizada->idPrestamo);

		pst->executeUpdate();

		cout << "Fila del prestamo actualizada" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "Error al actualizar la fila del prestamo " << e.what() << endl;
		return false;
	}
}

bool PrestamoRepositorio::eliminar(int id) const {
	try {
		PSTMT pst = conexion->prepareStatement(deleteRowQuery);
		pst->setInt(1, id);
		pst->executeUpdate();
		return true;
	}
	catch (sql::SQLException& e) {
		errorGlobal = "La BD ha rechazado la solicitud";
		return false;
	}
}

int PrestamoRepositorio::obtenerCantidadPrestamos(int id) {
	int conteo = 0;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(getQuantityBorrowsQuery);
		pst->setInt(1, id);
		rs = pst->executeQuery();
		if (rs->next()) {
			conteo = rs->getInt("conteo");
		}

		rs->close();

		return conteo;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el prestamo: " << e.what() << endl;
		return conteo = -1;
	}
}

NodoPrestamoLibroUsuario* PrestamoRepositorio::obtenerHistorialPrestamos() {
	NodoPrestamoLibroUsuario* prestamosHibridos = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchHibridPrestamoUsuarioLibro);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoPrestamoLibroUsuario* prestamoHibrido = new NodoPrestamoLibroUsuario(
				rs->getInt("idPrestamo"),
				rs->getString("isbn"),
				rs->getString("titulo"),
				rs->getInt("idBiblio"),
				rs->getString("nombres"),
				rs->getString("contacto"),
				rs->getString("fechaPrestamo"),
				rs->getString("fechaDevolucion"));

			if (prestamosHibridos == NULL) prestamosHibridos = prestamoHibrido;
			else {
				prestamoHibrido->sgte = prestamosHibridos;
				prestamosHibridos = prestamoHibrido;
			}
		}

		cout << "Prestamos recolectados" << endl;
		rs->close();
	}
	catch (sql::SQLException& e) {
		cout << "Error al recopilar los prestamos: " << e.what() << endl;

	}

	return prestamosHibridos;
}