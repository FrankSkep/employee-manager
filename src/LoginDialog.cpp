#include "../include/LoginDialog.h"
#include <wx/wx.h>

LoginDialog::LoginDialog(const wxString &title) : wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Título del diálogo
    wxStaticText *dialogTitle = new wxStaticText(this, wxID_ANY, "Inicio de Sesión", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont titleFont = dialogTitle->GetFont();
    titleFont.SetPointSize(14);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    dialogTitle->SetFont(titleFont);
    mainSizer->Add(dialogTitle, 0, wxALIGN_CENTER | wxALL, 10);

    // Nombre de usuario
    wxStaticText *usernameLabel = new wxStaticText(this, wxID_ANY, "Nombre de usuario:");
    mainSizer->Add(usernameLabel, 0, wxALL, 10);

    usernameCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(usernameCtrl, 0, wxEXPAND | wxALL, 10);

    // Contraseña
    wxStaticText *passwordLabel = new wxStaticText(this, wxID_ANY, "Contraseña:");
    mainSizer->Add(passwordLabel, 0, wxALL, 10);

    passwordCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    mainSizer->Add(passwordCtrl, 0, wxEXPAND | wxALL, 10);

    // Botón de inicio de sesión
    wxButton *loginButton = new wxButton(this, wxID_OK, "Iniciar sesión");
    mainSizer->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 10);

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
        wxMessageBox("Nombre de usuario o contraseña incorrectos.", "Error", wxICON_ERROR);
    }
}