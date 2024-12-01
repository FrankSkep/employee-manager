#ifndef EMPLEADOASALARIADO_H
#define EMPLEADOASALARIADO_H

#include "Empleado.h"

class EmpleadoAsalariado : public Empleado
{
private:
    int semanasAnuales;

public:
    EmpleadoAsalariado(string nom, string ap, int numEmp, double salBase, int semAn);

    double calcularSalario() override;
    std::string getInfo() const override;

    void setSemanas(int sem);
    int getSemanas();
};

#endif