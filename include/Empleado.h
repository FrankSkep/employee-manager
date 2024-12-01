#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <iomanip>
using namespace std;

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
    int numEmp;
    double salarioBase;
    TipoEmpleado tipoEmpleado;

public:
    Empleado(const std::string &nom, const std::string &ap, int numEmp, double salBase);

    virtual ~Empleado() = default;

    virtual double calcularSalario() = 0;
    virtual std::string getInfo() const;

    TipoEmpleado getTipoEmpleado() const { return tipoEmpleado; }
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    int getNumEmp() const { return numEmp; }
    double getSalarioBase() const { return salarioBase; }

    void setNombre(const std::string &nom) { nombre = nom; }
    void setApellido(const std::string &ap) { apellido = ap; }
    void setNumEmp(int num) { numEmp = num; }
    void setSalarioBase(double sal) { salarioBase = sal; }
};

#endif