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
    bool datosModificados = false;

public:
    Empresa(const std::string &nombre, const std::string &direccion, const std::string &telefono);
    Empresa() = default;

    void AgregarEmpleado(const std::shared_ptr<Empleado> &empleado);
    void EliminarEmpleado(int indice);
    std::shared_ptr<Empleado> ObtenerEmpleado(int indice);
    int ObtenerNumeroEmpleados() const;
    int ContarEmpleadosPorTipo(TipoEmpleado tipo) const;
    double CalcularGastosTotales() const;
    long GenerarIDUnico();
    bool ExisteEmpleado(int id);

    // Persistencia de datos
    void GuardarDatosArchivo(const std::string &nombreArchivo);
    void CargarDatosArchivo(const std::string &filename);

    // Getters y Setters
    void SetNombre(std::string nombre) { this->nombre = nombre; }
    std::string GetNombre() const { return nombre; }
    void SetDireccion(std::string direccion) { this->direccion = direccion; }
    std::string GetDireccion() const { return direccion; }
    void SetTelefono(std::string telefono) { this->telefono = telefono; }
    std::string GetTelefono() const { return telefono; }
    bool HayCambios() const { return datosModificados; }
    void ResetCambios() { datosModificados = false; }
    std::string ToString() const { return nombre + "\n" + direccion + "\n" + telefono; }
};

#endif