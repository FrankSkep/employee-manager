#include "../include/LoginDialog.h"
#include <wx/wx.h>

LoginDialog::LoginDialog(const wxString &title) : wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Título del diálogo
    wxStaticText *dialogTitle = new wxStaticText(this, wxID_ANY, "Inicio de Sesion", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont titleFont = dialogTitle->GetFont();
    titleFont.SetPointSize(14);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    dialogTitle->SetFont(titleFont);
    mainSizer->Add(dialogTitle, 0, wxALIGN_CENTER | wxALL, 10);

    // Panel para los campos de entrada
    wxPanel *inputPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *inputSizer = new wxBoxSizer(wxVERTICAL);

    // Nombre de usuario
    wxStaticText *usernameLabel = new wxStaticText(inputPanel, wxID_ANY, "Nombre de usuario:");
    inputSizer->Add(usernameLabel, 0, wxALL, 5);

    usernameCtrl = new wxTextCtrl(inputPanel, wxID_ANY);
    inputSizer->Add(usernameCtrl, 0, wxEXPAND | wxALL, 5);

    // Contraseña
    wxStaticText *passwordLabel = new wxStaticText(inputPanel, wxID_ANY, "Contrasenia:");
    inputSizer->Add(passwordLabel, 0, wxALL, 5);

    passwordCtrl = new wxTextCtrl(inputPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    inputSizer->Add(passwordCtrl, 0, wxEXPAND | wxALL, 5);

    inputPanel->SetSizer(inputSizer);
    inputPanel->SetBackgroundColour(*wxWHITE);
    inputPanel->SetWindowStyle(wxBORDER_SIMPLE);
    mainSizer->Add(inputPanel, 1, wxEXPAND | wxALL, 10);

    // Sizer para los botones
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    // Botón de inicio de sesión
    wxButton *loginButton = new wxButton(this, wxID_OK, "Iniciar sesion");
    buttonSizer->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 5);

    // Botón de cancelar
    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Cancelar");
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

    // Centrar la ventana en la pantalla
    Centre();

    loginButton->Bind(wxEVT_BUTTON, &LoginDialog::OnLogin, this);
}

void LoginDialog::OnLogin(wxCommandEvent &event)
{
    wxString username = GetUsername();
    wxString password = GetPassword();

    // Validar credenciales
    if (username == "admin" && password == "4321")
    {
        EndModal(wxID_OK);
    }
    else
    {
        wxMessageBox("Nombre de usuario o contrasenia incorrectos.", "Error", wxICON_ERROR);
    }
}