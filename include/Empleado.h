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
    double salarioBase;
    TipoEmpleado tipoEmpleado;

public:
    Empleado(const std::string &nombre, const std::string &apellido, double salarioBase);

    virtual double CalcularSalario() = 0;
    virtual std::string GetInfo() const;

    // Getters y Setters
    int GetNumeroEmpleado() const { return numeroEmpleado; }
    std::string GetNombre() const { return nombre; }
    std::string GetApellido() const { return apellido; }
    double GetSalarioBase() const { return salarioBase; }
    TipoEmpleado GetTipoEmpleado() const { return tipoEmpleado; }
    std::string GetTipoEmpleadoString() const;
    void SetNumeroEmpleado(int num) { numeroEmpleado = num; }
    void SetNombre(const std::string &nom) { nombre = nom; }
    void SetApellido(const std::string &ap) { apellido = ap; }
    void SetSalarioBase(double sal) { salarioBase = sal; }
};

#endif