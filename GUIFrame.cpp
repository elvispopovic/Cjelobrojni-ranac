///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Izađi") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	m_menu1 = new wxMenu();
	wxMenuItem* m_menu1Item = new wxMenuItem( fileMenu, wxID_ANY, wxT("Tablica"), wxEmptyString, wxITEM_NORMAL, m_menu1 );
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("&Obriši") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem4 );
	
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("&Po postavci") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem5 );
	
	fileMenu->Append( m_menu1Item );
	
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Iz&računaj") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( m_menuItem6 );
	
	mbar->Append( fileMenu, wxT("&Datoteka") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&O programu") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Pomoć") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	tablica = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES );
	tablica->SetFont( wxFont( 11, 74, 93, 90, false, wxT("Arial") ) );
	
	kolona_id = tablica->AppendTextColumn( wxT("Var") );
	kolona_naziv = tablica->AppendTextColumn( wxT("Naziv") );
	kolona_velicina = tablica->AppendTextColumn( wxT("Veličina") );
	kolicina_vrijednost = tablica->AppendTextColumn( wxT("Vrijednost") );
	kolona_dostupno = tablica->AppendTextColumn( wxT("Dostupno") );
	kolona_ukljuceno = tablica->AppendToggleColumn( wxT("Odabir") );
	bSizer2->Add( tablica, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer3->SetMinSize( wxSize( -1,80 ) ); 
	grUnos = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	
	// Grid
	grUnos->CreateGrid( 1, 4 );
	grUnos->EnableEditing( true );
	grUnos->EnableGridLines( true );
	grUnos->EnableDragGridSize( false );
	grUnos->SetMargins( 0, 0 );
	
	// Columns
	grUnos->EnableDragColMove( false );
	grUnos->EnableDragColSize( true );
	grUnos->SetColLabelSize( 30 );
	grUnos->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grUnos->SetRowSize( 0, 30 );
	grUnos->EnableDragRowSize( true );
	grUnos->SetRowLabelSize( 0 );
	grUnos->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	grUnos->SetLabelFont( wxFont( 11, 70, 93, 90, false, wxT("Arial") ) );
	
	// Cell Defaults
	grUnos->SetDefaultCellFont( wxFont( 11, 74, 90, 90, false, wxT("Arial") ) );
	grUnos->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grUnos->SetFont( wxFont( 16, 74, 90, 90, false, wxT("Arial") ) );
	grUnos->SetMinSize( wxSize( -1,80 ) );
	
	bSizer3->Add( grUnos, 1, wxEXPAND|wxLEFT, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	btnUnesi = new wxButton( this, wxID_ANY, wxT("Unesi"), wxDefaultPosition, wxDefaultSize, 0 );
	btnUnesi->SetToolTip( wxT("unos odnosno editiranje retka u tablici") );
	
	bSizer4->Add( btnUnesi, 0, wxALL, 5 );
	
	btnObrisi = new wxButton( this, wxID_ANY, wxT("Obriši"), wxDefaultPosition, wxDefaultSize, 0 );
	btnObrisi->SetToolTip( wxT("brisanje retka u tablici") );
	
	bSizer4->Add( btnObrisi, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 2, wxEXPAND, 5 );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 200,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Upravljanje elementima") ), wxVERTICAL );
	
	btnObrisiTablicu = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Obriši tablicu"), wxDefaultPosition, wxDefaultSize, 0 );
	btnObrisiTablicu->SetToolTip( wxT("brisanje sadržaja tablice") );
	
	sbSizer1->Add( btnObrisiTablicu, 0, wxALL|wxEXPAND, 5 );
	
	btnPostavka = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Po postavci"), wxDefaultPosition, wxDefaultSize, 0 );
	btnPostavka->SetToolTip( wxT("Unesi u tablicu elemente po postavci") );
	
	sbSizer1->Add( btnPostavka, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Kapacitet ranca"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	sbSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	tcKapacitet = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("29"), wxDefaultPosition, wxDefaultSize, 0 );
	tcKapacitet->SetFont( wxFont( 12, 74, 90, 92, false, wxT("Arial Black") ) );
	tcKapacitet->SetForegroundColour( wxColour( 255, 128, 64 ) );
	tcKapacitet->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	sbSizer1->Add( tcKapacitet, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	btnIzracunaj = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Izračunaj"), wxDefaultPosition, wxDefaultSize, 0 );
	btnIzracunaj->SetToolTip( wxT("izračunava se rješenje problema cjelobrojnog ranca") );
	
	sbSizer1->Add( btnIzracunaj, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );
	
	
	bSizer9->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Rješenje") ), wxVERTICAL );
	
	tcRjesenje = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	tcRjesenje->SetFont( wxFont( 11, 74, 90, 92, false, wxT("Arial") ) );
	tcRjesenje->SetForegroundColour( wxColour( 255, 128, 64 ) );
	tcRjesenje->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	sbSizer4->Add( tcRjesenje, 1, wxEXPAND|wxTOP, 5 );
	
	
	bSizer9->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer9 );
	m_panel1->Layout();
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 1 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( GUIFrame::OnActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::ObrisiTablicu ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UnesiPoPostavci ) );
	this->Connect( m_menuItem6->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::Izracunaj ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Connect( wxID_ANY, wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIFrame::SelectionChanged ) );
	btnUnesi->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Unesi ), NULL, this );
	btnObrisi->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Obrisi ), NULL, this );
	btnObrisiTablicu->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ObrisiTablicu ), NULL, this );
	btnPostavka->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UnesiPoPostavci ), NULL, this );
	btnIzracunaj->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Izracunaj ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( GUIFrame::OnActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::ObrisiTablicu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UnesiPoPostavci ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::Izracunaj ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, wxDataViewEventHandler( GUIFrame::SelectionChanged ) );
	btnUnesi->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Unesi ), NULL, this );
	btnObrisi->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Obrisi ), NULL, this );
	btnObrisiTablicu->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ObrisiTablicu ), NULL, this );
	btnPostavka->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UnesiPoPostavci ), NULL, this );
	btnIzracunaj->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Izracunaj ), NULL, this );
	
}
