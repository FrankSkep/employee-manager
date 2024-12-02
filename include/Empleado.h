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

    virtual double calcularSalario() = 0;
    virtual std::string getInfo() const;

    // Getters y Setters
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    int getNumEmp() const { return numeroEmpleado; }
    double getSalarioBase() const { return salarioBase; }
    TipoEmpleado GetTipoEmpleado() const { return tipoEmpleado; }
    std::string GetTipoEmpleadoString() const;

    void setNombre(const std::string &nom) { nombre = nom; }
    void setApellido(const std::string &ap) { apellido = ap; }
    void setNumEmp(int num) { numeroEmpleado = num; }
    void setSalarioBase(double sal) { salarioBase = sal; }
};

#endif