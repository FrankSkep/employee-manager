#ifndef EMPRESA_H
#define EMPRESA_H

#include <string>
#include <vector>
#include <memory>
#include "Empleado.h"

class Empresa
{
private:
    std::string nombre;
    std::string direccion;
    std::string telefono;
    std::vector<std::shared_ptr<Empleado>> empleados;

public:
    Empresa(const std::string &nombre, const std::string &direccion, const std::string &telefono);

    void AgregarEmpleado(const std::shared_ptr<Empleado> &empleado);
    void EliminarEmpleado(int indice);
    long GenerarIDUnico();
    bool ExisteEmpleado(int id);
    std::shared_ptr<Empleado> ObtenerEmpleado(int indice);
    int ObtenerTotalEmpleados() const { return empleados.size(); }

    void setNombre(std::string nombre) { this->nombre = nombre; }
    std::string getNombre() const { return nombre; }
    void setDireccion(std::string direccion) { this->direccion = direccion; }
    std::string getDireccion() const { return direccion; }
    void setTelefono(std::string telefono) { this->telefono = telefono; }
    std::string getTelefono() const { return telefono; }
    std::string ToString() const { return nombre + "\n" + direccion + "\n" + telefono; }
};

#endif