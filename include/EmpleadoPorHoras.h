#ifndef EMPLEADOPORHORAS_H
#define EMPLEADOPORHORAS_H

#include "Empleado.h"

class EmpleadoPorHoras : public Empleado
{
private:
    int horasTrabajadas;
    float tarifaHora;

public:
    EmpleadoPorHoras(const std::string &nombre, const std::string &apellido, int numeroEmpleado, double salarioBase, int horasTrabajadas, float tarifaHora);

    double calcularSalario() override;
    std::string getInfo() const override;

    // Getters y Setters
    int getHorasTrabajadas() const { return horasTrabajadas; };
    float getTarifaHora() const { return tarifaHora; };
    void setHorasTrabajadas(int horasTrabajadas) { this->horasTrabajadas = horasTrabajadas; };
    void setTarifaHora(float tarifaHora) { this->tarifaHora = tarifaHora; };
};

#endif