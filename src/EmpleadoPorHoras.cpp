#include "../include/EmpleadoPorHoras.h"

// Constructor
EmpleadoPorHoras::EmpleadoPorHoras(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int horasTrabajadas, float tarifaHora)
    : Empleado(nombre, apellido, numeroEmpleado, salarioBase)
{
    this->horasTrabajadas = horasTrabajadas;
    this->tarifaHora = tarifaHora;
    this->tipoEmpleado = TipoEmpleado::PorHoras;
}

double EmpleadoPorHoras::calcularSalario()
{
    return tarifaHora * horasTrabajadas;
}

std::string EmpleadoPorHoras::getInfo() const
{
    return Empleado::getInfo() + "\n- Horas trabajadas: " + std::to_string(horasTrabajadas) + "\n- Tarifa por hora: " + std::to_string(tarifaHora);
}