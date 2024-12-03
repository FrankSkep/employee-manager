#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/scrolwin.h>
#include <wx/artprov.h>
#include <memory>
#include <vector>
#include "../include/MainFrame.h"
#include "../include/EmpleadoAsalariado.h"
#include "../include/EmpleadoPorComision.h"
#include "../include/EmpleadoPorHoras.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)),
                                              nombreCtrl(nullptr), apellidoCtrl(nullptr), numEmpCtrl(nullptr), salarioBaseCtrl(nullptr),
                                              horasCtrl(nullptr), tarifaCtrl(nullptr), semanasCtrl(nullptr), ventasCtrl(nullptr), porcentajeCtrl(nullptr)
{
    empresa = std::make_unique<Empresa>("Empresa que no existe", "Calle Falsa 123", "123-456-7890");

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

    // Layout principal
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Panel izquierdo: lista de empleados
    wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);

    // Título
    wxStaticText *titleText = new wxStaticText(this, wxID_ANY, " GESTION DE EMPLEADOS ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font = titleText->GetFont();
    font.SetPointSize(16);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetForegroundColour(*wxBLACK);
    titleText->SetBackgroundColour(*wxWHITE);
    titleText->SetFont(font);
    leftSizer->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    // Crear un nuevo panel para la barra de búsqueda
    wxPanel *searchPanel = new wxPanel(this, wxID_ANY);
    searchPanel->SetBackgroundColour(*wxWHITE);

    // Crear un sizer para el panel de búsqueda
    wxBoxSizer *searchSizer = new wxBoxSizer(wxVERTICAL);

    // Crear la barra de búsqueda
    searchCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "", wxDefaultPosition, wxSize(600, -1), wxTE_PROCESS_ENTER);
    searchCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnBuscar, this);

    // Añadir el texto y la barra de búsqueda al sizer del panel de búsqueda
    searchSizer->Add(new wxStaticText(searchPanel, wxID_ANY, "Buscar Empleado"), 0, wxALL, 5);
    searchSizer->Add(searchCtrl, 0, wxEXPAND | wxALL, 5);

    // Establecer el sizer del panel de búsqueda
    searchPanel->SetSizer(searchSizer);

    // Añadir el panel de búsqueda al sizer izquierdo
    leftSizer->Add(searchPanel, 0, wxEXPAND | wxALL, 5);

    // Lista de empleados
    listaEmpleados = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(600, 350), wxLC_REPORT | wxLC_SINGLE_SEL);
    listaEmpleados->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
    listaEmpleados->InsertColumn(1, "Nombre", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(2, "Apellido", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(3, "Tipo", wxLIST_FORMAT_LEFT, 150);
    listaEmpleados->InsertColumn(4, "Salario", wxLIST_FORMAT_LEFT, 100);
    listaEmpleados->SetSize(wxSize(600, 350));

    listaEmpleados->Bind(wxEVT_LIST_ITEM_SELECTED, [&](wxListEvent &event)
                         {
        long itemIndex = event.GetIndex();
        RellenarFormulario(itemIndex); });

    leftSizer->Add(listaEmpleados, 1, wxEXPAND | wxALL, 10);

    // Panel derecho: información de empleados
    wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);

    // Crear un panel para la tarjeta de información general
    wxPanel *infoPanel = new wxPanel(this, wxID_ANY);
    infoPanel->SetBackgroundColour(*wxWHITE); // Cambiar color de fondo del panel

    wxBoxSizer *infoSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *infoTitle = new wxStaticText(infoPanel, wxID_ANY, "Informacion de la Empresa", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont infoFont = infoTitle->GetFont();
    infoFont.SetPointSize(14);
    infoFont.SetWeight(wxFONTWEIGHT_BOLD);
    infoTitle->SetFont(infoFont);
    infoSizer->Add(infoTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    // Información de la empresa
    wxStaticText *empresaNombreText = new wxStaticText(infoPanel, wxID_ANY, "Nombre: " + empresa->GetNombre(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empresaNombreText, 0, wxALL, 10);

    wxStaticText *empresaDireccionText = new wxStaticText(infoPanel, wxID_ANY, "Direccion: " + empresa->GetDireccion(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empresaDireccionText, 0, wxALL, 10);

    wxStaticText *empresaTelefonoText = new wxStaticText(infoPanel, wxID_ANY, "Telefono: " + empresa->GetTelefono(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empresaTelefonoText, 0, wxALL, 10);

    totalEmpleadosText = new wxStaticText(infoPanel, wxID_ANY, "Total de Empleados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(totalEmpleadosText, 0, wxALL, 10);

    empleadosPorHorasText = new wxStaticText(infoPanel, wxID_ANY, "Empleados por Horas: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empleadosPorHorasText, 0, wxALL, 10);

    empleadosAsalariadosText = new wxStaticText(infoPanel, wxID_ANY, "Empleados Asalariados: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empleadosAsalariadosText, 0, wxALL, 10);

    empleadosPorComisionText = new wxStaticText(infoPanel, wxID_ANY, "Empleados por Comision: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(empleadosPorComisionText, 0, wxALL, 10);

    ingresosTotalesText = new wxStaticText(infoPanel, wxID_ANY, "Gastos totales: $0.00", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    infoSizer->Add(ingresosTotalesText, 0, wxALL, 10);

    // Establecer el sizer del panel y añadir el panel al sizer derecho
    infoPanel->SetSizer(infoSizer);
    rightSizer->Add(infoPanel, 1, wxEXPAND | wxALL, 10);

    // Añadir los sizers al sizer principal
    mainSizer->Add(rightSizer, 0, wxEXPAND | wxALL, 10);
    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 10);

    // Panel inferior: formulario y botones
    wxBoxSizer *lowerSizer = new wxBoxSizer(wxHORIZONTAL);

    // Formulario dinámico
    wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

    // Agregar titulo al formulario
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

    // Botones
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *addButton = new wxButton(this, wxID_ANY, "Agregar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *editButton = new wxButton(this, wxID_ANY, "Editar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *deleteButton = new wxButton(this, wxID_ANY, "Eliminar", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxButton *viewDetailsButton = new wxButton(this, wxID_ANY, "Detalles", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

    addButton->SetMinSize(wxSize(-1, 40));
    editButton->SetMinSize(wxSize(-1, 40));
    deleteButton->SetMinSize(wxSize(-1, 40));
    viewDetailsButton->SetMinSize(wxSize(-1, 40));

    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAgregar, this);
    editButton->Bind(wxEVT_BUTTON, &MainFrame::OnEditar, this);
    deleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnEliminar, this);
    viewDetailsButton->Bind(wxEVT_BUTTON, &MainFrame::OnVerDetalles, this);

    buttonSizer->Add(addButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(editButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(deleteButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(viewDetailsButton, 0, wxEXPAND | wxALL, 5);

    // Agregar botones al sizer inferior
    formSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    mainSizer->Add(lowerSizer, 1, wxEXPAND | wxALL, 10);
    SetSizer(mainSizer);

    // Inicializar formulario
    wxCommandEvent dummyEvent;
    CambiarFormulario(dummyEvent);
}

// Agregar un empleado
void MainFrame::OnAgregar(wxCommandEvent &event)
{
    int tipoSeleccionado = tipoEmpleadoChoice->GetSelection();

    if (nombreCtrl->GetValue().IsEmpty() || apellidoCtrl->GetValue().IsEmpty() || numEmpCtrl->GetValue().IsEmpty() || salarioBaseCtrl->GetValue().IsEmpty() || tipoSeleccionado == wxNOT_FOUND)
    {
        wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
        return;
    }

    wxString nombre = nombreCtrl->GetValue();
    wxString apellido = apellidoCtrl->GetValue();
    int id = wxAtoi(numEmpCtrl->GetValue());
    if (empresa->ExisteEmpleado(id))
    {
        wxMessageBox("El ID ya existe. Por favor, ingrese un ID diferente.", "Error", wxICON_ERROR);
        return;
    }
    double salarioBase = wxAtof(salarioBaseCtrl->GetValue());

    // Crear empleado según el tipo seleccionado y agregarlo a la lista
    tipoSeleccionado = tipoEmpleadoChoice->GetSelection();
    if (tipoSeleccionado == 0) // Por Horas
    {
        if (horasCtrl->GetValue().IsEmpty() || tarifaCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        int horas = wxAtoi(horasCtrl->GetValue());
        float tarifa = wxAtof(tarifaCtrl->GetValue());
        empresa->AgregarEmpleado(std::make_shared<EmpleadoPorHoras>(nombre.ToStdString(), apellido.ToStdString(), salarioBase, horas, tarifa));
    }
    else if (tipoSeleccionado == 1) // Asalariado
    {
        if (semanasCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        int semanas = wxAtoi(semanasCtrl->GetValue());
        empresa->AgregarEmpleado(std::make_shared<EmpleadoAsalariado>(nombre.ToStdString(), apellido.ToStdString(), salarioBase, semanas));
    }
    else if (tipoSeleccionado == 2) // Por Comisión
    {
        if (semanasCtrl->GetValue().IsEmpty() || ventasCtrl->GetValue().IsEmpty() || porcentajeCtrl->GetValue().IsEmpty())
        {
            wxMessageBox("Por favor, completa todos los campos.", "Error", wxICON_ERROR);
            return;
        }

        int semanas = wxAtoi(semanasCtrl->GetValue());
        double ventas = wxAtof(ventasCtrl->GetValue());
        double porcentaje = wxAtof(porcentajeCtrl->GetValue());
        empresa->AgregarEmpleado(std::make_shared<EmpleadoPorComision>(nombre.ToStdString(), apellido.ToStdString(), salarioBase, semanas, ventas, porcentaje));
    }

    ActualizarInformacion();
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

    empleado->SetNombre(nombreCtrl->GetValue().ToStdString());
    empleado->SetApellido(apellidoCtrl->GetValue().ToStdString());
    empleado->SetNumeroEmpleado(wxAtoi(numEmpCtrl->GetValue()));
    empleado->SetSalarioBase(wxAtof(salarioBaseCtrl->GetValue()));

    if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_HORAS)
    {
        auto porHoras = std::dynamic_pointer_cast<EmpleadoPorHoras>(empleado);
        porHoras->SetHorasTrabajadas(wxAtoi(horasCtrl->GetValue()));
        porHoras->SetTarifaHora(wxAtof(tarifaCtrl->GetValue()));
    }
    else if (empleado->GetTipoEmpleado() == TipoEmpleado::ASALARIADO)
    {
        auto asalariado = std::dynamic_pointer_cast<EmpleadoAsalariado>(empleado);
        asalariado->SetSemanasAnuales(wxAtoi(semanasCtrl->GetValue()));
    }
    else if (empleado->GetTipoEmpleado() == TipoEmpleado::POR_COMISION)
    {
        auto porComision = std::dynamic_pointer_cast<EmpleadoPorComision>(empleado);
        porComision->SetSemanasAnuales(wxAtoi(semanasCtrl->GetValue()));
        porComision->SetMontoVentas(wxAtof(ventasCtrl->GetValue()));
        porComision->SetPorcentajeComision(wxAtof(porcentajeCtrl->GetValue()));
    }

    ActualizarInformacion();
    wxMessageBox("Empleado actualizado correctamente.", "Informacion", wxICON_INFORMATION);
}

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
    tipoEmpleadoChoice->SetSelection(static_cast<int>(tipoEmpleado));

    // Rellenar formulario con los datos del empleado seleccionado
    nombreCtrl->SetValue(empleado->GetNombre());
    apellidoCtrl->SetValue(empleado->GetApellido());
    numEmpCtrl->SetValue(wxString::Format("%d", empleado->GetNumeroEmpleado()));
    salarioBaseCtrl->SetValue(wxString::Format("%.2f", empleado->GetSalarioBase()));

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
            ActualizarInformacion();
            wxMessageBox("Empleado eliminado correctamente.", "Informacion", wxICON_INFORMATION);
        }
    }
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

// Buscar empleados por nombre o apellido
void MainFrame::OnBuscar(wxCommandEvent &event)
{
    wxString query = searchCtrl->GetValue().Lower();
    listaEmpleados->DeleteAllItems();

    for (size_t i = 0; i < empresa->ObtenerTotalEmpleados(); ++i)
    {
        auto emp = empresa->ObtenerEmpleado(i);
        std::string nombreLower = emp->GetNombre();
        std::transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);
        std::string apellidoLower = emp->GetApellido();
        std::transform(apellidoLower.begin(), apellidoLower.end(), apellidoLower.begin(), ::tolower);
        if (nombreLower.find(query.ToStdString()) != std::string::npos || apellidoLower.find(query.ToStdString()) != std::string::npos)
        {
            listaEmpleados->InsertItem(i, wxString::Format("%d", emp->GetNumeroEmpleado()));
            listaEmpleados->SetItem(i, 1, emp->GetNombre());
            listaEmpleados->SetItem(i, 2, emp->GetApellido());
            listaEmpleados->SetItem(i, 3, emp->GetTipoEmpleadoString());
            listaEmpleados->SetItem(i, 4, wxString::Format("%.2f", emp->CalcularSalario()));
        }
    }
}

// Actualizar la lista de empleados
void MainFrame::ActualizarInformacion()
{
    // Actualizar el total de empleados
    int totalEmpleados = empresa->ObtenerTotalEmpleados();
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
    ingresosTotalesText->SetLabel(wxString::Format("Gastos totales: $%.2f", totalGastos));

    // Refrescar la lista de empleados
    listaEmpleados->DeleteAllItems();

    for (int i = 0; i < totalEmpleados; i++)
    {
        std::shared_ptr<Empleado> empleado = empresa->ObtenerEmpleado(i);
        if (empleado)
        {
            long index = listaEmpleados->InsertItem(i, wxString::Format("%d", empleado->GetNumeroEmpleado()));
            listaEmpleados->SetItem(index, 1, empleado->GetNombre());
            listaEmpleados->SetItem(index, 2, empleado->GetApellido());
            listaEmpleados->SetItem(index, 3, empleado->GetTipoEmpleadoString());
            listaEmpleados->SetItem(index, 4, wxString::Format("$%.2f", empleado->CalcularSalario()));
        }
    }
}

// Cambiar el formulario dinámico según el tipo de empleado seleccionado
void MainFrame::CambiarFormulario(wxCommandEvent &event)
{
    formularioPanel->DestroyChildren();
    wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

    nombreCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    apellidoCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    numEmpCtrl = new wxTextCtrl(formularioPanel, wxID_ANY);
    numEmpCtrl->Disable();
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
        formSizer->Add(new wxStaticText(formularioPanel, wxID_ANY, "Porcentaje Comision (0\%-100\%)"), 0, wxALL, 5);
        formSizer->Add(porcentajeCtrl, 0, wxEXPAND | wxALL, 5);
    }

    formularioPanel->SetSizer(formSizer);
    formularioPanel->Layout();
}