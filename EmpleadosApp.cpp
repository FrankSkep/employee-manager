
#include <wx/wx.h>
#include "Mainframe.h"

class EmpleadosApp : public wxApp
{
public:
    virtual bool OnInit();
};
bool EmpleadosApp::OnInit()
{
    MainFrame *frame = new MainFrame("Gestion de Empleados");
    frame->SetSize(900, 700);
    frame->Show(true);
    frame->AgregarDatosAleatorios();
    return true;
}

IMPLEMENT_APP(EmpleadosApp)