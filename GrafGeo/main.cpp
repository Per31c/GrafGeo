#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

// Declaraciones de constantes
const int MAX_ALTO_PANTALLA = 100;
const int MAX_ANCHO_PANTALLA = 100;
const int TECLA_F12 = 123;
const int TECLA_F1 = 112; // F1 para Triangulo
const int TECLA_F2 = 113; // F2 para Cuadrado
const int TECLA_F3 = 114; // F3 para Rectangulo
const int TECLA_F4 = 115; // F4 para Circulo
const int TECLA_F5 = 116; // F5 para Linea
const int TECLA_F6 = 117; // F6 para Rombo
const int TECLA_F7 = 118; // F7 para Hexagono
const int TECLA_F8 = 119; // F8 para Nuevo Caracter
const int TECLA_F9 = 120; // F9 para Limpiar Pantalla
const int TECLA_F10 = 121; // F10 para Color de Caracter
const int TECLA_CTRL_A = 1; // Ctrl + A para Abrir Archivo

// Definiciones de variables globales
int anchoPantalla = 0, altoPantalla = 0;
char contenidoPantalla[MAX_ALTO_PANTALLA][MAX_ANCHO_PANTALLA];
int figuraSeleccionada = 0;
char caracterDibujo = '*'; // Caracter por defecto para dibujar figuras
std::vector<std::string> figurasDibujadas;

// Declaraciones de funciones
char obtenerEntradaUsuario();
void procesarEntradaUsuario(char entrada);
void calcularPosicionCircular(int &x, int &y);
double calcularDistancia(int x1, int y1, int x2, int y2);
void limpiarPantalla();
void grabarPantalla(std::string nombreArchivo);
void abrirArchivo(std::string nombreArchivo);
void dibujarTriangulo();
void dibujarCuadrado();
void dibujarRectangulo();
void dibujarCirculo(int x_centro, int y_centro, int radio);
void dibujarLinea(int x0, int y0, int x1, int y1);
void dibujarRombo();
void dibujarHexagono();
void mostrarMenuSeleccion();
void seleccionarFigura(char entradaUsuario);
void mostrarMenuOpciones();
void modificarOpciones(char entradaUsuario);
void borrarUltimaFigura();
void borrarFigura(int x, int y);
void borrarTodo();
void mostrarMenuNuevo();
void seleccionarOpcionNuevo(char entradaUsuario);
void dibujarPunto(int x, int y); // Logica para dibujar un punto en las coordenadas (x, y)

// Implementacion de funciones
char obtenerEntradaUsuario() {
    char entrada;
    std::cin >> entrada;
    return entrada;
}

void procesarEntradaUsuario(char entrada) {
    switch (entrada) {
        case TECLA_F1:
        case TECLA_F2:
        case TECLA_F3:
        case TECLA_F4:
        case TECLA_F5:
        case TECLA_F6:
        case TECLA_F7:
        case TECLA_F8:
            figuraSeleccionada = entrada;
            mostrarMenuOpciones();
            break;
        case TECLA_F9:
            limpiarPantalla();
            break;
        case TECLA_F10:
            // Implementar seleccion de color del caracter
            break;
        case TECLA_F12:
            grabarPantalla("pantalla.txt");
            break;
        case TECLA_CTRL_A:
            std::string nombreArchivo;
            std::cout << "Ingrese el nombre del archivo a abrir: ";
            std::cin >> nombreArchivo;
            abrirArchivo(nombreArchivo);
            break;
        default:
            // Manejar otras teclas o casos no especificados
            break;
    }
}

void calcularPosicionCircular(int &x, int &y) {
    // Calculamos la distancia desde el centro de la pantalla
    double distanciaDesdeCentro = calcularDistancia(x, y, anchoPantalla / 2, altoPantalla / 2);
    
    // Si la distancia es mayor que el radio de la pantalla circular, ajustamos la posicion
    if (distanciaDesdeCentro > std::min(anchoPantalla, altoPantalla) / 2) {
        // Calculamos el angulo de la posicion actual
        double angulo = atan2(y - altoPantalla / 2, x - anchoPantalla / 2);

        // Calculamos las nuevas coordenadas basadas en el angulo y el radio
        x = static_cast<int>(anchoPantalla / 2 + (std::min(anchoPantalla, altoPantalla) / 2) * cos(angulo));
        y = static_cast<int>(altoPantalla / 2 + (std::min(anchoPantalla, altoPantalla) / 2) * sin(angulo));
    }
}

double calcularDistancia(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void limpiarPantalla() {
    for (int y = 0; y < altoPantalla; ++y) {
        for (int x = 0; x < anchoPantalla; ++x) {
            contenidoPantalla[y][x] = ' ';
        }
    }
}

void grabarPantalla(std::string nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int y = 0; y < altoPantalla; ++y) {
            for (int x = 0; x < anchoPantalla; ++x) {
                archivo << contenidoPantalla[y][x];
            }
            archivo << std::endl;
        }
        std::cout << "La pantalla se ha guardado correctamente en el archivo: " << nombreArchivo << std::endl;
        archivo.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
    }
}

void abrirArchivo(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        limpiarPantalla();
        std::string linea;
        int y = 0;
        while (getline(archivo, linea) && y < altoPantalla) {
            for (int x = 0; x < linea.length() && x < anchoPantalla; ++x) {
                contenidoPantalla[y][x] = linea[x];
            }
            ++y;
        }
        archivo.close();
        std::cout << "El archivo se ha abierto correctamente: " << nombreArchivo << std::endl;
    } else {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
    }
}

void dibujarTriangulo() {
    int base;
    std::cout << "Ingrese el tamano de la base del triangulo: ";
    std::cin >> base;

    // Calculamos las coordenadas de los vertices del triangulo
    int x1 = anchoPantalla / 2;
    int y1 = 0;
    int x2 = x1 - base / 2;
    int y2 = altoPantalla - 1;
    int x3 = x1 + base / 2;
    int y3 = y2;

    // Dibujamos el triangulo usando la funcion dibujarLinea()
    dibujarLinea(x1, y1, x2, y2);
    dibujarLinea(x2, y2, x3, y3);
    dibujarLinea(x3, y3, x1, y1);
}

void dibujarCuadrado() {
    int lado;
    std::cout << "Ingrese el tamano de un lado del cuadrado: ";
    std::cin >> lado;

    // Calculamos las coordenadas de la esquina superior izquierda del cuadrado
    int x1 = anchoPantalla / 2 - lado / 2;
    int y1 = altoPantalla / 2 - lado / 2;

    // Dibujamos el cuadrado utilizando la funcion dibujarLinea()
    dibujarLinea(x1, y1, x1 + lado, y1);
    dibujarLinea(x1 + lado, y1, x1 + lado, y1 + lado);
    dibujarLinea(x1 + lado, y1 + lado, x1, y1 + lado);
    dibujarLinea(x1, y1 + lado, x1, y1);
}

void dibujarRectangulo() {
    int base, altura;
    std::cout << "Ingrese el tamano de la base del rectangulo: ";
    std::cin >> base;
    std::cout << "Ingrese el tamano de la altura del rectangulo: ";
    std::cin >> altura;

    // Calculamos las coordenadas de la esquina superior izquierda del rectangulo
    int x1 = anchoPantalla / 2 - base / 2;
    int y1 = altoPantalla / 2 - altura / 2;

    // Dibujamos el rectangulo utilizando la funcion dibujarLinea()
    dibujarLinea(x1, y1, x1 + base, y1);
    dibujarLinea(x1 + base, y1, x1 + base, y1 + altura);
    dibujarLinea(x1 + base, y1 + altura, x1, y1 + altura);
    dibujarLinea(x1, y1 + altura, x1, y1);
}

void dibujarCirculo(int x_centro, int y_centro, int radio) {
    for (int x = 0; x <= radio; ++x) {
        int y = round(sqrt(radio * radio - x * x));
        dibujarPunto(x_centro + x, y_centro + y);
        dibujarPunto(x_centro - x, y_centro + y);
        dibujarPunto(x_centro + x, y_centro - y);
        dibujarPunto(x_centro - x, y_centro - y);
    }
}

void dibujarLinea(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        dibujarPunto(x0, y0);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void dibujarRombo() {
    int lado;
    std::cout << "Ingrese el tamano de un lado del rombo: ";
    std::cin >> lado;

    // Calculamos las coordenadas de los vertices del rombo
    int x1 = anchoPantalla / 2;
    int y1 = 0;
    int x2 = x1 - lado / 2;
    int y2 = altoPantalla / 2;
    int x3 = x1;
    int y3 = altoPantalla - 1;
    int x4 = x1 + lado / 2;

    // Dibujamos el rombo usando la funcion dibujarLinea()
    dibujarLinea(x1, y1, x2, y2);
    dibujarLinea(x2, y2, x3, y3);
    dibujarLinea(x3, y3, x4, y2);
    dibujarLinea(x4, y2, x1, y1);
}

void dibujarHexagono() {
    int lado;
    std::cout << "Ingrese el tamano de un lado del hexagono: ";
    std::cin >> lado;

    // Calculamos las coordenadas de los vertices del hexagono
    int x_centro = anchoPantalla / 2;
    int y_centro = altoPantalla / 2;
    int radio = lado / 2;

    // Dibujamos el hexagono calculando los angulos y las coordenadas de los vertices
    for (int i = 0; i < 6; ++i) {
        int x1 = x_centro + radio * cos(i * M_PI / 3);
        int y1 = y_centro + radio * sin(i * M_PI / 3);
        int x2 = x_centro + radio * cos((i + 1) * M_PI / 3);
        int y2 = y_centro + radio * sin((i + 1) * M_PI / 3);
        dibujarLinea(x1, y1, x2, y2);
    }
}

void mostrarMenuSeleccion() {
    std::cout << "Seleccione una figura geometrica:" << std::endl;
    std::cout << "F1: Triangulo" << std::endl;
    std::cout << "F2: Cuadrado" << std::endl;
    std::cout << "F3: Rectangulo" << std::endl;
    std::cout << "F4: Circulo" << std::endl;
    std::cout << "F5: Linea" << std::endl;
    std::cout << "F6: Rombo" << std::endl;
    std::cout << "F7: Hexagono" << std::endl;
}

void seleccionarFigura(char entradaUsuario) {
    switch (entradaUsuario) {
        case TECLA_F1:
            dibujarTriangulo();
            break;
        case TECLA_F2:
            dibujarCuadrado();
            break;
        case TECLA_F3:
            dibujarRectangulo();
            break;
        case TECLA_F4:
            dibujarCirculo(anchoPantalla / 2, altoPantalla / 2, 10); // Ejemplo: Dibuja un circulo en el centro con radio 10
            break;
        case TECLA_F5:
            dibujarLinea(0, 0, anchoPantalla - 1, altoPantalla - 1); // Ejemplo: Dibuja una linea diagonal desde la esquina superior izquierda hasta la esquina inferior derecha
            break;
        case TECLA_F6:
            dibujarRombo();
            break;
        case TECLA_F7:
            dibujarHexagono();
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
    }
}

void mostrarMenuOpciones() {
    std::cout << "Menu de Opciones:" << std::endl;
    std::cout << "F9: Limpiar Pantalla" << std::endl;
    std::cout << "F10: Color de Caracter" << std::endl;
    std::cout << "F12: Grabar Pantalla" << std::endl;
    std::cout << "Ctrl + A: Abrir Archivo" << std::endl;
}

void modificarOpciones(char entradaUsuario) {
    switch (entradaUsuario) {
        case TECLA_F8:
            // Implementar seleccion de nuevo caracter
            break;
        case TECLA_F9:
            limpiarPantalla();
            break;
        case TECLA_F10:
            // Implementar seleccion de color de caracter
            break;
        case TECLA_F12:
            grabarPantalla("pantalla_grabada.txt");
            break;
        case TECLA_CTRL_A:
            std::string nombreArchivo;
            std::cout << "Ingrese el nombre del archivo que desea abrir: ";
            std::cin >> nombreArchivo;
            abrirArchivo(nombreArchivo);
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
    }
}

void borrarFigura() {
    // Implementacion para borrar una figura en la posicion actual del cursor
    int x, y;
    std::cout << "Ingrese las coordenadas (x, y) de la figura que desea borrar: ";
    std::cin >> x >> y;
    borrarFigura(x, y);
}

void borrarTodo() {
    // Implementacion para borrar todas las figuras de la pantalla
    limpiarPantalla();
    figurasDibujadas.clear();
    std::cout << "Se han borrado todas las figuras de la pantalla." << std::endl;
}

void mostrarMenuNuevo() {
    std::cout << "Seleccione una opcion:" << std::endl;
    std::cout << "F1: Dibujar figura" << std::endl;
    std::cout << "F2: Modificar opciones" << std::endl;
    std::cout << "F3: Borrar figura" << std::endl;
    std::cout << "F4: Borrar todo" << std::endl;
    std::cout << "F5: Salir" << std::endl;
}

void seleccionarOpcionNuevo(char entradaUsuario) {
    switch (entradaUsuario) {
        case TECLA_F1:
            mostrarMenuSeleccion();
            char opcionFigura;
            std::cin >> opcionFigura;
            seleccionarFigura(opcionFigura);
            break;
        case TECLA_F2:
            mostrarMenuOpciones();
            char opcionOpciones;
            std::cin >> opcionOpciones;
            modificarOpciones(opcionOpciones);
            break;
        case TECLA_F3:
            borrarFigura();
            break;
        case TECLA_F4:
            borrarTodo();
            break;
        case TECLA_F5:
            std::cout << "Saliendo del programa..." << std::endl;
            // Salir del programa
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
    }
}

int main() {
    // Codigo principal
    std::cout << "Bienvenido al programa de dibujo geometrico." << std::endl;
    std::cout << "Presione las flechas del teclado para mover el cursor y presione F12 para comenzar." << std::endl;

    // Test para verificar movimiento del cursor
    char testEntrada;
    do {
        testEntrada = obtenerEntradaUsuario();
        procesarEntradaUsuario(testEntrada);
    } while (testEntrada != TECLA_F12);

    // Comienza el proceso de dibujo
    bool salir = false;
    do {
        mostrarMenuNuevo();
        char entradaUsuario = obtenerEntradaUsuario();
        seleccionarOpcionNuevo(entradaUsuario);

        std::cout << "¿Desea dibujar otra figura? (s/n): ";
        char opcion;
        std::cin >> opcion;
        if (opcion == 'n') {
            salir = true;
        }
    } while (!salir);

    std::cout << "¡Gracias por usar el programa de dibujo geometrico!" << std::endl;
    return 0;
}