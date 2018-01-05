/***************************************************************
 * Name:      Naprtnjaca_grafickiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2018-01-03
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifndef NAPRTNJACA_GRAFICKIMAIN_H
#define NAPRTNJACA_GRAFICKIMAIN_H



#include "Naprtnjaca_grafickiApp.h"
#include "GUIFrame.h"


struct Element
{
    char imeVarijable[16];
    char naziv[16];
    double velicina;
    double vrijednost;
    long dostupno;
    int kolicina;
};

class Naprtnjaca_grafickiFrame: public GUIFrame
{
    public:
        Naprtnjaca_grafickiFrame(wxFrame *frame);
        ~Naprtnjaca_grafickiFrame();
    private:
        HANDLE hStdUlaz, hStdIzlaz, hCjevovodCitanje, hCjevovodPisanje;
        SECURITY_ATTRIBUTES sa;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        DWORD dwUpisano, dwProcitano, dwExitCode, dwDostupno;
        char medjuspremnik[2048];

        wxDataViewItem selektirano;

        virtual void OnActivate( wxActivateEvent& event );
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void SelectionChanged( wxDataViewEvent& event );

        virtual void Unesi( wxCommandEvent& event );
        virtual void Obrisi( wxCommandEvent& event );
        virtual void ObrisiTablicu( wxCommandEvent& event );
        virtual void UnesiPoPostavci( wxCommandEvent& event );
        virtual void Izracunaj( wxCommandEvent& event );

        virtual bool OcistiCjevovod();
        virtual void ParsirajRjesenje(wxString& rjesenje, std::vector<long>& vrijednosti);
        virtual void IspisiRjesenje(std::vector<Element> elementi, double kapacitet);
};

#endif // NAPRTNJACA_GRAFICKIMAIN_H
