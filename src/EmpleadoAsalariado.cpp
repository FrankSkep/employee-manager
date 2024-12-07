#include "../include/EmpleadoAsalariado.h"

// Constructor
EmpleadoAsalariado::EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, int edad, double salarioBase, int semanasAnuales) : Empleado(nombre, apellido, edad, salarioBase)
{
    this->semanasAnuales = semanasAnuales;
    this->tipoEmpleado = TipoEmpleado::ASALARIADO;
}

EmpleadoAsalariado::EmpleadoAsalariado(int numeroEmpleado, const std::string &nombre, const std::string &apellido, int edad, double salarioBase, int semanasAnuales) : Empleado(numeroEmpleado, nombre, apellido, edad, salarioBase)
{
    this->semanasAnuales = semanasAnuales;
    this->tipoEmpleado = TipoEmpleado::ASALARIADO;
}

double EmpleadoAsalariado::CalcularSalario()
{
    if (semanasAnuales == 0)
    {
        return 0.0;
    }
    int mesesTrabajados = semanasAnuales / 4;
    return salarioBase / mesesTrabajados;
}

std::string EmpleadoAsalariado::GetInfo() const
{
    return Empleado::GetInfo() + "\n- Semanas anuales: " + std::to_string(semanasAnuales);
}