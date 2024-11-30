#ifndef UTILS_H
#define UTILS_H

#include <cctype>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

// Lee un numero de cualquier tipo indicado entre <>
template <typename T>
T getNum(const string &msg)
{
    string input;
    T numero;

    while (true)
    {
        cout << msg;
        getline(cin, input);
        stringstream ss(input);

        // Verificar si la conversion fue exitosa y si no hay caracteres adicionales
        if (ss >> numero && ss.eof())
        {
            break;
        }

        cout << "Error: Ingrese un numero valido" << endl;
    }
    return numero;
}

// Lee un numero de cualquier tipo indicado entre <>, en un rango
template <typename T>
T getNum_R(const string &msg, T ri, T rf)
{
    string input;
    T numero;

    while (true)
    {
        cout << msg;
        getline(cin, input);
        stringstream ss(input);

        if (ss >> numero && ss.eof() && numero >= ri && numero <= rf)
        {
            break;
        }

        cout << "Error: Ingrese un numero valido entre " << ri << " y " << rf << "." << endl;
    }
    return numero;
}

int numAleatorio(int ri, int rf)
{
    return rand() % (rf - ri + 1) + ri;
}

string convMayus(const string &palabra)
{
    string resultado = palabra;
    for (char &c : resultado)
    {
        c = toupper(static_cast<unsigned char>(c));
    }
    return resultado;
}

bool isNumeric(const string &str)
{
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

#endif