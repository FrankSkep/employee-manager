#include <wx/wx.h>
#include <wx/intl.h>
#include <locale>
#include "include/MainFrame.h"
#include "include/Empresa.h"
#include "include/LoginDialog.h"

class EmployeeManager : public wxApp
{
public:
    virtual bool OnInit()
    {
        LoginDialog loginDialog("Identificacion");
        if (loginDialog.ShowModal() == wxID_OK)
        {
            MainFrame *frame = new MainFrame("Employee Manager");
            frame->SetSize(1600, 860);
            frame->Show(true);
            return true;
        }
        return false;
    }
};

IMPLEMENT_APP(EmployeeManager)