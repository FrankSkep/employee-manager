#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

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
    void OnLogin(wxCommandEvent &event);
};

#endif