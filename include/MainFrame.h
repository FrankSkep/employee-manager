#include <wx/wx.h>
#include <memory>
#include <vector>
#include <wx/listctrl.h>
#include "Empresa.h"
#include "Empleado.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:
    void CrearMenu();
    void CrearLayoutPrincipal();
    void CrearPanelIzquierdo();
    void CrearPanelDerecho();
    void CrearPanelInferior();
    void InicializarFormulario();

    void OnAgregar(wxCommandEvent &event);
    void OnEditar(wxCommandEvent &event);
    void OnEliminar(wxCommandEvent &event);
    void OnVerDetalles(wxCommandEvent &event);
    void OnBuscar(wxCommandEvent &event);
    void OnGuardarEmpresa(wxCommandEvent &event);
    void OnLimpiarFormulario(wxCommandEvent &event);
    void CambiarFormulario(wxCommandEvent &event);
    void RellenarFormulario(long itemIndex);
    void ActualizarInformacion();

    friend void LimpiarFormulario(MainFrame &frame);

    std::unique_ptr<Empresa> empresa;
    wxBoxSizer *mainSizer;
    wxBoxSizer *formSizer;
    wxTextCtrl *searchCtrl;
    wxListCtrl *listaEmpleados;
    wxStaticText *empresaNombreText;
    wxStaticText *empresaDireccionText;
    wxStaticText *empresaTelefonoText;
    wxStaticText *totalEmpleadosText;
    wxStaticText *empleadosPorHorasText;
    wxStaticText *empleadosAsalariadosText;
    wxStaticText *empleadosPorComisionText;
    wxStaticText *gastosTotales;
    wxTextCtrl *empresaNombreCtrl;
    wxTextCtrl *empresaDireccionCtrl;
    wxTextCtrl *empresaTelefonoCtrl;
    wxChoice *tipoEmpleadoChoice;
    wxScrolledWindow *formularioPanel;
    wxTextCtrl *nombreCtrl;
    wxTextCtrl *apellidoCtrl;
    wxTextCtrl *salarioBaseCtrl;
    wxTextCtrl *horasCtrl;
    wxTextCtrl *tarifaCtrl;
    wxTextCtrl *semanasCtrl;
    wxTextCtrl *ventasCtrl;
    wxTextCtrl *porcentajeCtrl;
};