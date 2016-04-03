/***************************************************************
 * Name:      EasyRoutingApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Dmitry Zykov (dmz64@yandex.ru)
 * Created:   2016-04-03
 * Copyright: Dmitry Zykov (eltech.ru)
 * License:
 **************************************************************/

#include "EasyRoutingApp.h"

//(*AppHeaders
#include "EasyRoutingMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EasyRoutingApp);

bool EasyRoutingApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EasyRoutingFrame* Frame = new EasyRoutingFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
