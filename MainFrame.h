#include <wx/wx.h>
#include <memory>
#include <vector>
#include <wx/listctrl.h>
#include "Empleado.h"

class MainFrame : public wxFrame
{
private:
    wxListCtrl *listaEmpleados; // Lista principal
    wxChoice *tipoEmpleadoChoice;
    wxPanel *formularioPanel;
    std::vector<std::shared_ptr<Empleado>> empleados;

    // Campos dinámicos
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
    bool ExisteID(int id);
    void ActualizarLista();
    void CambiarFormulario(wxCommandEvent &event);
    void AgregarDatosAleatorios();

public:
    MainFrame(const wxString &title);
};