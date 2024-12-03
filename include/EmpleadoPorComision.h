#ifndef EMPLEADOPORCOMISION_H
#define EMPLEADOPORCOMISION_H

#include "EmpleadoAsalariado.h"

class EmpleadoPorComision : public EmpleadoAsalariado
{
private:
    double montoVentas;
    double porcentajeComision;

public:
    EmpleadoPorComision(const std::string &nombre, const std::string &apellido, double salarioBase, int semanasAnuales, double montoVentas, double porcentajeComision);

    double CalcularSalario() override;
    std::string GetInfo() const override;

    // Getters y Setters
    double GetMontoVentas() const { return montoVentas; };
    double GetPorcentajeComision() const { return porcentajeComision; };
    void SetMontoVentas(double ventas) { this->montoVentas = montoVentas; };
    void SetPorcentajeComision(double porcen) { this->porcentajeComision = porcentajeComision; };
};

#endif