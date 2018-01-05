///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/dataview.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* m_menu1;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxDataViewListCtrl* tablica;
		wxDataViewColumn* kolona_id;
		wxDataViewColumn* kolona_naziv;
		wxDataViewColumn* kolona_velicina;
		wxDataViewColumn* kolicina_vrijednost;
		wxDataViewColumn* kolona_dostupno;
		wxDataViewColumn* kolona_ukljuceno;
		wxGrid* grUnos;
		wxButton* btnUnesi;
		wxButton* btnObrisi;
		wxPanel* m_panel1;
		wxButton* btnObrisiTablicu;
		wxButton* btnPostavka;
		wxStaticText* m_staticText1;
		wxTextCtrl* tcKapacitet;
		wxButton* btnIzracunaj;
		wxTextCtrl* tcRjesenje;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void ObrisiTablicu( wxCommandEvent& event ) { event.Skip(); }
		virtual void UnesiPoPostavci( wxCommandEvent& event ) { event.Skip(); }
		virtual void Izracunaj( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void SelectionChanged( wxDataViewEvent& event ) { event.Skip(); }
		virtual void Unesi( wxCommandEvent& event ) { event.Skip(); }
		virtual void Obrisi( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Cjelobrojni ranac"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrame();
	
};

#endif //__GUIFRAME_H__
