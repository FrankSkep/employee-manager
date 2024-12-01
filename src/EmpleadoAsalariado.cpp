#include "../include/EmpleadoAsalariado.h"

// Constructor
EmpleadoAsalariado::EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales) : Empleado(nombre, apellido, numeroEmpleado, salarioBase)
{
    this->semanasAnuales = semanasAnuales;
    this->tipoEmpleado = TipoEmpleado::Asalariado;
}

double EmpleadoAsalariado::calcularSalario()
{
    int mesesTrabajados = semanasAnuales / 4;
    return salarioBase / mesesTrabajados;
}

std::string EmpleadoAsalariado::getInfo() const
{
    return Empleado::getInfo() + "\n- Semanas anuales: " + std::to_string(semanasAnuales);
}