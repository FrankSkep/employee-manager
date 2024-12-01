#ifndef EMPLEADOASALARIADO_H
#define EMPLEADOASALARIADO_H

#include "Empleado.h"

class EmpleadoAsalariado : public Empleado
{
private:
    int semanasAnuales;

public:
    EmpleadoAsalariado(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales);

    double calcularSalario() override;
    std::string getInfo() const override;

    // Getters y Setters
    int getSemanasAnuales() const { return semanasAnuales; };
    void setSemanasAnuales(int semanasAnuales) { this->semanasAnuales = semanasAnuales; };
};

#endif