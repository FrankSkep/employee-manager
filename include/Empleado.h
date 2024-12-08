#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>

enum class TipoEmpleado
{
    POR_HORAS,
    ASALARIADO,
    POR_COMISION
};

class Empleado
{
protected:
    int numeroEmpleado;
    std::string nombre;
    std::string apellido;
    int edad;
    double salarioBase;
    TipoEmpleado tipoEmpleado;

public:
    Empleado(const std::string &nombre, const std::string &apellido, int edad, double salarioBase);
    Empleado(int numeroEmpleado, const std::string &nombre, const std::string &apellido, int edad, double salarioBase);

    virtual double CalcularSalario() = 0; // Metodo virtual puro
    virtual std::string GetInfo() const;  // Metodo virtual

    // Getters y Setters
    int GetNumeroEmpleado() const { return numeroEmpleado; }
    std::string GetNombre() const { return nombre; }
    std::string GetApellido() const { return apellido; }
    int GetEdad() const { return edad; }
    double GetSalarioBase() const { return salarioBase; }
    TipoEmpleado GetTipoEmpleado() const { return tipoEmpleado; }
    std::string GetTipoEmpleadoString() const;
    void SetNumeroEmpleado(int numeroEmpleado) { this->numeroEmpleado = numeroEmpleado; }
    void SetNombre(const std::string &nombre) { this->nombre = nombre; }
    void SetApellido(const std::string &apellido) { this->apellido = apellido; }
    void SetEdad(int edad) { this->edad = edad; }
    void SetSalarioBase(double salarioBase) { this->salarioBase = salarioBase; }
};

#endif