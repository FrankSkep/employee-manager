#ifndef EMPLEADOPORHORAS_H
#define EMPLEADOPORHORAS_H

#include "Empleado.h"

class EmpleadoPorHoras : public Empleado
{
private:
    int horasTrabajadas;
    float tarifaHora;

public:
    EmpleadoPorHoras(string nom, string ap, int numEmp, double salBase, int horasT, float tarifa);

    double calcularSalario() override;
    std::string getInfo() const override;

    void setHoras(int horasT);
    void setTarifa(float tarifaH);
    int getHorasTrabajadas() const { return horasTrabajadas; };
    float getTarifaHora() const { return tarifaHora; };
};

#endif