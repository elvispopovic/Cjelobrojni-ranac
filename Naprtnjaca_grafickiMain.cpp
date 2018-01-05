/***************************************************************
 * Name:      Naprtnjaca_grafickiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2018-01-03
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Naprtnjaca_grafickiMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

using namespace std;

Element postavka[] = {{"x(1)","Element 1",6,16,3},{"x(2)","Element 2",4,5,10},{"x(3)","Element 3",1,2,4},{"x(4)","Element 4",2,5,10}};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
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


Naprtnjaca_grafickiFrame::Naprtnjaca_grafickiFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(wxT("Cjelobrojni ranac - Logičko programiranje"), 0);
    statusBar->SetStatusText(wxString::Format(wxT("SWI-prolog + TDM64-GCC MinGW 5.1.0-2 + %s"),wxbuildinfo(short_f)),1);
#endif
    grUnos->SetColumnWidth(0,300);
    grUnos->SetColLabelValue(0,wxString(wxT("Naziv")));
    grUnos->SetColLabelValue(1,wxString(wxT("Veličina")));
    grUnos->SetColLabelValue(2,wxString(wxT("Vrijednost")));
    grUnos->SetColLabelValue(3,wxString(wxT("Dostupno")));
    btnObrisi->Enable(false);


    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = true;
    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = true;

    if (!CreatePipe(&hStdUlaz,&hCjevovodPisanje,&sa,0))
    {
        wxMessageBox(wxT("Ne mogu pokrenuti cjevovod za slanje."),"Upozorenje!", MB_ICONEXCLAMATION);
        return;
    }
    if (!CreatePipe(&hCjevovodCitanje,&hStdIzlaz,&sa,0))
    {
        wxMessageBox(wxT("Ne mogu pokrenuti cjevovod za primanje."),"Upozorenje!", MB_ICONEXCLAMATION);
        CloseHandle(hStdUlaz);
        CloseHandle(hCjevovodPisanje);
        return;
    }

    ZeroMemory( &si, sizeof(si) );
    GetStartupInfo(&si);
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdOutput = hStdIzlaz;
    si.hStdError = hStdIzlaz;
    si.hStdInput = hStdUlaz;
    ZeroMemory( &pi, sizeof(pi) );
    if(!CreateProcess(L".\\ranac_pipe.exe",NULL,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi))
    {
        wxMessageBox(wxT("Ne mogu pokrenuti proces prologa."),"Upozorenje!", MB_ICONEXCLAMATION);
        CloseHandle(hStdUlaz);
        CloseHandle(hStdIzlaz);
        CloseHandle(hCjevovodPisanje);
        CloseHandle(hCjevovodCitanje);
        return;
    }

    ZeroMemory(medjuspremnik,127);
    if(OcistiCjevovod()==false)
        Destroy();
}

Naprtnjaca_grafickiFrame::~Naprtnjaca_grafickiFrame()
{


}

void Naprtnjaca_grafickiFrame::OnActivate( wxActivateEvent& event )
{


}

void Naprtnjaca_grafickiFrame::OnClose(wxCloseEvent &event)
{
    wxString upis="\\q\n";
    WriteFile(hCjevovodPisanje,upis,upis.size(),&dwUpisano,NULL);

    WaitForSingleObject( pi.hProcess, INFINITE );
    CloseHandle( pi.hProcess );
    CloseHandle(hStdUlaz);
    CloseHandle(hStdIzlaz);
    CloseHandle(hCjevovodPisanje);
    CloseHandle(hCjevovodCitanje);
    Destroy();
}

void Naprtnjaca_grafickiFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void Naprtnjaca_grafickiFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxString::Format(wxT("Autor: Elvis Popović\nProjekt za kolegij iz logičkog programiranja.\nSWI-prolog\n\\
TDM64-GCC MinGW 5.1.0-2\n%s"),wxbuildinfo(short_f));
    wxMessageBox(msg, wxT("Cjelobrojni ranac"));
}

void Naprtnjaca_grafickiFrame::SelectionChanged( wxDataViewEvent& event )
{
    int i,j;
    wxVariant value;
    if((j=tablica->GetSelectedRow())==wxNOT_FOUND)
    {
        btnUnesi->SetLabel("Unesi");
        btnObrisi->Enable(false);
        for(i=0; i<4; i++)
            grUnos->SetCellValue(0,i,"");
    }
    else
    {
        btnUnesi->SetLabel(wxT("Osvježi"));
        btnObrisi->Enable(true);
        for(i=1; i<5; i++)
        {
            tablica->GetValue(value,j,i);
            grUnos->SetCellValue(0,i-1,value);
        }
    }
}

void Naprtnjaca_grafickiFrame::Unesi( wxCommandEvent& event )
{
    int i,j;
    double v;
    wxVector<wxVariant> redak, redakUnosa;
    wxString upis;
    unsigned int brojRedaka = tablica->GetItemCount();

    redak.clear();
    upis = wxString::Format(wxT("x(%d)"), brojRedaka+1);
    redak.push_back(wxVariant(upis));
    upis=grUnos->GetCellValue(0,0);
    if(upis.empty())
        return;
    redak.push_back(wxVariant(upis));
    for(i=1; i<4; i++)
    {
        if(!grUnos->GetCellValue(0,i).ToDouble(&v)){ v=1.0; };
        redak.push_back(wxVariant(v));
    }
    redak.push_back(wxVariant(false));

    if((j=tablica->GetSelectedRow())==wxNOT_FOUND)
        tablica->AppendItem(redak);
    else
        for(i=1; i<5; i++)
            tablica->SetValue(wxVariant(redak[i]),j,i);
}

void Naprtnjaca_grafickiFrame::Obrisi( wxCommandEvent& event )
{
    int j,n;
    wxString upis;
    wxVector<wxVariant> varijable;
    if((j=tablica->GetSelectedRow())==wxNOT_FOUND) return;

    tablica->DeleteItem(j);
    if((n=tablica->GetItemCount())==0) return;
    for(j=0; j<n; j++)
    {
        upis = wxString::Format(wxT("x(%d)"), j+1);
        tablica->SetValue(wxVariant(upis),j,0);
    }
}

void Naprtnjaca_grafickiFrame::ObrisiTablicu( wxCommandEvent& event )
{
    int i;
    if(tablica->GetItemCount()==0) return;
    const int rezultat = MessageBox(NULL, L"Ovo će obrisati sve podatke u tablici elemenata.\nŽelite li nastaviti?",
                                    L"Brisanje tablice elemenata",  MB_YESNO | MB_ICONQUESTION);
    if(rezultat==IDNO)
        return;
    tablica->DeleteAllItems();
    for(i=0; i<4; i++)
        grUnos->SetCellValue(0,i,"");
}

void Naprtnjaca_grafickiFrame::UnesiPoPostavci( wxCommandEvent& event )
{
    int i;
    wxString upis;
    wxVector<wxVariant> redak;
    if(tablica->GetItemCount()>0)
    {
        const int rezultat = MessageBox(NULL, L"Tablica će se obrisati i upisat će se elementi po postavci.\nŽelite li nastaviti?",
                                    L"Upisivanje elemenata po postavci",  MB_YESNO | MB_ICONQUESTION);
        if(rezultat==IDNO)
            return;
    }
    tablica->DeleteAllItems();
    for(i=0; i<4; i++)
    {
        redak.clear();
        redak.push_back(wxVariant(postavka[i].imeVarijable));
        redak.push_back(wxVariant(postavka[i].naziv));
        redak.push_back(wxVariant(postavka[i].velicina));
        redak.push_back(wxVariant(postavka[i].vrijednost));
        redak.push_back(wxVariant(postavka[i].dostupno));
        redak.push_back(wxVariant(true));
        tablica->AppendItem(redak);
    }
}

void Naprtnjaca_grafickiFrame::Izracunaj( wxCommandEvent& event )
{
    int i, j,k, brojRedaka, brojIzabranih;
    bool odabir;
    wxVariant vari;
    wxString upis;
    double kapacitet;
    vector<Element> elementi;
    vector<Element>::iterator itElem;
    vector<long> rjesenje;
    vector<long>::iterator itRjesenje;

    if(!tcKapacitet->GetLineText(0).ToDouble(&kapacitet)) return;
    if(kapacitet<=0.0) return;
    if((brojRedaka=tablica->GetItemCount())==0) return;
    brojIzabranih=0;
    for(j=0; j<brojRedaka; j++)
    {
        tablica->GetValue(vari,j,5);
        if(vari)
        {
            brojIzabranih++;
            upis.clear();
            Element e;
            strcpy(e.imeVarijable,tablica->GetTextValue(j,0).c_str());
            strcpy(e.naziv,tablica->GetTextValue(j,1).c_str());
            tablica->GetTextValue(j,2).ToDouble(&(e.velicina));
            tablica->GetTextValue(j,3).ToDouble(&(e.vrijednost));
            tablica->GetTextValue(j,4).ToLong(&(e.dostupno));
            elementi.push_back(e);
        }
    }
    if(elementi.size()<1) return;

    /* pripremanje upita za prijenos preko cjevovoda */
    upis.clear();
    for(j=0; j<elementi.size(); j++)
        if(j<elementi.size()-1)
            upis+=wxString::Format("%lf;",elementi[j].velicina);
        else
            upis+=wxString::Format("%lf|",elementi[j].velicina);
    for(j=0; j<elementi.size(); j++)
        if(j<elementi.size()-1)
            upis+=wxString::Format("%lf;",elementi[j].vrijednost);
        else
            upis+=wxString::Format("%lf|",elementi[j].vrijednost);
    upis.Append(wxString::Format("%s|",tcKapacitet->GetLineText(0)));
    for(j=0; j<elementi.size(); j++)
        if(j<elementi.size()-1)
            upis+=wxString::Format("%d;",elementi[j].dostupno);
        else
            upis+=wxString::Format("%d\n",elementi[j].dostupno);

    if(OcistiCjevovod()==false)
        Destroy();

    ZeroMemory(medjuspremnik,2047);
    tcRjesenje->Clear();
    //tcRjesenje->AppendText(upis.c_str());
    /* slanje upisa */
    WriteFile(hCjevovodPisanje,upis.c_str(),upis.size(),&dwUpisano,NULL);
    /* cekanje da cjevovod odgovori */
    i=0;
    do
    {
        this_thread::sleep_for(chrono::milliseconds(40));
        PeekNamedPipe(hCjevovodCitanje,medjuspremnik,2047,&dwProcitano,&dwDostupno,NULL);
        GetExitCodeProcess(pi.hProcess,&dwExitCode);
        if (dwExitCode != STILL_ACTIVE)
            break;
        i++;
    }while(dwProcitano==0&&i<7);
    /* ako je proces ugasen javlja gresku i prekida aplikaciju */
    if (dwExitCode != STILL_ACTIVE)
    {
        wxMessageBox(wxT("Prolog proces više nije dostupan. Zatvaram grafičku aplikaciju."),"Upozorenje!", MB_ICONEXCLAMATION);
        Destroy();
    }
    ZeroMemory(medjuspremnik,2047);
    if(dwProcitano!=0)
    {
        ReadFile(hCjevovodCitanje,medjuspremnik,2047,&dwProcitano,NULL);
        tcRjesenje->AppendText(medjuspremnik);
        upis.Clear();
        upis.Append(medjuspremnik,dwProcitano);
        ParsirajRjesenje(upis,rjesenje);
        upis.Clear();
        for(itRjesenje=rjesenje.begin(),itElem=elementi.begin();itRjesenje!=rjesenje.end()&&itElem!=elementi.end();++itRjesenje,++itElem)
                itElem->kolicina=*itRjesenje;
        IspisiRjesenje(elementi,kapacitet);
    }
}

bool Naprtnjaca_grafickiFrame::OcistiCjevovod()
{
    do
    {
        this_thread::sleep_for(chrono::milliseconds(10));
        PeekNamedPipe(hCjevovodCitanje,medjuspremnik,2047,&dwProcitano,&dwDostupno,NULL);
        GetExitCodeProcess(pi.hProcess,&dwExitCode);
        if (dwExitCode != STILL_ACTIVE)
            return false;
        if(dwProcitano>0)
            ReadFile(hCjevovodCitanje,medjuspremnik,2047,&dwProcitano,NULL);
    }while(dwProcitano>0);
    return true;
}
void Naprtnjaca_grafickiFrame::ParsirajRjesenje(wxString& rjesenje, vector<long>& vrijednosti)
{
	long v;
	int pos;
	vrijednosti.clear();
	while ((pos = rjesenje.find(';')) != string::npos)
	{
		//v = atof(rjesenje.substr(0, pos).c_str());
		rjesenje.substr(0, pos).ToLong(&v);
		vrijednosti.push_back(v);
		rjesenje.erase(0, pos + 1);
	}
	//v = atof(rjesenje.substr(0, pos).c_str());
	rjesenje.substr(0, pos).ToLong(&v);
	vrijednosti.push_back(v);
	rjesenje.erase(0, pos + 1);
}
void Naprtnjaca_grafickiFrame::IspisiRjesenje(vector<Element> elementi, double kapacitet)
{
    wxString unos;
    int sumaKolicina=0;
    double sumaVrijednosti=0.0;
    vector<Element>::iterator it;
    unos+=wxString::Format(wxT("Količine u rancu:\n------------\n"));
    for(it=elementi.begin(); it!=elementi.end(); ++it)
    {
        unos+=wxString::Format("%s->%s=%d\n",it->naziv, it->imeVarijable, it->kolicina);
        sumaKolicina+=it->kolicina*it->velicina;
        sumaVrijednosti+=it->kolicina*it->vrijednost;
    }
    unos+=wxString::Format(wxT("------------\nUkupna vrijednost: %.2lf\n"),sumaVrijednosti);
    unos+=wxString::Format(wxT("Popunjenost ranca: %ld (%.2lf%%)\n"),sumaKolicina,sumaKolicina*100.0/kapacitet);
    tcRjesenje->AppendText(unos);
}


