#include "../include/EmpleadoPorHoras.h"

// Constructor
EmpleadoPorHoras::EmpleadoPorHoras(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int horasTrabajadas, float tarifaHora)
    : Empleado(nombre, apellido, numeroEmpleado, salarioBase)
{
    this->horasTrabajadas = horasTrabajadas;
    this->tarifaHora = tarifaHora;
    this->tipoEmpleado = TipoEmpleado::POR_HORAS;
}

double EmpleadoPorHoras::CalcularSalario()
{
    return tarifaHora * horasTrabajadas;
}

std::string EmpleadoPorHoras::GetInfo() const
{
    return Empleado::GetInfo() + "\n- Horas trabajadas: " + std::to_string(horasTrabajadas) + "\n- Tarifa por hora: " + std::to_string(tarifaHora);
}