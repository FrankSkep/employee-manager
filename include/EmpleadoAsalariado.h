#ifndef EMPLEADOASALARIADO_H
#define EMPLEADOASALARIADO_H

#include "Empleado.h"

class EmpleadoAsalariado : public Empleado
{
private:
    int semanasAnuales;

public:
    EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales);

    double CalcularSalario() override;
    std::string GetInfo() const override;

    // Getters y Setters
    int GetSemanasAnuales() const { return semanasAnuales; };
    void SetSemanasAnuales(int semanasAnuales) { this->semanasAnuales = semanasAnuales; };
};

#endif