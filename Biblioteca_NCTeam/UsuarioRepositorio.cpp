#include "Repositorios.h"

//Metodos de Usuario
UsuarioRepositorio::UsuarioRepositorio(Conexion openConexion) : IConectar(openConexion) {
	this->insertQuery = "INSERT INTO usuarios (nombres, numTel, dni) VALUES (?, ?, ?)";
	this->searchIDQuery = "SELECT * FROM usuarios WHERE idBiblio = ?";
	this->searchAllQuery = "SELECT * FROM usuarios";
	this->searchNameQuery = "SELECT * FROM usuarios WHERE nombres = ?";
	this->updateRowQuery = "UPDATE usuarios SET nombres = ?, numTel = ?, dni = ? WHERE idBiblio = ?";
	this->deleteRowQuery = "DELETE FROM usuarios WHERE idBiblio = ?";
}

bool UsuarioRepositorio::registrar(NodoUsuario* filaNueva) const {
	try
	{
		PSTMT pst = conexion->prepareStatement(insertQuery);
		pst->setString(1, filaNueva->nombres);
		pst->setString(2, filaNueva->numTel);
		pst->setString(3, filaNueva->dni);

		pst->executeUpdate();

		return true;

	}
	catch (sql::SQLException& e)
	{

		return false;
	}
}

NodoUsuario* UsuarioRepositorio::obtenerPorId(int id) const {
	NodoUsuario* encontrado = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchIDQuery);
		pst->setInt(1, id);
		rs = pst->executeQuery();
		if (rs->next()) {
			encontrado = new NodoUsuario();
			encontrado->idBiblio = rs->getInt("idBiblio");
			encontrado->nombres = rs->getString("nombres");
			encontrado->numTel = rs->getString("numTel");
			encontrado->dni = rs->getString("dni");
		}

		rs->close();

		return encontrado;

	}
	catch (sql::SQLException& e) {
		cout << "Error al buscar el usuario: " << e.what() << endl;
		return encontrado;
	}

}

NodoUsuario* UsuarioRepositorio::obtenerTodos() const {
	NodoUsuario* usuarios = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchAllQuery);
		rs = pst->executeQuery();
		while (rs->next()) {
			NodoUsuario* usuario = new NodoUsuario(rs->getInt("idBiblio"), rs->getString("nombres"), rs->getString("numTel"), rs->getString("dni"));
			if (usuarios == NULL) usuarios = usuario;
			else {
				usuario->sgte = usuarios;
				usuarios = usuario;
			}
		}

		cout << "Usuarios recolectados" << endl;
		pst->close();
		rs->close();
	}
	catch (sql::SQLException& e) {
		cout << "Error al recopilar a los usuarios " << e.what() << endl;

	}

	return usuarios;
}

NodoUsuario* UsuarioRepositorio::obtenerPorNombres(string nombres) {
	NodoUsuario* encontrado = NULL;

	try {
		Respuesta rs;
		PSTMT pst = conexion->prepareStatement(searchNameQuery);
		pst->setString(1, nombres);
		rs = pst->executeQuery();
		if (rs->next()) {
			encontrado = new NodoUsuario();
			encontrado->idBiblio = rs->getInt("idBiblio");
			encontrado->nombres = rs->getString("nombres");
			encontrado->numTel = rs->getString("numTel");
			encontrado->dni = rs->getString("dni");
		}

		rs->close();

		return encontrado;

	}
	catch (sql::SQLException& e) {
		return encontrado;
	}
}

bool UsuarioRepositorio::actualizar(NodoUsuario* filaActualizada) const {
	try {
		PSTMT pst = conexion->prepareStatement(updateRowQuery);
		pst->setString(1, filaActualizada->nombres);
		pst->setString(2, filaActualizada->numTel);
		pst->setString(3, filaActualizada->dni);
		pst->setInt(4, filaActualizada->idBiblio);

		pst->executeUpdate();

		pst->close();

		cout << "Fila de usuario actualizada" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "Error al actualizar la fila de usuario: " << e.what() << endl;
		return false;
	}
}

bool UsuarioRepositorio::eliminar(int id) const {
	try {
		PSTMT pst = conexion->prepareStatement(deleteRowQuery);
		pst->setInt(1, id);
		pst->executeUpdate();
		cout << "Fila de usuario eliminada con exito" << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "No se pudo eliminar la fila del usuario: " << e.what() << endl;
		return false;
	}
}
