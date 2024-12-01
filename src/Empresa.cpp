#include "../include/Empresa.h"

Empresa::Empresa()
{
    this->nombre = "";
    this->direccion = "";
    this->telefono = "";
}

Empresa::Empresa(std::string nombre, std::string direccion, std::string telefono)
{
    this->nombre = nombre;
    this->direccion = direccion;
    this->telefono = telefono;
}

void Empresa::agregarEmpleado(Empleado *empleado)
{
    empleados.push_back(std::shared_ptr<Empleado>(empleado));
}

void Empresa::eliminarEmpleado()
{
}

void Empresa::modificarEmpleado()
{
}

long Empresa::generarIDUnico()
{
    return 0;
}
