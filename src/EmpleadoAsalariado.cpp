#include "../include/EmpleadoAsalariado.h"

// Constructor
EmpleadoAsalariado::EmpleadoAsalariado(string nom, string ap, int numEmp, double salBase, int semAn) : Empleado(nom, ap, numEmp, salBase)
{
    this->semanasAnuales = semAn;
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

void EmpleadoAsalariado::setSemanas(int sem) { this->semanasAnuales = sem; }
int EmpleadoAsalariado::getSemanas() { return semanasAnuales; }