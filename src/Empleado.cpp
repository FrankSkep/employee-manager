#include "../include/Empleado.h"

Empleado::Empleado(const std::string &nombre, const std::string &apellido, int edad, double salarioBase)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->salarioBase = salarioBase;
}

Empleado::Empleado(int numeroEmpleado, const std::string &nombre, const std::string &apellido, int edad, double salarioBase)
{
    this->numeroEmpleado = numeroEmpleado;
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->salarioBase = salarioBase;
}

std::string Empleado::GetInfo() const
{
    return "- Nombre: " + this->nombre + "\n- Apellido: " + this->apellido + "\n- Numero de empleado: " + std::to_string(this->numeroEmpleado) + "\n- Salario base: $" + std::to_string(this->salarioBase);
}

std::string Empleado::GetTipoEmpleadoString() const
{
    if (this->tipoEmpleado == TipoEmpleado::POR_HORAS)
    {
        return "Por Horas";
    }
    else if (this->tipoEmpleado == TipoEmpleado::ASALARIADO)
    {
        return "Asalariado";
    }
    else if (this->tipoEmpleado == TipoEmpleado::POR_COMISION)
    {
        return "Por Comision";
    }
    return "Desconocido"; // Valor de retorno por defecto
}