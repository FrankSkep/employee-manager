#include <string>
#include <vector>
#include <memory>
#include "Empleado.h"

class Empresa
{
public:
    std::string nombre;
    std::string direccion;
    std::string telefono;
    std::vector<std::shared_ptr<Empleado>> empleados;

    Empresa();
    Empresa(std::string nombre, std::string direccion, std::string telefono);

    void agregarEmpleado(Empleado *empleado);
    void eliminarEmpleado();
    void modificarEmpleado();
    long generarIDUnico();

    void setNombre(std::string nombre) { this->nombre = nombre; }
    std::string getNombre() const { return nombre; }
    void setDireccion(std::string direccion) { this->direccion = direccion; }
    std::string getDireccion() const { return direccion; }
    void setTelefono(std::string telefono) { this->telefono = telefono; }
    std::string getTelefono() const { return telefono; }
    std::string ToString() const { return nombre + "\n" + direccion + "\n" + telefono; }
};