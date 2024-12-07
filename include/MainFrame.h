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
    void AgregarDatosFicticios();

private:
    //Destructor
    ~MainFrame();

    // Metodos para crear la interfaz de usuario
    void CrearMenu();
    void CrearLayoutPrincipal();
    void CrearPanelIzquierdo();
    void CrearPanelDerecho();
    void CrearPanelInferior();
    void InicializarFormulario();

    // Metodos para manejar eventos
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

    void OnGuardar(wxCommandEvent &event);
    void OnCargar(wxCommandEvent &event);

    // Metodo friend para limpiar el formulario
    friend void LimpiarFormulario(MainFrame &frame);

    // Empresa
    std::unique_ptr<Empresa> empresa;

    // Elementos de la interfaz
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