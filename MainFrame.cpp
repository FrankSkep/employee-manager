#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/scrolwin.h>
#include <wx/artprov.h>
#include <memory>
#include <vector>
#include "MainFrame.h"
#include "EmpleadoAsalariado.h"
#include "EmpleadoPorComision.h"
#include "EmpleadoPorHoras.h"
#include "EmpleadoAsalariado.h"
#include "EmpleadoPorComision.h"
#include "EmpleadoPorHoras.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 700)),
                                              nombreCtrl(nullptr), apellidoCtrl(nullptr), numEmpCtrl(nullptr), salarioBaseCtrl(nullptr),
                                              horasCtrl(nullptr), tarifaCtrl(nullptr), semanasCtrl(nullptr), ventasCtrl(nullptr), porcentajeCtrl(nullptr)
{
    // Crear el menú
    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&Nuevo\tCtrl-N", "Crear un nuevo archivo");
    fileMenu->Append(wxID_OPEN, "&Abrir\tCtrl-O", "Abrir un archivo existente");
    fileMenu->Append(wxID_SAVE, "&Guardar\tCtrl-S", "Guardar el archivo actual");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Salir de la aplicación");

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&Acerca de\tF1", "Mostrar información de la aplicación");

    menuBar->Append(fileMenu, "&Archivo");
    menuBar->Append(helpMenu, "&Ayuda");

    SetMenuBar(menuBar);

    // Crear la barra de herramientas
    wxToolBar *toolBar = CreateToolBar();
    toolBar->AddTool(wxID_NEW, "Nuevo", wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR), "Crear un nuevo archivo");
    toolBar->AddTool(wxID_OPEN, "Abrir", wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), "Abrir un archivo existente");
    toolBar->AddTool(wxID_SAVE, "Guardar", wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), "Guardar el archivo actual");
    toolBar->Realize();

    // Layout principal
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Panel izquierdo: lista de empleados
    wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);

    // Título
    wxStaticText *titleText = new wxStaticText(this, wxID_ANY, "Gestion de Empleados", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font = titleText->GetFont();
    font.SetPointSize(16);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetForegroundColour(*wxWHITE);
    titleText->SetFont(font);
    leftSizer->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    // Campo de búsqueda
    searchCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    searchCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnBuscar, this);
    leftSizer->Add(new wxStaticText(this, wxID_ANY, "Buscar Empleado"), 0, wxALL, 5);
    leftSizer->Add(searchCtrl, 0, wxEXPAND | wxALL, 5);

    // Lista de empleados
    listaEmpleados = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(900, 350), wxLC_REPORT | wxLC_SINGLE_SEL);
    listaEmpleados->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
    listaEmpleados->InsertColumn(1, "Nombre", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(2, "Apellido", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(3, "Tipo", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(4, "Salario", wxLIST_FORMAT_LEFT, 100);

    listaEmpleados->Bind(wxEVT_LIST_ITEM_SELECTED, [&](wxListEvent &event)
                         {
        long itemIndex = event.GetIndex();
        auto empleado = empleados[itemIndex];
        tipoEmpleadoChoice->SetSelection(static_cast<int>(empleado->getTipoEmpleado()));

        // Rellenar formulario con los datos del empleado seleccionado
        nombreCtrl->SetValue(empleado->getNombre());
        apellidoCtrl->SetValue(empleado->getApellido());
        numEmpCtrl->SetValue(wxString::Format("%d", empleado->getNumEmp()));
        salarioBaseCtrl->SetValue(wxString::Format("%.2f", empleado->getSalarioBase()));

        if (empleado->getTipoEmpleado() == TipoEmpleado::PorHoras)
        {
            auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
            horasCtrl->SetValue(wxString::Format("%d", porHoras->getHorasTrabajadas()));
            tarifaCtrl->SetValue(wxString::Format("%.2f", porHoras->getTarifaHora()));
        }
        else if (empleado->getTipoEmpleado() == TipoEmpleado::Asalariado)
        {
            auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
            semanasCtrl->SetValue(wxString::Format("%d", asalariado->getSemanas()));
        }
        else if (empleado->getTipoEmpleado() == TipoEmpleado::PorComision)
        {
            auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
            semanasCtrl->SetValue(wxString::Format("%d", porComision->getSemanas()));
            ventasCtrl->SetValue(wxString::Format("%.2f", porComision->getVentas()));
            porcentajeCtrl->SetValue(wxString::Format("%.2f", porComision->getPorcenComision()));
        } });

    leftSizer->Add(listaEmpleados, 1, wxEXPAND | wxALL, 10);

    // Panel derecho: información de empleados
    wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *infoTitle = new wxStaticText(this, wxID_ANY, "Informacion de Empleados", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont infoFont = infoTitle->GetFont();
    infoFont.SetPointSize(14);
    infoFont.SetWeight(wxFONTWEIGHT_BOLD);
    infoTitle->SetFont(infoFont);
    rightSizer->Add(infoTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    totalEmpleadosText = new wxStaticText(this, wxID_ANY, "Total de Empleados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rightSizer->Add(totalEmpleadosText, 0, wxALL, 5);

    empleadosPorHorasText = new wxStaticText(this, wxID_ANY, "Empleados por Horas: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rightSizer->Add(empleadosPorHorasText, 0, wxALL, 5);

    empleadosAsalariadosText = new wxStaticText(this, wxID_ANY, "Empleados Asalariados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rightSizer->Add(empleadosAsalariadosText, 0, wxALL, 5);

    empleadosPorComisionText = new wxStaticText(this, wxID_ANY, "Empleados por Comision: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rightSizer->Add(empleadosPorComisionText, 0, wxALL, 5);

    ingresosTotalesText = new wxStaticText(this, wxID_ANY, "Ingresos Totales: $0.00", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    rightSizer->Add(ingresosTotalesText, 0, wxALL, 5);

    // Añadir los sizers al sizer principal
    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(rightSizer, 0, wxEXPAND | wxALL, 10);

    // Panel inferior: formulario y botones
    wxBoxSizer *lowerSizer = new wxBoxSizer(wxHORIZONTAL);

    // Formulario dinámico
    wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

    tipoEmpleadoChoice = new wxChoice(this, wxID_ANY);
    tipoEmpleadoChoice->Append("Por Horas");
    tipoEmpleadoChoice->Append("Asalariado");
    tipoEmpleadoChoice->Append("Por Comisión");
    tipoEmpleadoChoice->Bind(wxEVT_CHOICE, &MainFrame::CambiarFormulario, this);
    formSizer->Add(new wxStaticText(this, wxID_ANY, "Tipo de Empleado"), 0, wxALL, 5);
    formSizer->Add(tipoEmpleadoChoice, 0, wxEXPAND | wxALL, 5);

    formularioPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300), wxVSCROLL);
    // formularioPanel->SetScrollRate(5, 5);
    formSizer->Add(formularioPanel, 1, wxEXPAND | wxALL, 5);

    lowerSizer->Add(formSizer, 1, wxEXPAND | wxALL, 10);

    // Botones
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxVERTICAL);

    // Botones con iconos
    wxButton *addButton = new wxButton(this, wxID_ANY, "Agregar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    addButton->SetBitmap(wxArtProvider::GetBitmap(wxART_PLUS, wxART_BUTTON));
    wxButton *editButton = new wxButton(this, wxID_ANY, "Editar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    editButton->SetBitmap(wxArtProvider::GetBitmap(wxART_EDIT, wxART_BUTTON));
    wxButton *deleteButton = new wxButton(this, wxID_ANY, "Eliminar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    deleteButton->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_BUTTON));
    wxButton *viewDetailsButton = new wxButton(this, wxID_ANY, "Ver Detalles", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    viewDetailsButton->SetBitmap(wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON));

    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAgregar, this);
    editButton->Bind(wxEVT_BUTTON, &MainFrame::OnEditar, this);
    deleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnEliminar, this);
    viewDetailsButton->Bind(wxEVT_BUTTON, &MainFrame::OnVerDetalles, this);

    buttonSizer->Add(addButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(editButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(deleteButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(viewDetailsButton, 0, wxEXPAND | wxALL, 5);
    lowerSizer->Add(buttonSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

    mainSizer->Add(lowerSizer, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);

    // Inicializar formulario
    wxCommandEvent dummyEvent;
    CambiarFormulario(dummyEvent);
    // AgregarDatosAleatorios();
}

void MainFrame::OnAgregar(wxCommandEvent &event)
{
    if (nombreCtrl->GetValue().IsEmpty() || apellidoCtrl->GetValue().IsEmpty() || numEmpCtrl->GetValue().IsEmpty() || salarioBaseCtrl->GetValue().IsEmpty())
    {
        wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
        return;
    }

    // Crear empleado según el tipo seleccionado y agregarlo a la lista
    int id = wxAtoi(numEmpCtrl->GetValue());
    if (ExisteID(id))
    {
        wxMessageBox("El ID ya existe. Por favor, ingrese un ID diferente.", "Error", wxICON_ERROR);
        return;
    }

    wxString nombre = nombreCtrl->GetValue();
    wxString apellido = apellidoCtrl->GetValue();

    double salarioBase = wxAtof(salarioBaseCtrl->GetValue());

    int tipoSeleccionado = tipoEmpleadoChoice->GetSelection();
    if (tipoSeleccionado == 0) // Por Horas
    {
        int horas = wxAtoi(horasCtrl->GetValue());
        float tarifa = wxAtof(tarifaCtrl->GetValue());
        empleados.push_back(std::make_shared<EmpleadoPorHoras>(nombre.ToStdString(), apellido.ToStdString(), id, salarioBase, horas, tarifa));
    }
    else if (tipoSeleccionado == 1) // Asalariado
    {
        int semanas = wxAtoi(semanasCtrl->GetValue());
        empleados.push_back(std::make_shared<EmpleadoAsalariado>(nombre.ToStdString(), apellido.ToStdString(), id, salarioBase, semanas));
    }
    else if (tipoSeleccionado == 2) // Por Comisión
    {
        int semanas = wxAtoi(semanasCtrl->GetValue());
        double ventas = wxAtof(ventasCtrl->GetValue());
        double porcentaje = wxAtof(porcentajeCtrl->GetValue());
        empleados.push_back(std::make_shared<EmpleadoPorComision>(nombre.ToStdString(), apellido.ToStdString(), id, salarioBase, semanas, ventas, porcentaje));
    }

    ActualizarLista();
}

bool MainFrame::ExisteID(int id)
{
    for (const auto &empleado : empleados)
    {
        if (empleado->getNumEmp() == id)
        {
            return true;
        }
    }
    return false;
}

void MainFrame::OnEditar(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, selecciona un empleado para editar.", "Error", wxICON_ERROR);
        return;
    }

    auto empleado = empleados[itemIndex];
    empleado->setNombre(nombreCtrl->GetValue().ToStdString());
    empleado->setApellido(apellidoCtrl->GetValue().ToStdString());
    empleado->setNumEmp(wxAtoi(numEmpCtrl->GetValue()));
    empleado->setSalarioBase(wxAtof(salarioBaseCtrl->GetValue()));

    if (empleado->getTipoEmpleado() == TipoEmpleado::PorHoras)
    {
        auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
        porHoras->setHoras(wxAtoi(horasCtrl->GetValue()));
        porHoras->setTarifa(wxAtof(tarifaCtrl->GetValue()));
    }
    else if (empleado->getTipoEmpleado() == TipoEmpleado::Asalariado)
    {
        auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
        asalariado->setSemanas(wxAtoi(semanasCtrl->GetValue()));
    }
    else if (empleado->getTipoEmpleado() == TipoEmpleado::PorComision)
    {
        auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
        porComision->setSemanas(wxAtoi(semanasCtrl->GetValue()));
        porComision->setVentas(wxAtof(ventasCtrl->GetValue()));
        porComision->setPorcenComision(wxAtof(porcentajeCtrl->GetValue()));
    }

    ActualizarLista();
    wxMessageBox("Empleado actualizado correctamente.", "Informacion", wxICON_INFORMATION);
}

void MainFrame::OnEliminar(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex != wxNOT_FOUND)
    {
        int respuesta = wxMessageBox("¿Estas seguro de que deseas eliminar este empleado?", "Confirmacion", wxYES_NO | wxICON_QUESTION);
        if (respuesta == wxYES)
        {
            empleados.erase(empleados.begin() + itemIndex);
            ActualizarLista();
            wxMessageBox("Empleado eliminado correctamente.", "Informacion", wxICON_INFORMATION);
        }
    }
}

void MainFrame::OnVerDetalles(wxCommandEvent &event)
{
    long itemIndex = listaEmpleados->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, selecciona un empleado para ver los detalles.", "Error", wxICON_ERROR);
        return;
    }

    auto empleado = empleados[itemIndex];
    wxString detalles = empleado->getInfo();
    wxMessageBox(detalles, "Detalles del Empleado", wxICON_INFORMATION);
}

void MainFrame::OnBuscar(wxCommandEvent &event)
{
    wxString query = searchCtrl->GetValue().Lower();
    listaEmpleados->DeleteAllItems();

    for (size_t i = 0; i < empleados.size(); ++i)
    {
        auto emp = empleados[i];
        std::string nombreLower = emp->getNombre();
        std::transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);
        std::string apellidoLower = emp->getApellido();
        std::transform(apellidoLower.begin(), apellidoLower.end(), apellidoLower.begin(), ::tolower);
        if (nombreLower.find(query.ToStdString()) != std::string::npos || apellidoLower.find(query.ToStdString()) != std::string::npos)
        {
            listaEmpleados->InsertItem(i, wxString::Format("%d", emp->getNumEmp()));
            listaEmpleados->SetItem(i, 1, emp->getNombre());
            listaEmpleados->SetItem(i, 2, emp->getApellido());
            listaEmpleados->SetItem(i, 3, (emp->getTipoEmpleado() == TipoEmpleado::PorHoras) ? "Por Horas" : (emp->getTipoEmpleado() == TipoEmpleado::Asalariado) ? "Asalariado"
                                                                                                                                                                  : "Por Comisión");
            listaEmpleados->SetItem(i, 4, wxString::Format("%.2f", emp->calcularSalario()));
        }
    }
}

void MainFrame::ActualizarLista()
{
    listaEmpleados->DeleteAllItems();
    int totalEmpleados = 0;
    int empleadosPorHoras = 0;
    int empleadosAsalariados = 0;
    int empleadosPorComision = 0;
    double ingresosTotales = 0.0;

    for (size_t i = 0; i < empleados.size(); ++i)
    {
        auto emp = empleados[i];
        listaEmpleados->InsertItem(i, wxString::Format("%d", emp->getNumEmp()));
        listaEmpleados->SetItem(i, 1, emp->getNombre());
        listaEmpleados->SetItem(i, 2, emp->getApellido());
        listaEmpleados->SetItem(i, 3, (emp->getTipoEmpleado() == TipoEmpleado::PorHoras) ? "Por Horas" : (emp->getTipoEmpleado() == TipoEmpleado::Asalariado) ? "Asalariado"
                                                                                                                                                              : "Por Comisión");
        listaEmpleados->SetItem(i, 4, wxString::Format("%.2f", emp->calcularSalario()));

        totalEmpleados++;
        ingresosTotales += emp->calcularSalario();

        if (emp->getTipoEmpleado() == TipoEmpleado::PorHoras)
        {
            empleadosPorHoras++;
        }
        else if (emp->getTipoEmpleado() == TipoEmpleado::Asalariado)
        {
            empleadosAsalariados++;
        }
        else if (emp->getTipoEmpleado() == TipoEmpleado::PorComision)
        {
            empleadosPorComision++;
        }
    }

    totalEmpleadosText->SetLabel(wxString::Format("Total de Empleados: %d", totalEmpleados));
    empleadosPorHorasText->SetLabel(wxString::Format("Empleados por Horas: %d", empleadosPorHoras));
    empleadosAsalariadosText->SetLabel(wxString::Format("Empleados Asalariados: %d", empleadosAsalariados));
    empleadosPorComisionText->SetLabel(wxString::Format("Empleados por Comision: %d", empleadosPorComision));
    ingresosTotalesText->SetLabel(wxString::Format("Ingresos Totales: $%.2f", ingresosTotales));
}

void MainFrame::AgregarDatosAleatorios()
{
    empleados.push_back(std::make_shared<EmpleadoPorHoras>("Juan", "Perez", 1, 1000, 40, 10));
    empleados.push_back(std::make_shared<EmpleadoAsalariado>("Maria", "Gomez", 2, 2000, 48));
    empleados.push_back(std::make_shared<EmpleadoPorComision>("Pedro", "Lopez", 3, 1500, 52, 5000, 0.1));
    empleados.push_back(std::make_shared<EmpleadoPorHoras>("Ana", "Rodriguez", 4, 1200, 35, 12));
    empleados.push_back(std::make_shared<EmpleadoAsalariado>("Carlos", "Garcia", 5, 1800, 50));
    empleados.push_back(std::make_shared<EmpleadoPorComision>("Laura", "Martinez", 6, 1600, 45, 6000, 0.15));
    empleados.push_back(std::make_shared<EmpleadoPorHoras>("Jose", "Sanchez", 7, 1100, 38, 11));
    empleados.push_back(std::make_shared<EmpleadoAsalariado>("Sofia", "Fernandez", 8, 1900, 46));
    empleados.push_back(std::make_shared<EmpleadoPorComision>("Luis", "Torres", 9, 1400, 55, 7000, 0.2));
    ActualizarLista();
}

void MainFrame::CambiarFormulario(wxCommandEvent &event)
{
    formularioPanel->DestroyChildren();
    wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

    nombreCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    apellidoCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    numEmpCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    salarioBaseCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);

    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Nombre"), 0, wxALL, 5);
    formSizer->Add(nombreCtrl, 0, wxEXPAND | wxALL, 5);
    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Apellido"), 0, wxALL, 5);
    formSizer->Add(apellidoCtrl, 0, wxEXPAND | wxALL, 5);
    formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "ID"), 0, wxALL, 5);
    formSizer->Add(numEmpCtrl, 0, wxEXPAND | wxALL, 5);
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
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Semanas por Año"), 0, wxALL, 5);
        formSizer->Add(semanasCtrl, 0, wxEXPAND | wxALL, 5);
    }
    else if (tipoSeleccionado == 2) // Por Comisión
    {
        semanasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        ventasCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        porcentajeCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Semanas por Año"), 0, wxALL, 5);
        formSizer->Add(semanasCtrl, 0, wxEXPAND | wxALL, 5);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Monto Ventas"), 0, wxALL, 5);
        formSizer->Add(ventasCtrl, 0, wxEXPAND | wxALL, 5);
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Porcentaje Comisión"), 0, wxALL, 5);
        formSizer->Add(porcentajeCtrl, 0, wxEXPAND | wxALL, 5);
    }

    formularioPanel->SetSizer(formSizer);
    formularioPanel->Layout();
}
