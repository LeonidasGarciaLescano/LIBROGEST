#include "menu.h"
#include "tabular.h"
#include "Pantallas.h"

//OPCION 1 - REGISTRAR NUEVO LIBRO O AUMENTAR EL STOCK
void registroDeLibros() {
    system("cls");
    NodoLibro* libroNuevo = new NodoLibro();
    string tituloLibro, autorLibro, isbnLibro, generoLibro, stockLibro;
    bool existencia = false;


    while (true) {
        pantallaRegistroDeLibros();

        gotoxy(48, 6); getline(cin, isbnLibro);

        bool isbnValidado = NodoLibro::validarIsbn(isbnLibro);
        libroNuevo = libroDriver->obtenerPorId(isbnLibro);

        if (isbnValidado == false) {								// escape rápido del registro, no tocar
            gotoxy(41, 8); cout << "[ EL ISBN INGRESADO NO ES VALIDO ]";
            _getch();
            return;
        }
        else if (libroNuevo != NULL) {						// LÓGICA DE VERIFICACIÓN DE EXISTENCIA, cambiar ese 1 por la funcion correspondiente
            existencia = true;
            gotoxy(38, 8); cout << "[ LIBRO   EXISTENTE   EN   BASE   DE   DATOS ]";
            // LÓGICA PARA AUTOLLENADO DE INFO DEL LIBRO

            gotoxy(48, 11); cout << libroNuevo->titulo;
            gotoxy(48, 13); cout << libroNuevo->autor;
            gotoxy(48, 15); cout << libroNuevo->genero;

        }
        else {
            gotoxy(41, 8); cout << "[ LIBRO   NUEVO   EN   BASE   DE   DATOS ]";
            gotoxy(48, 11); getline(cin, tituloLibro);
            gotoxy(48, 13); getline(cin, autorLibro);		// nomás recoge la data
            gotoxy(48, 15); getline(cin, generoLibro);
        }

        gotoxy(48, 17); getline(cin, stockLibro);

        if (existencia) {

            try
            {
                libroNuevo->stockTotal = stoi(stockLibro);
            }
            catch (const std::exception&)
            {
                libroNuevo->stockTotal = -1;
            }

            if (!NodoLibro::validarStockTotal(libroNuevo->stockTotal)) {
                //if (stockLibro <= 0 || stockLibro > 20){			// falta hacer q pase de str a int, ahí ya le meten su rango grrr	
                gotoxy(51, 19); cout << "STOCK  INVALIDO.";
            }
            else {											// INSERTAR FUNCION DE GUARDADO EN BASE DE DATOS
                // aquí

                bool flag = true;

                if (libroNuevo->stockTotal < libroNuevo->stockDisponible) {
                    flag = false;
                }

                if (libroDriver->actualizar(libroNuevo) && flag) {
                    gotoxy(43, 19); cout << "LIBRO REGISTRADO CORRECTAMENTE !!";
                }
                else {	// no se guarda correctamente
                    gotoxy(38, 19); cout << "NO SE PUDO CONECTAR CON LA BASE DE DATOS";
                }
            }

        }
        else {

            libroNuevo = new NodoLibro();
            libroNuevo->isbn = isbnLibro;
            libroNuevo->titulo = tituloLibro;
            libroNuevo->autor = autorLibro;
            libroNuevo->genero = generoLibro;

            try
            {
                libroNuevo->stockTotal = stoi(stockLibro);
            }
            catch (const std::exception&)
            {
                libroNuevo->stockTotal = -1;
            }


            if (!NodoLibro::validarStockTotal(libroNuevo->stockTotal)) {
                //if (stockLibro <= 0 || stockLibro > 20){			// falta hacer q pase de str a int, ahí ya le meten su rango grrr	
                gotoxy(51, 19); cout << "STOCK  INVALIDO.";
            }
            else {											// INSERTAR FUNCION DE GUARDADO EN BASE DE DATOS
                // aquí
                libroNuevo->stockDisponible = libroNuevo->stockTotal;

                if (registrarLibro(libroNuevo)) {
                    gotoxy(43, 19); cout << "LIBRO REGISTRADO CORRECTAMENTE !!";
                }
                else {	// no se guarda correctamente
                    gotoxy(38, 19); cout << mostrarErrorGlobal();
                }
            }
        }

        gotoxy(39, 20); cout << "Presione cualquier tecla para regresar...";
        char tecla = _getch();
        return;
    }
}

//OPCION 2 - BUSQUEDA DE LIBROS Y GENERACIÓN DE PRÉSTAMOS

void seleccionGenero(int& opcionGeneroSeleccionada, NodoLibro*& librosPorGenero, NodoLibro*& librosBiblioteca) {
    string generos[] = { "ROMANCE", "FANTASIA", "CIENCIA FICCION", "HISTORIA", "MISTERIO", "HORROR", "BIOGRAFIA", "AMOR" };
    int numGeneros = sizeof(generos) / sizeof(generos[0]);

    while (true) {
        gotoxy(6, 5); cout << string(110, ' ');
        gotoxy(6, 5); cout << "Seleccione genero:";

        int x = 30;
        for (int i = 0; i < numGeneros; ++i) {
            setConsoleColor(opcionGeneroSeleccionada == i ? 0 : 15, opcionGeneroSeleccionada == i ? 15 : 0);
            gotoxy(x, 5); cout << generos[i];
            x += generos[i].length() + 3;
        }
        setConsoleColor(15, 0);

        char tecla = _getch();
        if (tecla == 0 || tecla == -32) {

            tecla = _getch();
            if (tecla == 75) {
                opcionGeneroSeleccionada = (opcionGeneroSeleccionada - 1 + numGeneros) % numGeneros;
            }
            else if (tecla == 77) {
                opcionGeneroSeleccionada = (opcionGeneroSeleccionada + 1) % numGeneros;
            }
            else if (tecla == 72) {
                return;
            }
        }
        else if (tecla == 13) {
            system("cls");
            pantallaBusquedaDeLibros(0, "");
            gotoxy(0, 9);
            switch (opcionGeneroSeleccionada) {
            case 0: {
                librosPorGenero = buscarPorGenero("Romance", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
                
            case 1: {
                librosPorGenero = buscarPorGenero("Fantasia", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 2:{
                librosPorGenero = buscarPorGenero("Ciencia ficcion", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 3: {
                librosPorGenero = buscarPorGenero("Historia", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 4: {
                librosPorGenero = buscarPorGenero("Misterio", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 5: {
                librosPorGenero = buscarPorGenero("Horror", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 6: {
                librosPorGenero = buscarPorGenero("Biografia", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            case 7: {
                librosPorGenero = buscarPorGenero("Amor", librosBiblioteca);
                cout << generarTablaLibros(librosPorGenero);
                break;
            }
            }
            char tecla = _getch();
            return;
        }
        else if (tecla == 27) {
            return;
        }
    }
}

void busquedaDeLibros() {   // AÑADIR TABLASSSSSSSSSSS
    system("cls");

    NodoLibro* librosBiblioteca = libroDriver->obtenerTodos();
    NodoLibro* librosPorTitulo = NULL;
    NodoLibro* librosPorAutor = NULL;
    NodoLibro* librosPorGenero = NULL;
    NodoLibro* librosPorIsbn = NULL;
    NodoLibro* libroAPrestar = NULL;

    int opcionSeleccionada = 0;
    int opcionGeneroSeleccionada = 0;
    string generos[] = { "ROMANCE", "FANTASIA", "CIENCIA FICCION", "HISTORIA", "MISTERIO", "HORROR", "BIOGRAFIA", "AMOR" };
    string generoSeleccionado = "";
    string titulo, isbn, autor, isbnPrestamo;
    pantallaBusquedaDeLibros(opcionSeleccionada, generoSeleccionado);

    while (true) {
        limpiarNodoLibro(librosPorTitulo);
        limpiarNodoLibro(librosPorAutor);
        limpiarNodoLibro(librosPorGenero);
        limpiarNodoLibro(librosPorIsbn);
        limpiarNodoLibro(libroAPrestar);
        char tecla = _getch();
        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 5) % 5;
            }
            else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 5;
            }
            pantallaBusquedaDeLibros(opcionSeleccionada, generoSeleccionado);
        }
        else if (tecla == 13) {
            switch (opcionSeleccionada) {
                //system("cls");
                //pantallaBusquedaDeLibros(0, "");
            case 0:
                seleccionGenero(opcionGeneroSeleccionada, librosPorGenero, librosBiblioteca);
                generoSeleccionado = generos[opcionGeneroSeleccionada];
                pantallaBusquedaDeLibros(opcionSeleccionada, generoSeleccionado);
                break;
            case 1:
                gotoxy(6, 5); cout << string(110, ' ');
                gotoxy(6, 5); cout << "Ingrese titulo:            ";
                getline(cin, titulo);
                limpiarEspacio(0, 9, 121, 20);
                gotoxy(0, 9);

                librosPorTitulo = buscarPorTitulo(titulo, librosBiblioteca);
                if (librosPorTitulo != NULL) cout << generarTablaLibros(librosPorTitulo); 
                else cout << mostrarErrorGlobal();
                
                break;
            case 2:
                gotoxy(6, 5); cout << string(110, ' ');
                gotoxy(6, 5); cout << "Ingrese ISBN:            ";
                getline(cin, isbn);
                limpiarEspacio(0, 9, 121, 20);
                gotoxy(0, 9); 
                
                librosPorIsbn = buscarPorISBN(isbn, librosBiblioteca);
                if (librosPorIsbn != NULL) cout << generarTablaLibros(librosPorIsbn);
                else cout << mostrarErrorGlobal();

                break;
            case 3:
                gotoxy(6, 5); cout << string(110, ' ');
                gotoxy(6, 5); cout << "Ingrese autor:           ";
                getline(cin, autor);
                limpiarEspacio(0, 9, 121, 20);
                gotoxy(0, 9); 

                librosPorAutor = buscarPorAutor(autor, librosBiblioteca);
                if (librosPorAutor != NULL) cout << generarTablaLibros(librosPorAutor);
                else cout << mostrarErrorGlobal();

                break;
            case 4:
                limpiarEspacio(41, 7, 25, 1);
                gotoxy(42, 7);
                getline(cin, isbnPrestamo);
                libroAPrestar = buscarPorISBN(isbnPrestamo, librosBiblioteca);
                if (libroAPrestar != NULL) prestamoDeLibros(libroAPrestar);
                else {
                    limpiarEspacio(41, 7, 25, 1);
                    gotoxy(42, 7); cout << "[ ISBN invalido ]";
                } 
                break;
            }
        }
        else if (tecla == 27) {
            limpiarNodoLibro(librosBiblioteca);
            limpiarNodoLibro(librosPorTitulo);
            limpiarNodoLibro(librosPorAutor);
            limpiarNodoLibro(librosPorGenero);
            limpiarNodoLibro(librosPorIsbn);
            limpiarNodoLibro(libroAPrestar);
            return;
        }
    }
}

void registroUsuario(NodoLibro*& libro) {
    system("cls");
    int opcionSeleccionada = 0;
    string codigo;
    bool validacion = false;
    NodoUsuario* usuario = new NodoUsuario();
    pantallaRegistroUsuario(opcionSeleccionada);
    gotoxy(65, 10); cout << "[ presione enter para escribir ]";

    gotoxy(30, 6); cout << libro->titulo; 					//INGRESA TITULO DEL LIBRO A PRESTAR
    while (true) {
        char tecla = _getch();

        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
            }
            else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 2;
            }
            pantallaRegistroUsuario(opcionSeleccionada);
        }
        else if (tecla == 13) {
            if (opcionSeleccionada == 0) {
                limpiarEspacio(63, 10, 20, 1);
                limpiarEspacio(32, 15, 56, 1);
                limpiarEspacio(64, 10, 34, 1);
                gotoxy(65, 10); getline(cin, codigo);

                try
                {
                    usuario->idBiblio = stoi(codigo);
                }
                catch (const std::exception&)
                {
                    usuario->idBiblio = -1;
                }

                if (usuario->validarIdBiblio()) {  // agregar lógica de confirmacion de códigos
                    gotoxy(33, 15); cout << "[ Codigo valido, usuario registrado en base de datos ]"; // meterle la condicional de n° de prestamos
                    validacion = true;
                }
                else {
                    gotoxy(32, 15); cout << "[ Codigo invalido, usuario no figura en base de datos ]";
                    validacion = false;
                }
            }
            else if (opcionSeleccionada == 1 && validacion == true) {
                confirmacionDatos(libro, usuario);
                return;
            }
        }
        else if (tecla == 27) {
            limpiarNodoUsuario(usuario);
            busquedaDeLibros();
            return;
        }
    }
}

void prestamoDeLibros(NodoLibro*& libro) {
    int opcionSeleccionada = 0;
    system("cls");
    pantallaPrestamoDeLibros(opcionSeleccionada);

    gotoxy(37, 6); cout << libro->isbn;
    gotoxy(29, 8); cout << libro->titulo;
    gotoxy(29, 10); cout << libro->autor;
    gotoxy(29, 12); cout << libro->genero;
    gotoxy(46, 14); cout << libro->stockDisponible;

    while (true) {
        char tecla = _getch();
        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
            }
            else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 2;
            }
            pantallaPrestamoDeLibros(opcionSeleccionada);
        }
        else if (tecla == 13) {
            if (opcionSeleccionada == 0) {
                registroUsuario(libro);
                return;
            }
            else if (opcionSeleccionada == 1) {
                busquedaDeLibros();
                return;

            }
        }
        else if (tecla == 27) {
            busquedaDeLibros();
            return;
        }
    }
}

void confirmacionDatos(NodoLibro*& libro, NodoUsuario*& usuario) {
    system("cls");
    pantallaConfirmacionDatos();

    //aki ponle el if
    //ola pon q va a pasar si no le deja grrrrrrrrrrrrrrrrrrrrrr
    while (true) {
        if (registrarPrestamo(libro, usuario)) {
            gotoxy(41, 11); cout << "PRESTAMO    REGISTRADO    CORECTAMENTE";
            gotoxy(58, 12); cout << "u w u";
            gotoxy(60, 13);
        }
        else {
            gotoxy(38, 11); cout << "PRESTAMO    NO   REGISTRADO    CORECTAMENTE";
            gotoxy(58, 12); cout << "u n u";
            gotoxy(60, 13);
        }
        char tecla = _getch();
        menuPrincipal();
    }
}

//OPCION 3 - DEVOLUCION DE LIBROS

void devolucionDeLibros() {
    string codigo;
    bool validacion = false;
    int opcionSeleccionada = 0;
    string titulo = "";
    NodoPrestamo* prestamo = new NodoPrestamo();

    gotoxy(65, 8); cout << "[ Presione enter para escribir ]";

    while (true) {
        pantallaDevolucionDeLibros(opcionSeleccionada);
        char tecla = _getch();
        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
            }
            else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 2;
            }
            pantallaDevolucionDeLibros(opcionSeleccionada);
        }
        else if (tecla == 13) {
            if (opcionSeleccionada == 0) {
                limpiarEspacio(31, 13, 62, 1);
                limpiarEspacio(55, 8, 45, 1);
                gotoxy(65, 8); getline(cin, codigo);

                try
                {
                    prestamo->idPrestamo = stoi(codigo);
                }
                catch (const std::exception&)
                {
                    prestamo->idPrestamo = -1;
                }

                if (prestamo->validarIdPrestamo()) {
                    NodoPrestamo* prestamoExistente = prestamoDriver->obtenerPorId(prestamo->idPrestamo);
                    if (prestamoExistente != NULL) {
                        titulo = libroDriver->obtenerPorId(prestamoExistente->isbn)->titulo;
                        gotoxy(33, 13); cout << "[ Codigo valido, prestamo registrado en base de datos ]";
                        validacion = true;
                    }
                    else {
                        gotoxy(33, 13); cout << "[ El prestamo no esta registrado en la base de datos ]";
                        validacion = false;
                    }
                    limpiarNodoPrestamo(prestamoExistente);

                }
                else {

                    gotoxy(32, 13); cout << "[ " << mostrarErrorGlobal() << " ]";
                    validacion = false;
                }

            }
            else if (opcionSeleccionada == 1 && validacion == true) {
                eliminarPrestamo(prestamo);
                limpiarEspacio(32, 13, 56, 1);
                gotoxy(44, 12); cout << "LIBRO REGRESADO CORRECTAMENTE !!";
                gotoxy(27, 14); cout << "Titulo del libro: " << titulo;
                char tecla = _getch();
                return;
            }
        }
        else if (tecla == 27) {
            limpiarNodoPrestamo(prestamo);
            return;
        }
        if (tecla == 27) {
            limpiarNodoPrestamo(prestamo);
            return;
        }
    }
}

//OPCION 4 - MOSTRAR HISTORIAL DE PRÉSTAMOS

void historialDePrestamos() {

    NodoPrestamoLibroUsuario* prestamos = prestamoDriver->obtenerHistorialPrestamos();

    while (true) {
        pantallaHistorialDePrestamos();
        gotoxy(0, 5); cout << generarTablaPrestamos(prestamos); // tabla
        char tecla = _getch();
        if (tecla == 27) {
            limpiarNodoPrestamoLibroUsuario(prestamos);
            return;
        }
    }
}

// OPCIÓN 5 - REGISTRO DE USUARIOS

void nuevoUsuario(){ 
	system("cls");
	string nombre, dni, telefono;
	int opcionSeleccionada = 0;
	pantallaNuevoUsuario(opcionSeleccionada);
    NodoUsuario* nuevoUsuario = new NodoUsuario();
	gotoxy(60, 11); cout << "[ Presione enter para escribir ]";
	
	while (true) {
		char tecla = _getch();
        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 2) % 2;
            }
            else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 2;
            }
            pantallaNuevoUsuario(opcionSeleccionada);
        }
        else if (tecla == 13) {
        		if (opcionSeleccionada == 0) {
        			limpiarEspacio(57, 8, 50, 8);
        			gotoxy(58, 8); getline(cin, nombre);
					gotoxy(58, 11); getline(cin, dni);
					gotoxy(58, 14); getline(cin, telefono);
                    nuevoUsuario->idBiblio = 1;
                    nuevoUsuario->nombres = nombre;
                    nuevoUsuario->dni = dni;
                    nuevoUsuario->numTel = telefono;
                    
                    nuevoUsuario->validarRegistro();

				} else if (opcionSeleccionada == 1) { 
        			if (!nuevoUsuario->validarRegistro()) {
        			gotoxy(46, 18); cout << "[ " << mostrarErrorGlobal() << " ]"; //ERROR
				} else {//EXITO
                        if (registrarUsuario(nuevoUsuario)) {
                            gotoxy(44, 19); cout << "[ Usuario guardado correctamente ]";
                            gotoxy(42, 21); cout << "[ Su nuevo codigo de biblioteca es: " << usuarioDriver->obtenerPorNombres(nombre)->idBiblio << " ]";	// acá va el código q le debería salir uwu
                        }
                        else {
                            
                            gotoxy(48, 18); cout << "[ " << mostrarErrorGlobal() << " ]"; //ERROR
                        }
					
				}
                char tecla = _getch();
				return; 
            }
        }
        else if (tecla == 27) {
        	menuPrincipal();
            return;
        }
    }
}

//SELECCIÓN DE OPCIONES
void menuPrincipal(){
	system("cls");
    int opcionSeleccionada = 0;
	pantallaPrincipal(opcionSeleccionada);

    while (true) {
        char tecla = _getch();
        if (tecla == 0 || tecla == -32) {
            tecla = _getch();
            if (tecla == 75) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 6) % 6;
            } else if (tecla == 77) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 6;
            }
            pantallaPrincipal(opcionSeleccionada);
        } else if (tecla == 13) {
            system("cls");
            switch (opcionSeleccionada) {
                case 0:
                    registroDeLibros();
                    break;
                case 1:
                    busquedaDeLibros();
                    break;
                case 2:
                    devolucionDeLibros();
                    break;
                case 3:
                    historialDePrestamos();
                    break;
                case 4:
                    nuevoUsuario();
                    break;
            }
            system ("cls");
            pantallaPrincipal(opcionSeleccionada);
        }
    }
}

int menu() {
    tamanoConsola();
    menuPrincipal();
    return 0;
}

