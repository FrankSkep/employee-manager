#include "../include/EmpleadoPorHoras.h"

// Constructor
EmpleadoPorHoras::EmpleadoPorHoras(string nom, string ap, int numEmp, double salBase, int horasT, float tarifa) : Empleado(nom, ap, numEmp, salBase)
{
    this->horasTrabajadas = horasT;
    this->tarifaHora = tarifa;
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

void EmpleadoPorHoras::setHoras(int horasT) { this->horasTrabajadas = horasT; }
void EmpleadoPorHoras::setTarifa(float tarifaH) { this->tarifaHora = tarifaH; }