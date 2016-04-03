/***************************************************************
 * Name:      EasyRoutingMain.h
 * Purpose:   Defines Application Frame
 * Author:    Dmitry Zykov (dmz64@yandex.ru)
 * Created:   2016-04-03
 * Copyright: Dmitry Zykov (eltech.ru)
 * License:
 **************************************************************/

#ifndef EASYROUTINGMAIN_H
#define EASYROUTINGMAIN_H

//(*Headers(EasyRoutingFrame)
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/scrolbar.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
//*)

class EasyRoutingFrame: public wxFrame
{
    public:

        EasyRoutingFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EasyRoutingFrame();

    private:

        //(*Handlers(EasyRoutingFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSpinCtrl2Change(wxSpinEvent& event);
        //*)

        //(*Identifiers(EasyRoutingFrame)
        static const long ID_STATICTEXT4;
        static const long ID_SCROLLBAR1;
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRL3;
        static const long ID_STATICTEXT2;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT3;
        static const long ID_SPINCTRL2;
        static const long ID_STATICTEXT7;
        static const long ID_SPINCTRL4;
        static const long ID_STATICTEXT5;
        static const long ID_COMBOBOX1;
        static const long ID_STATICTEXT6;
        static const long ID_COMBOBOX2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_MENUITEM1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(EasyRoutingFrame)
        wxStatusBar* StatusBar1;
        wxSpinCtrl* SpinCtrl4;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxComboBox* ComboBox1;
        wxSpinCtrl* SpinCtrl3;
        wxComboBox* ComboBox2;
        wxStaticText* StaticText7;
        wxSpinCtrl* SpinCtrl2;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxStaticText* StaticText6;
        wxSpinCtrl* SpinCtrl1;
        wxScrollBar* ScrollBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // EASYROUTINGMAIN_H
