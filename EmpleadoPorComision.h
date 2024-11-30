#ifndef EMPLEADOPORCOMISION_H
#define EMPLEADOPORCOMISION_H

#include "EmpleadoAsalariado.h"

class EmpleadoPorComision : public EmpleadoAsalariado
{
private:
    double montoTotalVentas;
    double porcentajeComision;

public:
    EmpleadoPorComision(string nom, string ap, int numEmp, double salBase, int semAn, double ventas, double porcen);

    double calcularSalario() override;
    std::string getInfo() const override;

    void setVentas(double ventas);
    void setPorcenComision(double porcen);

    double getVentas();
    double getPorcenComision();
};

#endif