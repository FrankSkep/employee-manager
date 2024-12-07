#include "../include/EmpleadoPorComision.h"

// Constructor
EmpleadoPorComision::EmpleadoPorComision(const std::string &nombre, const std::string &apellido, int edad, double salarioBase, int semanasAnuales, double montoVentas, double porcentajeComision)
    : EmpleadoAsalariado(nombre, apellido, edad, salarioBase, semanasAnuales)
{
    this->montoVentas = montoVentas;
    this->porcentajeComision = porcentajeComision;
    this->tipoEmpleado = TipoEmpleado::POR_COMISION;
}

EmpleadoPorComision::EmpleadoPorComision(int numeroEmpleado, const std::string &nombre, const std::string &apellido, int edad, double salarioBase, int semanasAnuales, double montoVentas, double porcentajeComision)
    : EmpleadoAsalariado(numeroEmpleado, nombre, apellido, edad, salarioBase, semanasAnuales)
{
    this->montoVentas = montoVentas;
    this->porcentajeComision = porcentajeComision;
    this->tipoEmpleado = TipoEmpleado::POR_COMISION;
}

double EmpleadoPorComision::CalcularSalario()
{
    this->salarioBase = EmpleadoAsalariado::CalcularSalario();
    double comision = montoVentas * (porcentajeComision / 100);
    return salarioBase + comision;
}

std::string EmpleadoPorComision::GetInfo() const
{
    return EmpleadoAsalariado::GetInfo() + "\n- Monto total de ventas: " + std::to_string(montoVentas) + "\n- Porcentaje de comisión: " + std::to_string(porcentajeComision);
}