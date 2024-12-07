#include "../include/Empresa.h"
#include <fstream>
#include <sstream>
#include "../include/EmpleadoPorHoras.h"
#include "../include/EmpleadoAsalariado.h"
#include "../include/EmpleadoPorComision.h"

Empresa::Empresa(const std::string &nombre, const std::string &direccion, const std::string &telefono)
{
    this->nombre = nombre;
    this->direccion = direccion;
    this->telefono = telefono;
}

// Agregar un empleado a la lista
void Empresa::AgregarEmpleado(const std::shared_ptr<Empleado> &empleado)
{
    empleado->SetNumeroEmpleado(GenerarIDUnico());
    empleados.push_back(empleado);
}

// Eliminar un empleado por su índice
void Empresa::EliminarEmpleado(int indice)
{
    empleados.erase(empleados.begin() + indice);
}

// Obtener un empleado por su índice
std::shared_ptr<Empleado> Empresa::ObtenerEmpleado(int indice)
{
    if (indice < 0 || indice >= static_cast<int>(empleados.size()))
    {
        return nullptr;
    }
    return empleados[indice];
}

// Obtener numero total de empleados
int Empresa::ObtenerNumeroEmpleados() const { return empleados.size(); }

// Contar empleados por tipo
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

// Calcular la suma de los salarios de todos los empleados
double Empresa::CalcularGastosTotales() const
{
    double total = 0.0;
    for (const auto &empleado : empleados)
    {
        total += empleado->CalcularSalario();
    }
    return total;
}

// Generar un ID único para cada empleado
long Empresa::GenerarIDUnico()
{
    long id = rand() % 1000;
    while (ExisteEmpleado(id))
    {
        id = rand() % 1000;
    }
    return id;
}

// Verificar si un empleado ya existe por su ID
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

// Guardar datos en un archivo de texto
void Empresa::GuardarDatosArchivo(const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo para guardar datos." << std::endl;
        return;
    }

    for (const auto &empleado : empleados)
    {
        file << empleado->GetTipoEmpleadoString() << ","
             << empleado->GetNombre() << ","
             << empleado->GetApellido() << ","
             << empleado->GetSalarioBase();

        if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_HORAS)
        {
            auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
            file << "," << porHoras->GetHorasTrabajadas() << "," << porHoras->GetTarifaHora();
        }
        else if (empleado->GetTipoEmpleado() == TipoEmpleado::ASALARIADO)
        {
            auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
            file << "," << asalariado->GetSemanasAnuales();
        }
        else if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_COMISION)
        {
            auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
            file << "," << porComision->GetSemanasAnuales() << "," << porComision->GetMontoVentas() << "," << porComision->GetPorcentajeComision();
        }

        file << std::endl;
    }

    file.close();
}

// Cargar datos desde un archivo de texto
void Empresa::CargarDatosArchivo(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo para cargar datos." << std::endl;
        return;
    }

    empleados.clear();
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string tipo, nombre, apellido;
        double salarioBase;

        std::getline(iss, tipo, ',');
        std::getline(iss, nombre, ',');
        std::getline(iss, apellido, ',');
        iss >> salarioBase;
        iss.ignore(1, ',');

        if (tipo == "Por Horas")
        {
            int horasTrabajadas;
            float tarifaHora;
            iss >> horasTrabajadas;
            iss.ignore(1, ',');
            iss >> tarifaHora;
            empleados.push_back(std::make_shared<EmpleadoPorHoras>(nombre, apellido, salarioBase, horasTrabajadas, tarifaHora));
        }
        else if (tipo == "Asalariado")
        {
            int semanasAnuales;
            iss >> semanasAnuales;
            empleados.push_back(std::make_shared<EmpleadoAsalariado>(nombre, apellido, salarioBase, semanasAnuales));
        }
        else if (tipo == "Por Comision")
        {
            int semanasAnuales;
            double montoVentas, porcentajeComision;
            iss >> semanasAnuales;
            iss.ignore(1, ',');
            iss >> montoVentas;
            iss.ignore(1, ',');
            iss >> porcentajeComision;
            empleados.push_back(std::make_shared<EmpleadoPorComision>(nombre, apellido, salarioBase, semanasAnuales, montoVentas, porcentajeComision));
        }
    }

    file.close();
    std::cout << "Datos cargados correctamente desde el archivo." << std::endl;
}