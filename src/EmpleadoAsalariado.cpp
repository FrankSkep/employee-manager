#include "../include/EmpleadoAsalariado.h"

// Constructor
EmpleadoAsalariado::EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales) : Empleado(nombre, apellido, numeroEmpleado, salarioBase)
{
    this->semanasAnuales = semanasAnuales;
    this->tipoEmpleado = TipoEmpleado::Asalariado;
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