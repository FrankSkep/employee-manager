#ifndef EMPLEADOPORCOMISION_H
#define EMPLEADOPORCOMISION_H

#include "EmpleadoAsalariado.h"

class EmpleadoPorComision : public EmpleadoAsalariado
{
private:
    double montoVentas;
    double porcentajeComision;

public:
    EmpleadoPorComision(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int semanasAnuales, double montoVentas, double porcentajeComision);

    double calcularSalario() override;
    std::string getInfo() const override;

    // Getters y Setters
    double getMontoVentas() const { return montoVentas; };
    double getPorcentajeComision() const { return porcentajeComision; };
    void setMontoVentas(double ventas) { this->montoVentas = montoVentas; };
    void setPorcentajeComision(double porcen) { this->porcentajeComision = porcentajeComision; };
};

#endif