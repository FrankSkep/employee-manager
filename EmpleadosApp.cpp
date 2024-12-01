
#include <wx/wx.h>
#include <wx/intl.h>
#include "Mainframe.h"

class EmpleadosApp : public wxApp
{
public:
    virtual bool OnInit();
};
bool EmpleadosApp::OnInit()
{
    MainFrame *frame = new MainFrame("Employee Manager");
    frame->SetSize(1300, 720);
    frame->Show(true);
    return true;
}

IMPLEMENT_APP(EmpleadosApp)