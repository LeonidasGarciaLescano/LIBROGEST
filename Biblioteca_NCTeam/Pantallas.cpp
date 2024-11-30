#include "tabular.h"
#include "Pantallas.h"

// FUNCIONES TÉCNICAS
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setConsoleColor(int text, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | text);
}

void tamanoConsola() {
    SMALL_RECT rect;
    COORD coord;
    coord.X = 121; // Definiendo X y
    coord.Y = 30;  // Y para el tamaño del búfer.
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = coord.Y-1; // Altura para ventana
    rect.Right = coord.X-1;  // Ancho para ventana

    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hwnd, coord);       // Establece tamaño del búfer
    SetConsoleWindowInfo(hwnd, TRUE, &rect);
}

void dibujarCuadro(int x, int y, int ancho, int alto, bool selected = false) {
    setConsoleColor(selected ? 0 : 15, selected ? 15 : 0);  // Cambia color si está seleccionado
    for (int i = 0; i < ancho; i++) {
        gotoxy(x + i, y);
        cout << (i == 0 ? (char)201 : (i == ancho - 1 ? (char)187 : (char)205)); // Borde superior
        gotoxy(x + i, y + alto - 1);
        cout << (i == 0 ? (char)200 : (i == ancho - 1 ? (char)188 : (char)205)); // Borde inferior
    }

    for (int i = 1; i < alto - 1; i++) {
        gotoxy(x, y + i);
        cout << (char)186; // Borde izquierdo
        gotoxy(x + ancho - 1, y + i);
        cout << (char)186; // Borde derecho
    }
    setConsoleColor(15, 0);  // Restablece el color original
}

void limpiarEspacio(int x, int y, int ancho, int alto) {
    for (int i = 0; i < alto; i++) {
        gotoxy(x, y + i); // Posiciona el cursor en cada fila
        cout << string(ancho, ' '); // Escribe una línea de espacios del ancho especificado
    }
}


// PANTALLAS

void pantallaConfirmacionDatos(){
	dibujarCuadro(0, 0, 120, 30); // MARCO BASE
    
    string asciiArt[] = {
        "                .-~~~~~~~~~-._       _.-~~~~~~~~~-.",
        "            __.'              ~.   .~              `.__",
        "          .'//                  \\./                  \\\\`.",
        "        .'//                     |                     \\\\`.",
        "      .'// .-~\"\"\"\"\"\"\"~~~~-._     |     _,-~~~~\"\"\"\"\"\"\"~-. \\\\`.",
        "    .'//.-\"                 `-.  |  .-'                 \"-.\\\\`.",
        "  .'//______.============-..   \\ | /   ..-============.______\\\\`.",
        ".'______________________________\\|/______________________________`.",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(27, 16 + i);
        cout << asciiArt[i];
    }
}

void pantallaNuevoUsuario(int opcionSeleccionada){
	dibujarCuadro(0, 0, 120, 30); // MARCO BASE
    
    string asciiArt[] = {
        "  _   _  __ ___  __ ___ _   _              _       _         __           _  ___  _  ",
        " |_) |_ /__  |  (_   | |_) / \\   |\\ | | | |_ \\  / / \\   | | (_  | |  /\\  |_)  |  / \\ ",
        " | \\ |_ \\_| _|_ __)  | | \\ \\_/   | \\| |_| |_  \\/  \\_/   |_| __) |_| /--\\ | \\ _|_ \\_/ ",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(19, 1 + i);
        cout << asciiArt[i];
    }
        
    dibujarCuadro(9, 6, 101, 11, opcionSeleccionada == 0);
    gotoxy(15, 8); cout << "Ingrese nombre completo:";  		
    gotoxy(15, 11); cout << "Ingrese DNI:";
    gotoxy(15, 14); cout << "Ingrese numero de telefono:";
    
    dibujarCuadro(47, 24, 25, 3, opcionSeleccionada == 1); gotoxy(53, 25); cout << "A C E P T A R";
}

void pantallaPrestamoDeLibros(int opcionSeleccionada) {
    dibujarCuadro(0, 0, 121, 30); // MARCO BASE
    
    string asciiArt2[] = {
        "  _   _ ___            _  __    _   _      ___  _   _   _  ",
        " | \\ |_  |  /\\  |  |  |_ (_    | \\ |_   |   |  |_) |_) / \\ ",
        " |_/ |_  | /--\\ |_ |_ |_ __)   |_/ |_   |_ _|_ |_) | \\ \\_/ ",
    };
    int numLines2 = sizeof(asciiArt2) / sizeof(asciiArt2[0]);
    for (int i = 0; i < numLines2; ++i) {
        gotoxy(31, 1 + i);
        cout << asciiArt2[i];
    }

    string asciiArt[] = {
        "            _ _       _ _       _ _       _ _",
        "       .-. | | | .-. | | | .-. | | | .-. |.| |",
        "       | |_|.| |_| |_| |.|_| |_| |.|_| |_| | |",
        "     />| | |.|.| | | |.|.| | | |.|.| | | |.|.|<\\",
        "    // | | | |.| | | |.| | | | | |.| | | | | | \\\\",
        "   //  | | | | | | | |.| | | | |.| | | | | |.|  \\\\",
        "  </   | | | | | | | | | | | | | | | | | | | |   \\>",
        "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(33, 21 + i);
        cout << asciiArt[i];
    }
    
    gotoxy(18, 6); cout << "ISBN del libro:";
    gotoxy(18, 8); cout << "Titulo:"; 
    gotoxy(18, 10); cout << "Autor:"; 
    gotoxy(18, 12); cout << "Genero:"; 
    gotoxy(20, 14); cout << "---> Stock disponible:"; 
    
    dibujarCuadro(30, 17, 25, 3, opcionSeleccionada == 0); 
    gotoxy(36, 18); cout << "A C E P T A R"; 
    
    dibujarCuadro(65, 17, 25, 3, opcionSeleccionada == 1); 
    gotoxy(68, 18); cout << "R E T R O C E D E R";
}

void pantallaRegistroDeLibros(){
	system ("cls");
	string tituloLibro, autorLibro, isbnLibro, generoLibro, stockLibro;
    dibujarCuadro(0, 0, 120, 30); // MARCO BASE
    
    string asciiArt[] = {
        "  _   _  __ ___  __ ___ _   _     _   _      ___  _   _   _   __ ",
        " |_) |_ /__  |  (_   | |_) / \\   | \\ |_   |   |  |_) |_) / \\ (_  ",
        " | \\ |_ \\_| _|_ __)  | | \\ \\_/   |_/ |_   |_ _|_ |_) | \\ \\_/ __) ",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(29, 1 + i);
        cout << asciiArt[i];
    }
    
    string asciiArt2[] = {
        "            _ _       _ _       _ _       _ _",
        "       .-. | | | .-. | | | .-. | | | .-. |.| |",
        "       | |_|.| |_| |_| |.|_| |_| |.|_| |_| | |",
        "     />| | |.|.| | | |.|.| | | |.|.| | | |.|.|<\\",
        "    // | | | |.| | | |.| | | | | |.| | | | | | \\\\",
        "   //  | | | | | | | |.| | | | |.| | | | | |.|  \\\\",
        "  </   | | | | | | | | | | | | | | | | | | | |   \\>",
        "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"",
    };
    int numLines2 = sizeof(asciiArt2) / sizeof(asciiArt2[0]);
    for (int i = 0; i < numLines2; ++i) {
        gotoxy(33, 21 + i);
        cout << asciiArt2[i];
    }
    
    gotoxy(10, 6); cout << "|   Ingrese ISBN:";  		
    gotoxy(10, 11); cout << "|   Ingrese titulo del libro:";
    gotoxy(10, 13); cout << "|   Ingrese autor:";
    gotoxy(10, 15); cout << "|   Ingrese genero:";
    gotoxy(10, 17); cout << "|   Ingrese stock:";
}

void pantallaPrincipal(int opcionSeleccionada) {
    dibujarCuadro(0, 0, 120, 30); // MARCO BASE
    string asciiArt[] = {
        " _       _________ ______   _______  _______  _______  _______  _______ _________",
        "( \\      \\__   __/(  ___ \\ (  ____ )(  ___  )(  ____ \\(  ____ \\(  ____ \\\\__   __/",
        "| (         ) (   | (   ) )| (    )|| (   ) || (    \\/| (    \\/| (    \\/   ) (   ",
        "| |         | |   | (__/ / | (____)|| |   | || |      | (__    | (_____    | |   ",
        "| |         | |   |  __ (  |     __)| |   | || | ____ |  __)   (_____  )   | |   ",
        "| |         | |   | (  \\ \\ | (\\ (   | |   | || | \\_  )| (            ) |   | |   ",
        "| (____/\\___) (___| )___) )| ) \\ \\__| (___) || (___) || (____/\\/\\____) |   | |   ",
        "(_______/\\_______/|/ \\___/ |/   \\__/(_______)(_______)(_______/\\_______)   )_(   "
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(20, 1 + i);
        cout << asciiArt[i];
    }

    string asciiArt2[] = {
        "                      ______ ______",
        "                    _/      Y      \\_",
        "                   // ~~ ~~ | ~~ ~  \\\\",
        "                  // ~ ~ ~~ | ~~~ ~~ \\\\",
        "                 //________.|.________\\\\",
        "                `----------`-'----------'",
    };
    int numLines2 = sizeof(asciiArt2) / sizeof(asciiArt2[0]);
    for (int i = 0; i < numLines2; ++i) {
        gotoxy(4, 12 + i);
        cout << asciiArt2[i];
    }

    string asciiArt3[] = {
        "         .--\"\"--.",
        " _______/        \\  ",
        "|_______          ;",
        "        \\        /",
        "         '--..--'",
    };
    int numLines3 = sizeof(asciiArt3) / sizeof(asciiArt3[0]);
    for (int i = 0; i < numLines3; ++i) {
        gotoxy(80, 12 + i);
        cout << asciiArt3[i];
    }
	
	// 2 superiores
    dibujarCuadro(7, 11, 50, 10, opcionSeleccionada == 0); 
    gotoxy(14, 18); cout << "R E G I S T R O   D E   L I B R O S";
    
    dibujarCuadro(64, 11, 50, 10, opcionSeleccionada == 1); 
    gotoxy(72, 18); cout << "B U S Q U E D A   D E   L I B R O S";
    
    // 3 inferiores
    dibujarCuadro(7, 22, 33, 5, opcionSeleccionada == 2);
    gotoxy(11, 23); cout << "D E V O L U C I O N   D E";
    gotoxy(18, 25); cout << "L I B R O S";
    
    dibujarCuadro(44, 22, 33, 5, opcionSeleccionada == 3); 
    gotoxy(49, 23); cout << "H I S T O R I A L   D E";
    gotoxy(53, 25); cout << "P R E S T A M O S";
    
    dibujarCuadro(81, 22, 33, 5, opcionSeleccionada == 4); 
    gotoxy(83, 23); cout << "R E G I S T R A R   N U E V O";
    gotoxy(91, 25); cout << "U S U A R I O";
    
    gotoxy(0, 0);
}

void pantallaBusquedaDeLibros(int opcionSeleccionada, string generoSeleccionado = "") {
    dibujarCuadro(0, 0, 121, 9); // MARCO BASE
    dibujarCuadro(0, 0, 121, 5); // MARCO CATEGORIAS
    gotoxy(0, 4); cout << (char)204;
    gotoxy(120, 4); cout << (char)185;

    gotoxy(6, 2); cout << "Seleccione categoria:";

    dibujarCuadro(33, 1, 17, 3, opcionSeleccionada == 0);
    gotoxy(36, 2); cout << "G E N E R O";

    dibujarCuadro(55, 1, 17, 3, opcionSeleccionada == 1);
    gotoxy(58, 2); cout << "T I T U L O";

    dibujarCuadro(77, 1, 17, 3, opcionSeleccionada == 2);
    gotoxy(82, 2); cout << "I S B N";

    dibujarCuadro(99, 1, 17, 3, opcionSeleccionada == 3);
    gotoxy(103, 2); cout << "A U T O R";

    dibujarCuadro(0, 4, 121, 3);
    gotoxy(0, 4); cout << (char)204;
    gotoxy(0, 6); cout << (char)204;
    gotoxy(120, 4); cout << (char)185;
    gotoxy(120, 6); cout << (char)185;

   
    gotoxy(22, 7); cout << "Ingrese ISBN:";

    dibujarCuadro(0, 6, 17, 3, opcionSeleccionada == 4);
    gotoxy(2, 7); cout << "PRESTAR LIBRO";
}

void pantallaHistorialDePrestamos(){
	string asciiArt[] = {
        "     ___  __ ___ _   _  ___            _   _    _   _   _/ __ ___           _   __   ",
        " |_|  |  (_   | / \\ |_)  |   /\\  |    | \\ |_   |_) |_) |_ (_   |  /\\  |\\/| / \\ (_  o ",
        " | | _|_ __)  | \\_/ | \\ _|_ /--\\ |_   |_/ |_   |   | \\ |_ __)  | /--\\ |  | \\_/ __) o ",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(5, 0 + i);
        cout << asciiArt[i];
    }
}

void pantallaDevolucionDeLibros(int opcionSeleccionada){
	dibujarCuadro(0, 0, 121, 30); // MARCO BASE
	
	string asciiArt[] = {
        "  _   _       _          _ ___  /          _   _      ___  _   _   _   __ ",
        " | \\ |_ \\  / / \\ |  | | /   |  / \\ |\\ |   | \\ |_   |   |  |_) |_) / \\ (_",
        " |_/ |_  \\/  \\_/ |_ |_| \\_ _|_ \\_/ | \\|   |_/ |_   |_ _|_ |_) | \\ \\_/ __)",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(25, 1 + i);
        cout << asciiArt[i];
    }
    
    string asciiArt2[] = {
        "                .-~~~~~~~~~-._       _.-~~~~~~~~~-.",
        "            __.'              ~.   .~              `.__",
        "          .'//                  \\./                  \\\\`.",
        "        .'//                     |                     \\\\`.",
        "      .'// .-~\"\"\"\"\"\"\"~~~~-._     |     _,-~~~~\"\"\"\"\"\"\"~-. \\\\`.",
        "    .'//.-\"                 `-.  |  .-'                 \"-.\\\\`.",
        "  .'//______.============-..   \\ | /   ..-============.______\\\\`.",
        ".'______________________________\\|/______________________________`.",
    };
    int numLines2 = sizeof(asciiArt2) / sizeof(asciiArt2[0]);
    for (int i = 0; i < numLines2; ++i) {
        gotoxy(27, 20 + i);
        cout << asciiArt2[i];
    }
    
    dibujarCuadro(20, 6, 85, 5, opcionSeleccionada == 0); 
	gotoxy(25, 8); cout << "Ingrese codigo de prestamo:";  
	dibujarCuadro(47, 16, 25, 3, opcionSeleccionada == 1); gotoxy(53, 17); cout << "A C E P T A R";   
}

void pantallaRegistroUsuario(int opcionSeleccionada){
	dibujarCuadro(0, 0, 121, 30); // MARCO BASE
	
	string asciiArt2[] = {
        "  _  _        _ ___  _             _ ___  /          _   _    _      ___ _   __ ",
        " /  / \\ |\\ | |_  |  |_) |\\/|  /\\  /   |  / \\ |\\ |   | \\ |_   | \\  /\\  | / \\ (_  ",
        " \\_ \\_/ | \\| |  _|_ | \\ |  | /--\\ \\_ _|_ \\_/ | \\|   |_/ |_   |_/ /--\\ | \\_/ __) ",
    };
    int numLines2 = sizeof(asciiArt2) / sizeof(asciiArt2[0]);
    for (int i = 0; i < numLines2; ++i) {
        gotoxy(22, 1 + i);
        cout << asciiArt2[i];
    }
	
	gotoxy(18, 6); cout << "Titulo: ";
	
	dibujarCuadro(20, 8, 85, 5, opcionSeleccionada == 0); 
	gotoxy(25, 10); cout << "Codigo de biblioteca: ";

	
	string asciiArt[] = {
        "            _ _       _ _       _ _       _ _",
        "       .-. | | | .-. | | | .-. | | | .-. |.| |",
        "       | |_|.| |_| |_| |.|_| |_| |.|_| |_| | |",
        "     />| | |.|.| | | |.|.| | | |.|.| | | |.|.|<\\",
        "    // | | | |.| | | |.| | | | | |.| | | | | | \\\\",
        "   //  | | | | | | | |.| | | | |.| | | | | |.|  \\\\",
        "  </   | | | | | | | | | | | | | | | | | | | |   \\>",
        "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"",
    };
    int numLines = sizeof(asciiArt) / sizeof(asciiArt[0]);
    for (int i = 0; i < numLines; ++i) {
        gotoxy(33, 21 + i);
        cout << asciiArt[i];
    }
    
    dibujarCuadro(47, 17, 25, 3, opcionSeleccionada == 1); gotoxy(53, 18); cout << "A C E P T A R"; 
}

