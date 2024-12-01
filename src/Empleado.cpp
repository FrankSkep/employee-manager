#include "../include/Empleado.h"

// Constructor
Empleado::Empleado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->numeroEmpleado = numeroEmpleado;
    this->salarioBase = salarioBase;
}

std::string Empleado::getInfo() const
{
    return "- Nombre: " + this->nombre + "\n- Apellido: " + this->apellido + "\n- Numero de empleado: " + std::to_string(this->numeroEmpleado) + "\n- Salario base: $" + std::to_string(this->salarioBase);
}