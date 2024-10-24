#include "commonFunctions.h"

string trim(const string& str) {
    auto start = find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
        });

    auto end = find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base();

    if (start >= end) {
        return "";
    }

    return string(start, end);
}

bool validarSoloDigitosEnCadena(const std::string& str) {
    return all_of(str.begin(), str.end(), [](unsigned char c) { return isdigit(c); });
}

bool validarSoloEspaciosEnBlanco(const string& str) {
    return all_of(str.begin(), str.end(), [](unsigned char c) { return isspace(c); });
}

bool validarFecha(const std::string& fecha) {
    std::regex formatoFecha("\\d{4}-\\d{2}-\\d{2}");

    if (!std::regex_match(fecha, formatoFecha)) {
        return false;
    }

    int anio = std::stoi(fecha.substr(0, 4));
    int mes = std::stoi(fecha.substr(5, 2));
    int dia = std::stoi(fecha.substr(8, 2));

    if (mes < 1 || mes > 12) {
        return false;
    }

    int diasEnMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        diasEnMes[1] = 29;
    }

    if (dia < 1 || dia > diasEnMes[mes - 1]) {
        return false;
    }

    return true;
}

string obtenerFechaDevolucion(int dias) {
    using namespace chrono;

    auto ahora = system_clock::now();
    auto fechaDevolucion = ahora + hours(24 * dias);
    time_t tiempoDevolucion = system_clock::to_time_t(fechaDevolucion);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tiempoDevolucion));
    return string(buffer);
}

string obtenerFechaActual() {
    using namespace chrono;

    auto ahora = system_clock::now();
    time_t tiempoActual = system_clock::to_time_t(ahora);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&tiempoActual));
    return string(buffer);
}
