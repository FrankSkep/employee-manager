#include "Empleado.h"

// Constructor
Empleado::Empleado(const std::string& nom, const std::string& ap, int numEmp, double salBase)
{
    this->nombre = nom;
    this->apellido = ap;
    this->numEmp = numEmp;
    this->salarioBase = salBase;
}

std::string Empleado::getInfo() const
{
    return "- Nombre: " + this->nombre + "\n- Apellido: " + this->apellido + "\n- Numero de empleado: " + std::to_string(this->numEmp);
}