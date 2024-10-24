#include "Usuario.h"

bool registrarUsuario(NodoUsuario* usuario) {
    bool result = false;

    usuario->trimCampos();
    
    if (usuario->validarRegistro()) {
        result = usuarioDriver->registrar(usuario);
        delete usuario;
        if (result == true) {
            return result;
        }
        else {
            errorGlobal = "El usuario ya existe en la BD";
        }
    }
    return result;
}