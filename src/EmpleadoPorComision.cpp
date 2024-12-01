#include "../include/EmpleadoPorComision.h"

// Constructor
EmpleadoPorComision::EmpleadoPorComision(string nom, string ap, int numEmp, double salBase, int semAn, double ventas, double porcen)
    : EmpleadoAsalariado(nom, ap, numEmp, salBase, semAn)
{
    this->montoTotalVentas = ventas;
    this->porcentajeComision = porcen;
    this->tipoEmpleado = TipoEmpleado::PorComision;
}

double EmpleadoPorComision::calcularSalario()
{
    this->salarioBase = EmpleadoAsalariado::calcularSalario();
    double comision = montoTotalVentas * (porcentajeComision / 100);
    return salarioBase + comision;
}

std::string EmpleadoPorComision::getInfo() const
{
    return EmpleadoAsalariado::getInfo() + "\n- Monto total de ventas: " + std::to_string(montoTotalVentas) + "\n- Porcentaje de comisión: " + std::to_string(porcentajeComision);
}

void EmpleadoPorComision::setVentas(double ventas) { this->montoTotalVentas = ventas; }
void EmpleadoPorComision::setPorcenComision(double porcen) { this->porcentajeComision = porcen; }

double EmpleadoPorComision::getVentas() { return montoTotalVentas; }
double EmpleadoPorComision::getPorcenComision() { return porcentajeComision; }