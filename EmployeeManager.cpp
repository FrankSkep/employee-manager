#include <wx/wx.h>
#include <wx/intl.h>
#include "include/MainFrame.h"
#include "include/Empresa.h"
#include "include/LoginDialog.h"

class EmployeeManager : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame *frame = new MainFrame("Employee Manager");
        frame->SetSize(1340, 720);
        frame->Show(true);
        return true;
    }
};

IMPLEMENT_APP(EmployeeManager)