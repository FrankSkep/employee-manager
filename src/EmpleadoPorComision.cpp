#include "../include/EmpleadoPorComision.h"

// Constructor
EmpleadoPorComision::EmpleadoPorComision(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales, double montoVentas, double porcentajeComision)
    : EmpleadoAsalariado(nombre, apellido, numeroEmpleado, salarioBase, semanasAnuales)
{
    this->montoVentas = montoVentas;
    this->porcentajeComision = porcentajeComision;
    this->tipoEmpleado = TipoEmpleado::PorComision;
}

double EmpleadoPorComision::calcularSalario()
{
    this->salarioBase = EmpleadoAsalariado::calcularSalario();
    double comision = montoVentas * (porcentajeComision / 100);
    return salarioBase + comision;
}

std::string EmpleadoPorComision::getInfo() const
{
    return EmpleadoAsalariado::getInfo() + "\n- Monto total de ventas: " + std::to_string(montoVentas) + "\n- Porcentaje de comisión: " + std::to_string(porcentajeComision);
}