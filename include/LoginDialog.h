#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "Usuario.h"
#include <wx/wx.h>

class LoginDialog : public wxDialog
{
public:
    LoginDialog(const wxString &title);

    wxString GetUsername() const { return usernameCtrl->GetValue(); }
    wxString GetPassword() const { return passwordCtrl->GetValue(); }

private:
    wxTextCtrl *usernameCtrl;
    wxTextCtrl *passwordCtrl;
    void GuardarCredenciales(const Usuario& usuario, const std::string& filename);
    bool CargarCredenciales(Usuario& usuario, const std::string& filename);
    void OnLogin(wxCommandEvent &event);
};

#endif