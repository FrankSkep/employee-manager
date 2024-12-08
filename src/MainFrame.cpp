#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/scrolwin.h>
#include <wx/artprov.h>
#include <memory>
#include <vector>
#include <fstream>
#include "../include/MainFrame.h"
#include "../include/EmpleadoAsalariado.h"
#include "../include/EmpleadoPorComision.h"
#include "../include/EmpleadoPorHoras.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)),
                                              nombreCtrl(nullptr), apellidoCtrl(nullptr), edadCtrl(nullptr), salarioBaseCtrl(nullptr),
                                              horasCtrl(nullptr), tarifaCtrl(nullptr), semanasCtrl(nullptr), ventasCtrl(nullptr), porcentajeCtrl(nullptr)
{
    empresa = std::make_unique<Empresa>("Empresa que no existe", "Calle Falsa 123", "123-456-7890");

    // Creacion de la interfaz de usuario
    CrearMenu();
    CrearLayoutPrincipal();
    CrearPanelIzquierdo();
    CrearPanelCentral();
    CrearPanelDerecho();

    // Cargar datos desde archivo
    CargarArchivo("data/empresa.txt");

    Centre();
    SetBackgroundColour(*wxWHITE);
    InicializarFormulario();
}

// Crear el menu de la aplicacion
void MainFrame::CrearMenu()
{
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_OPEN, "&Importar\tCtrl-O", "Importar datos desde archivo");
    fileMenu->Append(wxID_SAVE, "&Exportar\tCtrl-S", "Exportar datos a archivo");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Salir de la aplicación");

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&Acerca de\tF1", "Mostrar información de la aplicación");

    menuBar->Append(fileMenu, "&Archivo");
    menuBar->Append(helpMenu, "&Ayuda");
    SetMenuBar(menuBar);
}

// Crear el layout principal
void MainFrame::CrearLayoutPrincipal()
{
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(mainSizer);
}

// Crear el panel central
void MainFrame::CrearPanelCentral()
{
    wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *titleText = new wxStaticText(this, wxID_ANY, " GESTION DE EMPLEADOS ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    AjustarFuente(titleText, 16);
    titleText->SetFont(titleText->GetFont().Bold());
    titleText->SetForegroundColour(*wxBLACK);
    titleText->SetBackgroundColour(*wxWHITE);
    leftSizer->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    wxPanel *searchPanel = new wxPanel(this, wxID_ANY);
    searchPanel->SetBackgroundColour(*wxWHITE);
    wxBoxSizer *searchSizer = new wxBoxSizer(wxVERTICAL);
    searchCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "", wxDefaultPosition, wxSize(500, -1), wxTE_PROCESS_ENTER);
    searchCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnBuscar, this);
    wxStaticText *searchLabel = new wxStaticText(searchPanel, wxID_ANY, "Buscar Empleado (Nombre o Apellido)", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(searchLabel, 12);
    searchLabel->SetFont(searchLabel->GetFont().Bold());
    searchSizer->Add(searchLabel, 0, wxALL, 5);
    searchSizer->Add(searchCtrl, 0, wxEXPAND | wxALL, 5);
    searchPanel->SetSizer(searchSizer);
    leftSizer->Add(searchPanel, 0, wxEXPAND | wxALL, 5);

    listaEmpleados = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(500, 350), wxLC_REPORT | wxLC_SINGLE_SEL);

    // Ajuste la fuente de los encabezados de las columnas
    wxFont headerFont = listaEmpleados->GetFont();
    headerFont.SetPointSize(12);
    listaEmpleados->SetFont(headerFont);

    // Ajuste la fuente de los elementos de la lista
    listaEmpleados->SetWindowStyleFlag(wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_HRULES | wxLC_VRULES);

    listaEmpleados->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
    listaEmpleados->InsertColumn(1, "Nombre", wxLIST_FORMAT_LEFT, 200);
    listaEmpleados->InsertColumn(2, "Apellido", wxLIST_FORMAT_LEFT, 200);
    listaEmpleados->InsertColumn(3, "Edad", wxLIST_FORMAT_LEFT, 50);
    listaEmpleados->InsertColumn(4, "Tipo", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(5, "Salario", wxLIST_FORMAT_LEFT, 100);
    listaEmpleados->SetSize(wxSize(500, 350));

    // Agregar eventos para seleccionar un elemento de la lista
    listaEmpleados->Bind(wxEVT_LIST_ITEM_SELECTED, [&](wxListEvent &event)
                         {
        long itemIndex = event.GetIndex();
        RellenarFormulario(itemIndex); });

    leftSizer->Add(listaEmpleados, 2, wxEXPAND | wxALL, 10);
    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 10);
}

// Crea el panel de informacion
void MainFrame::CrearPanelIzquierdo()
{
    wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *infoPanel = new wxPanel(this, wxID_ANY);
    infoPanel->SetBackgroundColour(wxColour(64, 64, 64));
    wxBoxSizer *infoSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *infoTitle = new wxStaticText(infoPanel, wxID_ANY, "Informacion de la Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    AjustarFuente(infoTitle, 14);
    infoTitle->SetFont(infoTitle->GetFont().Bold());
    infoTitle->SetForegroundColour(*wxWHITE);
    infoSizer->Add(infoTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    empresaNombreText = new wxStaticText(infoPanel, wxID_ANY, "Nombre: " + empresa->GetNombre(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaNombreText, 12);
    empresaNombreText->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaNombreText, 0, wxALL, 10);
    empresaDireccionText = new wxStaticText(infoPanel, wxID_ANY, "Direccion: " + empresa->GetDireccion(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaDireccionText, 12);
    empresaDireccionText->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaDireccionText, 0, wxALL, 10);
    empresaTelefonoText = new wxStaticText(infoPanel, wxID_ANY, "Telefono: " + empresa->GetTelefono(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaTelefonoText, 12);
    empresaTelefonoText->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaTelefonoText, 0, wxALL, 10);
    totalEmpleadosText = new wxStaticText(infoPanel, wxID_ANY, "Total de Empleados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    totalEmpleadosText->SetForegroundColour(*wxWHITE);
    AjustarFuente(totalEmpleadosText, 12);
    infoSizer->Add(totalEmpleadosText, 0, wxALL, 10);
    empleadosPorHorasText = new wxStaticText(infoPanel, wxID_ANY, "Empleados por Horas: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    empleadosPorHorasText->SetForegroundColour(*wxWHITE);
    AjustarFuente(empleadosPorHorasText, 12);
    infoSizer->Add(empleadosPorHorasText, 0, wxALL, 10);
    empleadosAsalariadosText = new wxStaticText(infoPanel, wxID_ANY, "Empleados Asalariados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    empleadosAsalariadosText->SetForegroundColour(*wxWHITE);
    AjustarFuente(empleadosAsalariadosText, 12);
    infoSizer->Add(empleadosAsalariadosText, 0, wxALL, 10);
    empleadosPorComisionText = new wxStaticText(infoPanel, wxID_ANY, "Empleados por Comision: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    empleadosPorComisionText->SetForegroundColour(*wxWHITE);
    AjustarFuente(empleadosPorComisionText, 12);
    infoSizer->Add(empleadosPorComisionText, 0, wxALL, 10);
    gastosTotales = new wxStaticText(infoPanel, wxID_ANY, "Gastos totales: $0.00", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(gastosTotales, 12);
    gastosTotales->SetForegroundColour(*wxWHITE);
    infoSizer->Add(gastosTotales, 0, wxALL, 10);
    infoSizer->AddSpacer(30);

    wxStaticText *editEmpresaTitle = new wxStaticText(infoPanel, wxID_ANY, "Editar informacion Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    AjustarFuente(editEmpresaTitle, 14);
    editEmpresaTitle->SetFont(editEmpresaTitle->GetFont().Bold());
    editEmpresaTitle->SetForegroundColour(*wxWHITE);
    infoSizer->Add(editEmpresaTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    empresaNombreCtrl = new wxTextCtrl(infoPanel, wxID_ANY, empresa->GetNombre(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    AjustarFuente(empresaNombreCtrl, 12);
    empresaDireccionCtrl = new wxTextCtrl(infoPanel, wxID_ANY, empresa->GetDireccion(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    AjustarFuente(empresaDireccionCtrl, 12);
    empresaTelefonoCtrl = new wxTextCtrl(infoPanel, wxID_ANY, empresa->GetTelefono(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    AjustarFuente(empresaTelefonoCtrl, 12);
    wxStaticText *empresaLabel = new wxStaticText(infoPanel, wxID_ANY, "Nombre de la Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaLabel, 12);
    empresaLabel->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaLabel, 0, wxALL, 5);
    infoSizer->Add(empresaNombreCtrl, 0, wxEXPAND | wxALL, 5);
    wxStaticText *empresaDireccionLabel = new wxStaticText(infoPanel, wxID_ANY, "Direccion de la Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaDireccionLabel, 12);
    empresaDireccionLabel->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaDireccionLabel, 0, wxALL, 5);
    infoSizer->Add(empresaDireccionCtrl, 0, wxEXPAND | wxALL, 5);
    wxStaticText *empresaTelefonoLabel = new wxStaticText(infoPanel, wxID_ANY, "Telefono de la Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    AjustarFuente(empresaTelefonoLabel, 12);
    empresaTelefonoLabel->SetForegroundColour(*wxWHITE);
    infoSizer->Add(empresaTelefonoLabel, 0, wxEXPAND | wxALL, 5);
    infoSizer->Add(empresaTelefonoCtrl, 0, wxEXPAND | wxALL, 5);

    wxButton *guardarEmpresaButton = new wxButton(infoPanel, wxID_ANY, "Guardar Cambios");
    AjustarFuente(guardarEmpresaButton, 12);
    guardarEmpresaButton->SetBackgroundColour(*wxGREEN);
    infoSizer->Add(guardarEmpresaButton, 0, wxALIGN_CENTER | wxALL, 10);
    guardarEmpresaButton->Bind(wxEVT_BUTTON, &MainFrame::OnGuardarEmpresa, this);

    infoPanel->SetSizer(infoSizer);
    rightSizer->Add(infoPanel, 0, wxEXPAND | wxALL, 10);

    mainSizer->Add(rightSizer, 0, wxEXPAND | wxALL, 10);
}

// Crea el panel de registro de empleados
void MainFrame::CrearPanelDerecho()
{
    wxBoxSizer *lowerSizer = new wxBoxSizer(wxHORIZONTAL);
    formSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *formTitle = new wxStaticText(this, wxID_ANY, " REGISTRAR EMPLEADO ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont formFont = formTitle->GetFont();
    formFont.SetPointSize(16);
    formFont.SetWeight(wxFONTWEIGHT_BOLD);
    formTitle->SetFont(formFont);
    formTitle->SetForegroundColour(*wxBLACK);
    formTitle->SetBackgroundColour(*wxWHITE);
    formSizer->Add(formTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    tipoEmpleadoChoice = new wxChoice(this, wxID_ANY);
    tipoEmpleadoChoice->Append("Por Horas");
    tipoEmpleadoChoice->Append("Asalariado");
    tipoEmpleadoChoice->Append("Por Comision");
    tipoEmpleadoChoice->Bind(wxEVT_CHOICE, &MainFrame::CambiarFormulario, this);

    formSizer->Add(new wxStaticText(this, wxID_ANY, "Tipo de Empleado"), 0, wxALL, 5);
    formSizer->Add(tipoEmpleadoChoice, 0, wxEXPAND | wxALL, 5);

    formularioPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300), wxVSCROLL);
    formSizer->Add(formularioPanel, 1, wxEXPAND | wxALL, 5);

    lowerSizer->Add(formSizer, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonSizer2 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *addButton = new wxButton(this, wxID_ANY, "Agregar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *updateButton = new wxButton(this, wxID_ANY, "Actualizar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *deleteButton = new wxButton(this, wxID_ANY, "Eliminar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *viewDetailsButton = new wxButton(this, wxID_ANY, "Detalles", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *clearButton = new wxButton(this, wxID_ANY, "Limpiar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

    addButton->SetMinSize(wxSize(-1, 35));
    wxFont fontAddBtn = addButton->GetFont();
    fontAddBtn.SetPointSize(12);
    addButton->SetFont(fontAddBtn);
    addButton->SetBackgroundColour(*wxGREEN);
    addButton->SetForegroundColour(*wxBLACK);

    updateButton->SetMinSize(wxSize(-1, 35));
    wxFont fontEditBtn = updateButton->GetFont();
    fontEditBtn.SetPointSize(12);
    updateButton->SetFont(fontEditBtn);
    updateButton->SetBackgroundColour(*wxBLUE);
    updateButton->SetForegroundColour(*wxWHITE);

    deleteButton->SetMinSize(wxSize(-1, 35));
    wxFont fontDeleteBtn = deleteButton->GetFont();
    fontDeleteBtn.SetPointSize(12);
    deleteButton->SetFont(fontDeleteBtn);
    deleteButton->SetBackgroundColour(*wxRED);
    deleteButton->SetForegroundColour(*wxWHITE);

    viewDetailsButton->SetMinSize(wxSize(-1, 35));
    wxFont fontViewBtn = viewDetailsButton->GetFont();
    fontViewBtn.SetPointSize(12);
    viewDetailsButton->SetFont(fontViewBtn);
    viewDetailsButton->SetBackgroundColour(*wxCYAN);
    viewDetailsButton->SetForegroundColour(*wxBLACK);

    clearButton->SetMinSize(wxSize(-1, 35));
    wxFont fontClearBtn = clearButton->GetFont();
    fontClearBtn.SetPointSize(12);
    clearButton->SetFont(fontClearBtn);
    clearButton->SetBackgroundColour(*wxYELLOW);
    clearButton->SetForegroundColour(*wxBLACK);

    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAgregar, this);
    updateButton->Bind(wxEVT_BUTTON, &MainFrame::OnEditar, this);
    deleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnEliminar, this);
    viewDetailsButton->Bind(wxEVT_BUTTON, &MainFrame::OnVerDetalles, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnLimpiarFormulario, this);

    buttonSizer->Add(addButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(updateButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(deleteButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer2->Add(viewDetailsButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer2->Add(clearButton, 0, wxEXPAND | wxALL, 5);

    formSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    formSizer->Add(buttonSizer2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    mainSizer->Add(lowerSizer, 0, wxEXPAND | wxALL, 10);
}

void MainFrame::InicializarFormulario()
{
    wxCommandEvent dummyEvent;
    CambiarFormulario(dummyEvent);
    searchCtrl->SetFocus();
}

/********  Metodos manejadores de eventos del menu  ********/
void MainFrame::OnNuevo(wxCommandEvent &event)
{
    // Lógica para crear un nuevo archivo
    wxMessageBox("Nuevo archivo creado.", "Información", wxICON_INFORMATION);
}

void MainFrame::OnImportar(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, _("Abrir archivo"), "", "",
                                "Archivos de texto (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    // Lógica para importar datos desde archivo
    CargarArchivo(openFileDialog.GetPath().ToStdString());
}

void MainFrame::OnExportar(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, _("Guardar archivo"), "", "",
                                "Archivos de texto (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    std::ofstream outFile(saveFileDialog.GetPath().ToStdString());
    if (!outFile)
    {
        wxMessageBox("No se pudo abrir el archivo para guardar.", "Error", wxICON_ERROR);
        return;
    }
    std::cout << "Guardando datos en " << saveFileDialog.GetPath().ToStdString() << std::endl;
    empresa->GuardarDatosArchivo(saveFileDialog.GetPath().ToStdString());
}

void MainFrame::OnSalir(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAcercaDe(wxCommandEvent &event)
{
    wxMessageBox("Aplicación de Gestión de Empleados", "Acerca de", wxOK | wxICON_INFORMATION);
}

/********  Metodos manejadores de eventos CRUD  ********/
// Agregar un empleado
void MainFrame::OnAgregar(wxCommandEvent &event)
{
    std::string nombre = nombreCtrl->GetValue().ToStdString();
    std::string apellido = apellidoCtrl->GetValue().ToStdString();
    long edad;
    double salarioBase;

    if (nombre.empty() || apellido.empty())
    {
        wxMessageBox("El nombre y apellido no pueden estar vacíos.", "Error", wxICON_ERROR);
        return;
    }

    if (!edadCtrl->GetValue().ToLong(&edad) || edad < 15 || edad > 90)
    {
        wxMessageBox("Por favor, ingresa una edad válida.", "Error", wxICON_ERROR);
        return;
    }

    if (!salarioBaseCtrl->GetValue().ToDouble(&salarioBase) || salarioBase < 0)
    {
        wxMessageBox("Por favor, ingresa un salario base válido.", "Error", wxICON_ERROR);
        return;
    }

    int tipoSeleccionado = tipoEmpleadoChoice->GetSelection();

    if (tipoSeleccionado == 0) // Por Horas
    {
        if (horasCtrl->GetValue().IsEmpty() || tarifaCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        long horasTrabajadas;
        double tarifaHora;

        if (!horasCtrl->GetValue().ToLong(&horasTrabajadas) || horasTrabajadas < 0)
        {
            wxMessageBox("Por favor, ingresa un número de horas trabajadas válido.", "Error", wxICON_ERROR);
            return;
        }

        if (!tarifaCtrl->GetValue().ToDouble(&tarifaHora) || tarifaHora <= 0)
        {
            wxMessageBox("Por favor, ingresa una tarifa por hora válida.", "Error", wxICON_ERROR);
            return;
        }

        empresa->AgregarEmpleado(std::make_shared<EmpleadoPorHoras>(nombre, apellido, edad, salarioBase, horasTrabajadas, tarifaHora));
    }
    else if (tipoSeleccionado == 1) // Asalariado
    {
        if (semanasCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        long semanas;
        if (!semanasCtrl->GetValue().ToLong(&semanas) || semanas <= 0 || semanas > 52)
        {
            wxMessageBox("El número de semanas anuales debe estar entre 1 y 52.", "Error", wxICON_ERROR);
            return;
        }

        empresa->AgregarEmpleado(std::make_shared<EmpleadoAsalariado>(nombre, apellido, edad, salarioBase, semanas));
    }
    else if (tipoSeleccionado == 2) // Por Comisión
    {
        if (semanasCtrl->GetValue().IsEmpty() || ventasCtrl->GetValue().IsEmpty() || porcentajeCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        long semanas;
        double ventas, porcentaje;

        if (!semanasCtrl->GetValue().ToLong(&semanas) || semanas <= 0 || semanas > 52)
        {
            wxMessageBox("El número de semanas anuales debe estar entre 1 y 52.", "Error", wxICON_ERROR);
            return;
        }

        if (!ventasCtrl->GetValue().ToDouble(&ventas) || ventas < 0)
        {
            wxMessageBox("Por favor, ingresa un valor de ventas válido.", "Error", wxICON_ERROR);
            return;
        }

        if (!porcentajeCtrl->GetValue().ToDouble(&porcentaje) || porcentaje <= 0 || porcentaje > 100)
        {
            wxMessageBox("Por favor, ingresa un porcentaje de comisión válido.", "Error", wxICON_ERROR);
            return;
        }

        empresa->AgregarEmpleado(std::make_shared<EmpleadoPorComision>(nombre, apellido, edad, salarioBase, semanas, ventas, porcentaje));
    }

    RefrescarInformacion();
    wxMessageBox("Empleado agregado correctamente.", "Información", wxICON_INFORMATION);
    LimpiarFormulario(*this);
}

// Editar un empleado
void MainFrame::OnEditar(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, selecciona un empleado para editar.", "Error", wxICON_ERROR);
        return;
    }

    auto empleado = empresa->ObtenerEmpleado(itemIndex);

    std::string nombre = nombreCtrl->GetValue().ToStdString();
    std::string apellido = apellidoCtrl->GetValue().ToStdString();
    long edad;
    double salarioBase;

    if (nombre.empty() || apellido.empty())
    {
        wxMessageBox("El nombre y apellido no pueden estar vacíos.", "Error", wxICON_ERROR);
        return;
    }

    if (!edadCtrl->GetValue().ToLong(&edad) || edad < 15 || edad > 90)
    {
        wxMessageBox("Por favor, ingresa una edad válida.", "Error", wxICON_ERROR);
        return;
    }

    if (!salarioBaseCtrl->GetValue().ToDouble(&salarioBase) || salarioBase < 0)
    {
        wxMessageBox("Por favor, ingresa un salario base válido.", "Error", wxICON_ERROR);
        return;
    }

    empleado->SetNombre(nombre);
    empleado->SetApellido(apellido);
    empleado->SetEdad(edad);
    empleado->SetSalarioBase(salarioBase);

    if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_HORAS)
    {
        auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
        long horasTrabajadas;
        double tarifaHora;

        if (!horasCtrl->GetValue().ToLong(&horasTrabajadas) || horasTrabajadas < 0)
        {
            wxMessageBox("Por favor, ingresa un número de horas trabajadas válido.", "Error", wxICON_ERROR);
            return;
        }

        if (!tarifaCtrl->GetValue().ToDouble(&tarifaHora) || tarifaHora <= 0)
        {
            wxMessageBox("Por favor, ingresa una tarifa por hora válida.", "Error", wxICON_ERROR);
            return;
        }

        porHoras->SetHorasTrabajadas(horasTrabajadas);
        porHoras->SetTarifaHora(tarifaHora);
    }
    else if (empleado->GetTipoEmpleado() == TipoEmpleado::ASALARIADO)
    {
        auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
        long semanasAnuales;

        if (!semanasCtrl->GetValue().ToLong(&semanasAnuales) || semanasAnuales <= 0 || semanasAnuales > 52)
        {
            wxMessageBox("Por favor, ingresa un número de semanas anuales válido.", "Error", wxICON_ERROR);
            return;
        }

        asalariado->SetSemanasAnuales(semanasAnuales);
    }
    else if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_COMISION)
    {
        auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
        long semanasAnuales;
        double montoVentas, porcentajeComision;
        if (!semanasCtrl->GetValue().ToLong(&semanasAnuales) || semanasAnuales <= 0)
        {
            wxMessageBox("Por favor, ingresa un número de semanas anuales válido.", "Error", wxICON_ERROR);
            return;
        }

        if (!ventasCtrl->GetValue().ToDouble(&montoVentas) || montoVentas <= 0)
        {
            wxMessageBox("Por favor, ingresa un monto de ventas válido.", "Error", wxICON_ERROR);
            return;
        }

        if (!porcentajeCtrl->GetValue().ToDouble(&porcentajeComision) || porcentajeComision <= 0)
        {
            wxMessageBox("Por favor, ingresa un porcentaje de comisión válido.", "Error", wxICON_ERROR);
            return;
        }

        porComision->SetSemanasAnuales(semanasAnuales);
        porComision->SetMontoVentas(montoVentas);
        porComision->SetPorcentajeComision(porcentajeComision);
    }

    RefrescarInformacion();
    wxMessageBox("Empleado actualizado correctamente.", "Informacion", wxICON_INFORMATION);
    empresa->SetCambios(true);
}

// Eliminar un empleado
void MainFrame::OnEliminar(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex != wxNOT_FOUND)
    {
        int respuesta = wxMessageBox("¿Estas seguro de que deseas eliminar este empleado?", "Confirmacion", wxYES_NO | wxICON_QUESTION);
        if (respuesta == wxYES)
        {
            empresa->EliminarEmpleado(itemIndex);
            RefrescarInformacion();
            wxMessageBox("Empleado eliminado correctamente.", "Informacion", wxICON_INFORMATION);
        }
    }
    else
    {
        wxMessageBox("Por favor, selecciona un empleado para eliminar.", "Error", wxICON_ERROR);
    }
    empresa->SetCambios(true);
}

// Ver detalles de un empleado
void MainFrame::OnVerDetalles(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, selecciona un empleado para ver los detalles.", "Error", wxICON_ERROR);
        return;
    }

    auto empleado = empresa->ObtenerEmpleado(itemIndex);
    wxString detalles = empleado->GetInfo();
    wxMessageBox(detalles, "Detalles del Empleado", wxICON_INFORMATION);
}

// Buscar empleado por nombre o apellido
void MainFrame::OnBuscar(wxCommandEvent &event)
{
    std::string query = searchCtrl->GetValue().Lower().ToStdString();
    listaEmpleados->DeleteAllItems();

    for (size_t i = 0; i < empresa->ObtenerNumeroEmpleados(); ++i)
    {
        auto emp = empresa->ObtenerEmpleado(i);
        std::string nombreLower = ToLower(emp->GetNombre());
        std::string apellidoLower = ToLower(emp->GetApellido());
        if (nombreLower.find(query) != std::string::npos || apellidoLower.find(query) != std::string::npos)
        {
            long index = listaEmpleados->InsertItem(i, wxString::Format("%d", emp->GetNumeroEmpleado()));
            listaEmpleados->SetItem(index, 1, emp->GetNombre());
            listaEmpleados->SetItem(index, 2, emp->GetApellido());
            listaEmpleados->SetItem(index, 3, wxString::Format("%d", emp->GetEdad()));
            listaEmpleados->SetItem(index, 4, emp->GetTipoEmpleadoString());
            listaEmpleados->SetItem(index, 5, wxString::Format("$%.2f", emp->CalcularSalario()));
        }
    }
}

// Editar y guardar la información de la empresa
void MainFrame::OnGuardarEmpresa(wxCommandEvent &event)
{
    empresa->SetNombre(empresaNombreCtrl->GetValue().ToStdString());
    empresa->SetDireccion(empresaDireccionCtrl->GetValue().ToStdString());
    empresa->SetTelefono(empresaTelefonoCtrl->GetValue().ToStdString());

    empresaNombreText->SetLabel("Nombre: " + empresa->GetNombre());
    empresaDireccionText->SetLabel("Direccion: " + empresa->GetDireccion());
    empresaTelefonoText->SetLabel("Telefono: " + empresa->GetTelefono());

    empresa->SetCambios(true);

    wxMessageBox("Informacion de la empresa actualizada correctamente.", "Informacion", wxICON_INFORMATION);
}

// Limpia el formulario
void MainFrame::OnLimpiarFormulario(wxCommandEvent &event)
{
    LimpiarFormulario(*this);
}

// Cargar en el formulario los datos del empleado seleccionado en la lista
void MainFrame::RellenarFormulario(long itemIndex)
{
    if (itemIndex == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, selecciona un empleado válido.", "Error", wxICON_ERROR);
        return;
    }

    std::shared_ptr<Empleado> empleado = empresa->ObtenerEmpleado(itemIndex);

    if (!empleado)
    {
        wxMessageBox("No se pudo obtener el empleado.", "Error", wxICON_ERROR);
        return;
    }

    TipoEmpleado tipoEmpleado = empleado->GetTipoEmpleado();

    if (tipoEmpleado == TipoEmpleado::POR_HORAS)
    {
        tipoEmpleadoChoice->SetSelection(0);
    }
    else if (tipoEmpleado == TipoEmpleado::ASALARIADO)
    {
        tipoEmpleadoChoice->SetSelection(1);
    }
    else if (tipoEmpleado == TipoEmpleado::POR_COMISION)
    {
        tipoEmpleadoChoice->SetSelection(2);
    }
    else
    {
        wxMessageBox("Tipo de empleado no válido.", "Error", wxICON_ERROR);
        return;
    }

    // Actualizar el formulario dinámico según el tipo de empleado seleccionado
    wxCommandEvent dummyEvent;
    CambiarFormulario(dummyEvent);

    // Rellenar formulario con los datos del empleado seleccionado
    nombreCtrl->SetValue(empleado->GetNombre());
    apellidoCtrl->SetValue(empleado->GetApellido());
    edadCtrl->SetValue(wxString::Format("%d", empleado->GetEdad()));
    salarioBaseCtrl->SetValue(wxString::Format("%.2f", empleado->GetSalarioBase()));

    // Rellenar campos específicos según el tipo de empleado
    if (tipoEmpleado == TipoEmpleado::POR_HORAS)
    {
        auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
        if (porHoras)
        {
            horasCtrl->SetValue(wxString::Format("%d", porHoras->GetHorasTrabajadas()));
            tarifaCtrl->SetValue(wxString::Format("%.2f", porHoras->GetTarifaHora()));
        }
    }
    else if (tipoEmpleado == TipoEmpleado::ASALARIADO)
    {
        auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
        if (asalariado)
        {
            semanasCtrl->SetValue(wxString::Format("%d", asalariado->GetSemanasAnuales()));
        }
    }
    else if (tipoEmpleado == TipoEmpleado::POR_COMISION)
    {
        auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
        if (porComision)
        {
            semanasCtrl->SetValue(wxString::Format("%d", porComision->GetSemanasAnuales()));
            ventasCtrl->SetValue(wxString::Format("%.2f", porComision->GetMontoVentas()));
            porcentajeCtrl->SetValue(wxString::Format("%.2f", porComision->GetPorcentajeComision()));
        }
    }
}

// Cambiar el formulario dinámico según el tipo de empleado seleccionado
void MainFrame::CambiarFormulario(wxCommandEvent &event)
{
    bool destruir = formularioPanel->DestroyChildren();
    if (!destruir)
    {
        wxMessageBox("Error al destruir los controles del formulario.", "Error", wxICON_ERROR);
        return;
    }

    formSizer = new wxBoxSizer(wxVERTICAL);

    nombreCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    apellidoCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    edadCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    salarioBaseCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);

    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Nombre"), 0, wxALL, 5);
    formSizer->Add(nombreCtrl, 0, wxEXPAND | wxALL, 5);
    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Apellido"), 0, wxALL, 5);
    formSizer->Add(apellidoCtrl, 0, wxEXPAND | wxALL, 5);
    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Edad"), 0, wxALL, 5);
    formSizer->Add(edadCtrl, 0, wxEXPAND | wxALL, 5);
    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Salario Base"), 0, wxALL, 5);
    formSizer->Add(salarioBaseCtrl, 0, wxEXPAND | wxALL, 5);

    int tipoSeleccionado = tipoEmpleadoChoice->GetSelection();
    if (tipoSeleccionado == 0) // Por Horas
    {
        horasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        tarifaCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Horas Trabajadas"), 0, wxALL, 5);
        formSizer->Add(horasCtrl, 0, wxEXPAND | wxALL, 5);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Tarifa por Hora"), 0, wxALL, 5);
        formSizer->Add(tarifaCtrl, 0, wxEXPAND | wxALL, 5);
    }
    else if (tipoSeleccionado == 1) // Asalariado
    {
        semanasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Semanas anuales"), 0, wxALL, 5);
        formSizer->Add(semanasCtrl, 0, wxEXPAND | wxALL, 5);
    }
    else if (tipoSeleccionado == 2) // Por Comisión
    {
        semanasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        ventasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        porcentajeCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Semanas anuales"), 0, wxALL, 5);
        formSizer->Add(semanasCtrl, 0, wxEXPAND | wxALL, 5);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Monto Ventas"), 0, wxALL, 5);
        formSizer->Add(ventasCtrl, 0, wxEXPAND | wxALL, 5);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Porcentaje Comision (0%-100%)"), 0, wxALL, 5);
        formSizer->Add(porcentajeCtrl, 0, wxEXPAND | wxALL, 5);
    }

    formularioPanel->SetSizer(formSizer);
    formularioPanel->Layout();
}

// Refrescar informacion
void MainFrame::RefrescarInformacion()
{
    RefrescarInfoEmpresa();
    RefrescarListaEmpleados();
}

// Refrescar la información de la empresa
void MainFrame::RefrescarInfoEmpresa()
{
    // Actualizar el total de empleados
    int totalEmpleados = empresa->ObtenerNumeroEmpleados();
    totalEmpleadosText->SetLabel(wxString::Format("Total de Empleados: %d", totalEmpleados));

    // Contar los empleados por tipo
    int empleadosPorHoras = empresa->ContarEmpleadosPorTipo(TipoEmpleado::POR_HORAS);
    int empleadosAsalariados = empresa->ContarEmpleadosPorTipo(TipoEmpleado::ASALARIADO);
    int empleadosPorComision = empresa->ContarEmpleadosPorTipo(TipoEmpleado::POR_COMISION);

    // Actualizar los textos de cada categoría
    empleadosPorHorasText->SetLabel(wxString::Format("Empleados por Horas: %d", empleadosPorHoras));
    empleadosAsalariadosText->SetLabel(wxString::Format("Empleados Asalariados: %d", empleadosAsalariados));
    empleadosPorComisionText->SetLabel(wxString::Format("Empleados por Comision: %d", empleadosPorComision));

    // Actualizar el total de gastos (suma de salarios)
    double totalGastos = empresa->CalcularGastosTotales();
    gastosTotales->SetLabel(wxString::Format("Gastos totales: $%.2f", totalGastos));

    empresaNombreText->SetLabel("Nombre: " + empresa->GetNombre());
    empresaDireccionText->SetLabel("Direccion: " + empresa->GetDireccion());
    empresaTelefonoText->SetLabel("Telefono: " + empresa->GetTelefono());

    empresaNombreCtrl->SetValue(empresa->GetNombre());
    empresaDireccionCtrl->SetValue(empresa->GetDireccion());
    empresaTelefonoCtrl->SetValue(empresa->GetTelefono());
}

// Refrescar la lista de empleados
void MainFrame::RefrescarListaEmpleados()
{
    int totalEmpleados = empresa->ObtenerNumeroEmpleados();
    listaEmpleados->DeleteAllItems();

    for (int i = 0; i < empresa->ObtenerNumeroEmpleados(); i++)
    {
        std::shared_ptr<Empleado> empleado = empresa->ObtenerEmpleado(i);
        if (empleado)
        {
            long index = listaEmpleados->InsertItem(i, wxString::Format("%d", empleado->GetNumeroEmpleado()));
            listaEmpleados->SetItem(index, 1, empleado->GetNombre());
            listaEmpleados->SetItem(index, 2, empleado->GetApellido());
            listaEmpleados->SetItem(index, 3, wxString::Format("%d", empleado->GetEdad()));
            listaEmpleados->SetItem(index, 4, empleado->GetTipoEmpleadoString());
            listaEmpleados->SetItem(index, 5, wxString::Format("$%.2f", empleado->CalcularSalario()));
        }
    }
}

// Cargar datos desde archivo
void MainFrame::CargarArchivo(const std::string &filename)
{
    empresa->CargarDatosArchivo(filename); // Cargar datos desde archivo
    RefrescarInformacion();
}

// Ajustar el tamaño de la fuente de un control
void MainFrame::AjustarFuente(wxWindow *control, int pointSize)
{
    wxFont font = control->GetFont();
    font.SetPointSize(pointSize);
    control->SetFont(font);
}

// Limpiar los campos del formulario
void LimpiarFormulario(MainFrame &frame)
{
    if (frame.nombreCtrl)
        frame.nombreCtrl->Clear();
    if (frame.apellidoCtrl)
        frame.apellidoCtrl->Clear();
    if (frame.edadCtrl)
        frame.edadCtrl->Clear();
    if (frame.salarioBaseCtrl)
        frame.salarioBaseCtrl->Clear();

    if (frame.tipoEmpleadoChoice->GetSelection() == 0)
    {
        if (frame.horasCtrl)
            frame.horasCtrl->Clear();
        if (frame.tarifaCtrl)
            frame.tarifaCtrl->Clear();
    }
    else if (frame.tipoEmpleadoChoice->GetSelection() == 1)
    {
        if (frame.semanasCtrl)
            frame.semanasCtrl->Clear();
    }
    else if (frame.tipoEmpleadoChoice->GetSelection() == 2)
    {
        if (frame.semanasCtrl)
            frame.semanasCtrl->Clear();
        if (frame.ventasCtrl)
            frame.ventasCtrl->Clear();
        if (frame.porcentajeCtrl)
            frame.porcentajeCtrl->Clear();
    }
}

std::string ToLower(const std::string &str)
{
    std::string resultado = str;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

// Destructor que guarda los cambios realizados
MainFrame::~MainFrame()
{
    if (empresa->GetCambios())
    {
        empresa->GuardarDatosArchivo("data/empresa.txt");
    }
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_OPEN, MainFrame::OnImportar)
        EVT_MENU(wxID_SAVE, MainFrame::OnExportar)
            EVT_MENU(wxID_EXIT, MainFrame::OnSalir)
                EVT_MENU(wxID_ABOUT, MainFrame::OnAcercaDe)
                    wxEND_EVENT_TABLE()