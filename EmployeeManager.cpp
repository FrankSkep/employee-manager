#include <wx/wx.h>
#include <wx/intl.h>
#include "include/MainFrame.h"
#include "include/Empresa.h"

class EmployeeManager : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame *frame = new MainFrame("Employee Manager");
        frame->SetSize(1300, 720);
        frame->Show(true);
        return true;
    }
};

IMPLEMENT_APP(EmployeeManager)