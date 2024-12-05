#include <wx/wx.h>
#include <memory>
#include <vector>
#include <wx/listctrl.h>
#include "Empresa.h"
#include "Empleado.h"

class MainFrame : public wxFrame
{
private:
    std::unique_ptr<Empresa> empresa; // Empresa

    wxListCtrl *listaEmpleados;   // Lista visual de empleados
    wxChoice *tipoEmpleadoChoice; // Selector de tipo de empleado
    wxPanel *formularioPanel;     // Panel para el formulario
    wxBoxSizer *formSizer; // Sizer para el formulario

    // Campos en común para todos los tipos de empleados
    wxTextCtrl *nombreCtrl, *apellidoCtrl, *salarioBaseCtrl;

    // Campos específicos para cada tipo de empleado
    wxTextCtrl *semanasCtrl, *ventasCtrl, *porcentajeCtrl, *horasCtrl, *tarifaCtrl;

    // Controles de texto para la información de la empresa
    wxStaticText *empresaNombreText, *empresaDireccionText, *empresaTelefonoText;
    wxTextCtrl *empresaNombreCtrl, *empresaDireccionCtrl, *empresaTelefonoCtrl;
    wxStaticText *totalEmpleadosText, *empleadosPorHorasText, *empleadosAsalariadosText, *empleadosPorComisionText, *gastosTotales;

    // Campo de búsqueda
    wxTextCtrl *searchCtrl;

    void OnAgregar(wxCommandEvent &event);
    void OnEditar(wxCommandEvent &event);
    void OnEliminar(wxCommandEvent &event);
    void OnVerDetalles(wxCommandEvent &event);
    void OnBuscar(wxCommandEvent &event);
    void OnGuardarEmpresa(wxCommandEvent &event);
    void RellenarFormulario(long itemIndex);
    void OnLimpiarFormulario(wxCommandEvent &event);
    friend void LimpiarFormulario(MainFrame &frame);
    void ActualizarInformacion();
    void CambiarFormulario(wxCommandEvent &event);

public:
    MainFrame(const wxString &title);
};