#include "../include/EmpleadoAsalariado.h"

// Constructor
EmpleadoAsalariado::EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, double salarioBase, int semanasAnuales) : Empleado(nombre, apellido, salarioBase)
{
    this->semanasAnuales = semanasAnuales;
    this->tipoEmpleado = TipoEmpleado::ASALARIADO;
}

double EmpleadoAsalariado::CalcularSalario()
{
    int mesesTrabajados = semanasAnuales / 4;
    return salarioBase / mesesTrabajados;
}

std::string EmpleadoAsalariado::GetInfo() const
{
    return Empleado::GetInfo() + "\n- Semanas anuales: " + std::to_string(semanasAnuales);
}