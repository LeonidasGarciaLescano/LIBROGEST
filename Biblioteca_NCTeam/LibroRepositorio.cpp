#include "Repositorios.h"

LibroRepositorio::LibroRepositorio(Conexion openConexion) : IConectar(openConexion) {
	this->insertQuery = "INSERT INTO libros (isbn, titulo, autor, genero, stockTotal, stockDisponible) VALUES (?, ?, ?, ?, ?, ?)";
	this->searchIDQuery = "SELECT * FROM libros WHERE isbn = ?";
	this->searchAllQuery = "SELECT * FROM libros";
	this->updateRowQuery = "UPDATE libros SET titulo = ?, autor = ?, genero = ?, stockDisponible = ?, stockTotal = ? WHERE isbn = ?";
	this->deleteRowQuery = "DELETE FROM libros WHERE isbn = ?";
	this->updateIncreaseStockQuery = "UPDATE libros SET stockDisponible = stockDisponible + 1, stockTotal = stockTotal + 1 WHERE isbn = ?";
	this->updateDecreaseStockQuery = "UPDATE libros SET stockDisponible = stockDisponible - 1 WHERE isbn = ?";
	this->searchTitleQuery = "SELECT * FROM libros WHERE titulo LIKE ?";
	this->searchAuthorQuery = "SELECT * FROM libros WHERE autor LIKE ?";
	this->searchGenreQuery = "SELECT * FROM libros WHERE genero = ?";
}

bool LibroRepositorio::registrar(NodoLibro* filaNueva) const {
	try
	{
		PSTMT pst = conexion->prepareStatement(insertQuery);

		pst->setString(1, filaNueva->isbn);
		pst->setString(2, filaNueva->titulo);
		pst->setString(3, filaNueva->autor);
		pst->setString(4, filaNueva->genero);
		pst->setInt(5, filaNueva->stockTotal);
		pst->setInt(6, filaNueva->stockDisponible);

		pst->executeUpdate();
		return true;

	}
	catch (sql::SQLException& e)
	{
		return false;
	}
}

NodoLibro* LibroRepositorio::obtenerPorId(string id) const {
	NodoLibro* encontrado = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchIDQuery);
		pst->setString(1, id);
		rs = pst->executeQuery();
		if (rs->next()) {
			encontrado = new NodoLibro();
			encontrado->isbn = rs->getString("isbn");
			encontrado->titulo = rs->getString("titulo");
			encontrado->autor = rs->getString("autor");
			encontrado->genero = rs->getString("genero");
			encontrado->stockDisponible = rs->getInt("stockDisponible");
			encontrado->stockTotal = rs->getInt("stockTotal");
		}

		rs->close();

		return encontrado;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el libro: " << e.what() << endl;
		return encontrado;
	}

}

NodoLibro* LibroRepositorio::obtenerTodos() const {
	NodoLibro* libros = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchAllQuery);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoLibro* libro = new NodoLibro(rs->getString("isbn"), rs->getString("titulo"), rs->getString("autor"), rs->getString("genero"), rs->getInt("stockDisponible"), rs->getInt("stockTotal"));
			if (libros == NULL) libros = libro;
			else {
				libro->sgte = libros;
				libros = libro;
			}
		}

		cout << "Libros recolectados" << endl;
		rs->close();
	}
	catch (sql::SQLException& e) {
		cout << "Error al recopilar los libros " << e.what() << endl;

	}

	return libros;
}

bool LibroRepositorio::actualizar(NodoLibro* filaActualizada) const {
	try {
		PSTMT pst = conexion->prepareStatement(updateRowQuery);
		pst->setString(1, filaActualizada->titulo);
		pst->setString(2, filaActualizada->autor);
		pst->setString(3, filaActualizada->genero);
		pst->setInt(4, filaActualizada->stockDisponible);
		pst->setInt(5, filaActualizada->stockTotal);
		pst->setString(6, filaActualizada->isbn);

		pst->executeUpdate();

		return true;
	}
	catch (sql::SQLException& e) {
		return false;
	}
}

bool LibroRepositorio::eliminar(string id) const {
	try {
		PSTMT pst = conexion->prepareStatement(deleteRowQuery);
		pst->setString(1, id);
		pst->executeUpdate();
		cout << "Fila de libro eliminada con exito" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "No se pudo eliminar la fila del libro: " << e.what() << endl;
		return false;
	}
}

bool LibroRepositorio::aumentarStockPorIsbn(string isbn) {
	try {
		PSTMT pst = conexion->prepareStatement(updateIncreaseStockQuery);
		pst->setString(1, isbn);

		pst->executeUpdate();

		return true;
	}
	catch (sql::SQLException& e) {
		return false;
	}
}

bool LibroRepositorio::reducirStockDisponiblePorIsbn(string isbn) {
	try {
		PSTMT pst = conexion->prepareStatement(updateDecreaseStockQuery);
		pst->setString(1, isbn);

		pst->executeUpdate();

		return true;
	}
	catch (sql::SQLException& e) {
		return false;
	}
}

NodoLibro* LibroRepositorio::obtenerPorTitulo(string titulo) {

	NodoLibro* encontrados = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchTitleQuery);
		pst->setString(1, titulo + "%");
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoLibro* encontrado = new NodoLibro();
			encontrado->isbn = rs->getString("isbn");
			encontrado->titulo = rs->getString("titulo");
			encontrado->autor = rs->getString("autor");
			encontrado->genero = rs->getString("genero");
			encontrado->stockDisponible = rs->getInt("stockDisponible");
			encontrado->stockTotal = rs->getInt("stockTotal");
			if (encontrados == NULL) encontrados = encontrado;
			else {
				encontrado->sgte = encontrados;
				encontrados = encontrado;
			}
		}

		rs->close();

		return encontrados;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el libro: " << e.what() << endl;
		return encontrados;
	}
}

NodoLibro* LibroRepositorio::obtenerPorAutor(string autor) {

	NodoLibro* encontrados = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchAuthorQuery);
		pst->setString(1, autor+"%");
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoLibro* encontrado = new NodoLibro();
			encontrado->isbn = rs->getString("isbn");
			encontrado->titulo = rs->getString("titulo");
			encontrado->autor = rs->getString("autor");
			encontrado->genero = rs->getString("genero");
			encontrado->stockDisponible = rs->getInt("stockDisponible");
			encontrado->stockTotal = rs->getInt("stockTotal");
			if (encontrados == NULL) encontrados = encontrado;
			else {
				encontrado->sgte = encontrados;
				encontrados = encontrado;
			}
		}

		rs->close();

		return encontrados;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el libro: " << e.what() << endl;
		return encontrados;
	}
}

NodoLibro* LibroRepositorio::obtenerPorGenero(string genero) {

	NodoLibro* encontrados = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchGenreQuery);
		pst->setString(1, genero);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoLibro* encontrado = new NodoLibro();
			encontrado->isbn = rs->getString("isbn");
			encontrado->titulo = rs->getString("titulo");
			encontrado->autor = rs->getString("autor");
			encontrado->genero = rs->getString("genero");
			encontrado->stockDisponible = rs->getInt("stockDisponible");
			encontrado->stockTotal = rs->getInt("stockTotal");
			if (encontrados == NULL) encontrados = encontrado;
			else {
				encontrado->sgte = encontrados;
				encontrados = encontrado;
			}
		}

		rs->close();

		return encontrados;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el libro: " << e.what() << endl;
		return encontrados;
	}
}