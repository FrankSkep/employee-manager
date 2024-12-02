#include "../include/Empresa.h"

Empresa::Empresa(const std::string &nombre, const std::string &direccion, const std::string &telefono)
{
    this->nombre = nombre;
    this->direccion = direccion;
    this->telefono = telefono;
}

void Empresa::AgregarEmpleado(const std::shared_ptr<Empleado> &empleado)
{
    empleados.push_back(empleado);
}

void Empresa::EliminarEmpleado(int indice)
{
    empleados.erase(empleados.begin() + indice);
}

long Empresa::GenerarIDUnico()
{
    long id = rand() % 1000;
    while (ExisteEmpleado(id))
    {
        id = rand() % 1000;
    }
    return id;
}

bool Empresa::ExisteEmpleado(int id)
{
    for (const auto &empleado : empleados)
    {
        if (empleado->GetNumeroEmpleado() == id)
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Empleado> Empresa::ObtenerEmpleado(int indice)
{
    if (indice < 0 || indice >= static_cast<int>(empleados.size()))
    {
        return nullptr;
    }
    return empleados[indice];
}

int Empresa::ContarEmpleadosPorTipo(TipoEmpleado tipo) const
{
    int total = 0;
    for (const auto &empleado : empleados)
    {
        if (empleado->GetTipoEmpleado() == tipo)
        {
            total++;
        }
    }
    return total;
}

double Empresa::CalcularGastosTotales() const
{
    double total = 0.0;
    for (const auto &empleado : empleados)
    {
        total += empleado->CalcularSalario();
    }
    return total;
}