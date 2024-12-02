#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>

enum class TipoEmpleado
{
    PorHoras,
    Asalariado,
    PorComision
};

class Empleado
{
protected:
    std::string nombre;
    std::string apellido;
    int numeroEmpleado;
    double salarioBase;
    TipoEmpleado tipoEmpleado;

public:
    Empleado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase);

    virtual double CalcularSalario() = 0;
    virtual std::string GetInfo() const;

    // Getters y Setters
    std::string getNombre() const { return nombre; }
    std::string GetApellido() const { return apellido; }
    int GetNumeroEmpleado() const { return numeroEmpleado; }
    double GetSalarioBase() const { return salarioBase; }
    TipoEmpleado GetTipoEmpleado() const { return tipoEmpleado; }
    std::string GetTipoEmpleadoString() const;

    void SetNombre(const std::string &nom) { nombre = nom; }
    void SetApellido(const std::string &ap) { apellido = ap; }
    void SetNumeroEmpleado(int num) { numeroEmpleado = num; }
    void SetSalarioBase(double sal) { salarioBase = sal; }
};

#endif