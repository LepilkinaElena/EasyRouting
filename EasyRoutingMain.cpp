/***************************************************************
 * Name:      EasyRoutingMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Dmitry Zykov (dmz64@yandex.ru)
 * Created:   2016-04-03
 * Copyright: Dmitry Zykov (eltech.ru)
 * License:
 **************************************************************/

#include "EasyRoutingMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(EasyRoutingFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(EasyRoutingFrame)
const long EasyRoutingFrame::ID_STATICTEXT4 = wxNewId();
const long EasyRoutingFrame::ID_SCROLLBAR1 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT1 = wxNewId();
const long EasyRoutingFrame::ID_SPINCTRL3 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT2 = wxNewId();
const long EasyRoutingFrame::ID_SPINCTRL1 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT3 = wxNewId();
const long EasyRoutingFrame::ID_SPINCTRL2 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT7 = wxNewId();
const long EasyRoutingFrame::ID_SPINCTRL4 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT5 = wxNewId();
const long EasyRoutingFrame::ID_COMBOBOX1 = wxNewId();
const long EasyRoutingFrame::ID_STATICTEXT6 = wxNewId();
const long EasyRoutingFrame::ID_COMBOBOX2 = wxNewId();
const long EasyRoutingFrame::ID_BUTTON1 = wxNewId();
const long EasyRoutingFrame::ID_BUTTON2 = wxNewId();
const long EasyRoutingFrame::ID_MENUITEM1 = wxNewId();
const long EasyRoutingFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EasyRoutingFrame,wxFrame)
    //(*EventTable(EasyRoutingFrame)
    //*)
END_EVENT_TABLE()

EasyRoutingFrame::EasyRoutingFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EasyRoutingFrame)
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxFlexGridSizer* FlexGridSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer8;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxGridBagSizer* GridBagSizer2;
    wxBoxSizer* BoxSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, wxID_ANY, _("EasyRouting"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Карта"));
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    GridBagSizer2->Add(641,514,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Масштаб карты:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer6->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ScrollBar1 = new wxScrollBar(this, ID_SCROLLBAR1, wxDefaultPosition, wxSize(236,24), 0, wxDefaultValidator, _T("ID_SCROLLBAR1"));
    ScrollBar1->SetScrollbar(0, 1, 10, 1);
    BoxSizer6->Add(ScrollBar1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer2->Add(BoxSizer6, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxSHAPED, 5);
    StaticBoxSizer2->Add(GridBagSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxSHAPED, 5);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Маршруты"));
    StaticBoxSizer3->Add(480,302,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Параметры"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Количество человек:"), wxDefaultPosition, wxSize(100,21), 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl3 = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL3"));
    SpinCtrl3->SetValue(_T("0"));
    BoxSizer3->Add(SpinCtrl3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 1);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Ограничение по стоимости:"), wxDefaultPosition, wxSize(53,21), 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL1"));
    SpinCtrl1->SetValue(_T("0"));
    BoxSizer4->Add(SpinCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer4, 1, wxALL|wxEXPAND, 1);
    FlexGridSizer2 = new wxFlexGridSizer(1, 4, 0, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Ограничение по часам:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL2"));
    SpinCtrl2->SetValue(_T("0"));
    FlexGridSizer2->Add(SpinCtrl2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("минутам:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer2->Add(StaticText7, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl4 = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL4"));
    SpinCtrl4->SetValue(_T("0"));
    FlexGridSizer2->Add(SpinCtrl4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 1);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Интересы:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer7->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    BoxSizer7->Add(ComboBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer7, 1, wxALL|wxEXPAND, 1);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Предпочитаемый транспорт:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer8->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    BoxSizer8->Add(ComboBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer8, 1, wxALL|wxEXPAND, 1);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    Button1 = new wxButton(this, ID_BUTTON1, _("Поиск маршрутов"), wxDefaultPosition, wxSize(129,35), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetFocus();
    FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    Button2 = new wxButton(this, ID_BUTTON2, _("Очистить"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxSHAPED, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, ID_MENUITEM1, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EasyRoutingFrame::OnAbout);
    //*)
}

EasyRoutingFrame::~EasyRoutingFrame()
{
    //(*Destroy(EasyRoutingFrame)
    //*)
}

void EasyRoutingFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EasyRoutingFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
