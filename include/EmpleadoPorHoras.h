#ifndef EMPLEADOPORHORAS_H
#define EMPLEADOPORHORAS_H

#include "Empleado.h"

class EmpleadoPorHoras : public Empleado
{
private:
    int horasTrabajadas;
    float tarifaHora;

public:
    EmpleadoPorHoras(const std::string &nombre, const std::string &apellido, double salarioBase, int horasTrabajadas, float tarifaHora);

    double CalcularSalario() override;
    std::string GetInfo() const override;

    // Getters y Setters
    int GetHorasTrabajadas() const { return horasTrabajadas; };
    float GetTarifaHora() const { return tarifaHora; };
    void SetHorasTrabajadas(int horasTrabajadas) { this->horasTrabajadas = horasTrabajadas; };
    void SetTarifaHora(float tarifaHora) { this->tarifaHora = tarifaHora; };
};

#endif