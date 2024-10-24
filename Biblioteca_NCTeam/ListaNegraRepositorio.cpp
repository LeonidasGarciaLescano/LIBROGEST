#include "Repositorios.h"

//Metodos de lista negra
ListaNegraRepositorio::ListaNegraRepositorio(Conexion openConexion) : IConectar(openConexion) {
	this->insertQuery = "INSERT INTO listanegra (idListaNegra, nombres, dni) VALUES (?, ?, ?, ?)";
	this->searchIDQuery = "SELECT * FROM listanegra WHERE idListaNegra = ?";
	this->searchAllQuery = "SELECT * FROM listanegra";
	this->updateRowQuery = "UPDATE listanegra SET nombres = ?, dni = ? WHERE idListaNegra = ?";
	this->deleteRowQuery = "DELETE FROM listanegra WHERE idListaNegra = ?";
	this->searchDNIQuery = "SELECT * FROM listanegra WHERE idListaNegra = ?";
}

bool ListaNegraRepositorio::registrar(NodoListaNegra* filaNueva) const {
	try
	{
		PSTMT pst = conexion->prepareStatement(insertQuery);

		pst->setInt(1, filaNueva->idListaNegra);
		pst->setString(2, filaNueva->nombres);
		pst->setString(3, filaNueva->dni);

		pst->executeUpdate();

		cout << "Vetado registrado con exito en la BD" << endl;
		return true;

	}
	catch (sql::SQLException& e)
	{
		cout << "Error al registrar al vetado en la BD: " << e.what() << endl;
		return false;
	}
}

NodoListaNegra* ListaNegraRepositorio::obtenerPorId(int id) const {
	NodoListaNegra* encontrado = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchIDQuery);
		pst->setInt(1, id);
		rs = pst->executeQuery();
		if (rs->next()) {
			encontrado = new NodoListaNegra();
			encontrado->idListaNegra = rs->getInt("idBiblio");
			encontrado->nombres = rs->getString("nombres");
			encontrado->dni = rs->getString("dni");
		}

		rs->close();

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar al vetado: " << e.what() << endl;

	}

	return encontrado;

}

NodoListaNegra* ListaNegraRepositorio::obtenerTodos() const {
	NodoListaNegra* vetados = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchAllQuery);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoListaNegra* vetado = new NodoListaNegra(rs->getInt("idListaNegra"), rs->getString("nombres"), rs->getString("dni"));
			if (vetados == NULL) vetados = vetado;
			else {
				vetado->sgte = vetados;
				vetados = vetado;
			}
		}

		cout << "Vetados recolectados" << endl;
		pst->close();
		rs->close();
	}
	catch (sql::SQLException& e) {
		cout << "Error al recopilar a los vetados: " << e.what() << endl;

	}

	return vetados;
}

bool ListaNegraRepositorio::actualizar(NodoListaNegra* filaActualizada) const {
	try {
		PSTMT pst = conexion->prepareStatement(updateRowQuery);
		pst->setString(1, filaActualizada->nombres);
		pst->setString(3, filaActualizada->dni);
		pst->setInt(4, filaActualizada->idListaNegra);

		pst->executeUpdate();

		pst->close();

		cout << "Fila de vetado actualizada" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "Error al actualizar la fila de vetado: " << e.what() << endl;
		return false;
	}
}

bool ListaNegraRepositorio::eliminar(int id) const {
	try {
		PSTMT pst = conexion->prepareStatement(deleteRowQuery);
		pst->setInt(1, id);
		pst->executeUpdate();
		cout << "Fila de vetado eliminada con exito" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "No se pudo eliminar la fila del vetado: " << e.what() << endl;
		return false;
	}
}

//DEVUELVE TRUE SI EL USUARIO ESTA BANEADO
bool ListaNegraRepositorio::verificarBaneado(string dni) {

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchDNIQuery);
		pst->setString(1, dni);
		rs = pst->executeQuery();
		if (rs->next()) return true;
		else return false;

		rs->close();

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar al vetado: " << e.what() << endl;
		return false;
	}
}