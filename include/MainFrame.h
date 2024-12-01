#include <wx/wx.h>
#include <memory>
#include <vector>
#include <wx/listctrl.h>
#include "Empresa.h"
#include "Empleado.h"

class MainFrame : public wxFrame
{
private:
    Empresa *empresa; // Empresa

    wxListCtrl *listaEmpleados;   // Lista visual de empleados
    wxChoice *tipoEmpleadoChoice; // Selector de tipo de empleado
    wxPanel *formularioPanel;     // Panel para el formulario

    // Campos dinámicos del formulario
    wxTextCtrl *nombreCtrl, *apellidoCtrl, *numEmpCtrl, *salarioBaseCtrl;
    wxTextCtrl *semanasCtrl, *ventasCtrl, *porcentajeCtrl, *horasCtrl, *tarifaCtrl;

    // Controles de texto para la información de empleados
    wxStaticText *totalEmpleadosText;
    wxStaticText *empleadosPorHorasText;
    wxStaticText *empleadosAsalariadosText;
    wxStaticText *empleadosPorComisionText;
    wxStaticText *ingresosTotalesText;

    // Campo de búsqueda
    wxTextCtrl *searchCtrl;

    void OnAgregar(wxCommandEvent &event);
    void OnEditar(wxCommandEvent &event);
    void OnEliminar(wxCommandEvent &event);
    void OnVerDetalles(wxCommandEvent &event);
    void OnBuscar(wxCommandEvent &event);
    void ActualizarLista();
    void CambiarFormulario(wxCommandEvent &event);

public:
    MainFrame(const wxString &title);
    ~MainFrame();
};