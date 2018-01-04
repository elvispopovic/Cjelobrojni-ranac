#include <iostream>
#include <cstring>
#include <vector>
#include <locale>
#include <SWI-Prolog.h>

static char imePrologPrograma[]="ranac.pl";
using namespace std;

/* kompiliranje: swipl-ld -D_REENTRANT -mthread -o ranac.exe ranac.cpp ranac.pl */
/* primjer unosa 6;4;1;2|16;5;2;5|29 */
/* rezultat 4,0,1,2*/

int kreirajListu(term_t l, vector<double> vrijednosti)
{
	int i, povratna;
	term_t t = PL_new_term_ref();
	PL_put_nil(l);
	for(i=vrijednosti.size()-1; i>=0; i--)
	{
		povratna=PL_put_integer(t,vrijednosti[i]);
		povratna=PL_cons_list(l,t,l);
	}
	return povratna;
}

int kreirajImenaVarijabli(term_t l, int n)
{
	int povratna, i;
	char ime[8];
	term_t t = PL_new_term_ref();
	PL_put_nil(l);
	for(i=n; i>0; i--)
	{
		sprintf(ime,"x(%d)",i);
		povratna=PL_put_string_chars(t,ime);
		povratna=PL_cons_list(l,t,l);
	}
	return povratna;
}


void parsirajToken(string& token, vector<double>& vrijednosti)
{
	double v;
	int pos;
	vrijednosti.clear();
	while ((pos = token.find(';')) != string::npos)
	{
		v = atof(token.substr(0, pos).c_str());
		vrijednosti.push_back(v);
		token.erase(0, pos + 1);
	}
	v = atof(token.substr(0, pos).c_str());
	vrijednosti.push_back(v);
	token.erase(0, pos + 1);
}
void parsirajUnos(string& unos, vector< vector<double> >& parametri)
{
	string token;
	int pos;
	vector<double> vrijednosti;
	parametri.clear();
	while ((pos = unos.find('|')) != string::npos)
	{
		token = unos.substr(0, pos);
		parsirajToken(token,vrijednosti);
		parametri.push_back(vrijednosti);
		unos.erase(0, pos + 1);
	}
	token = unos.substr(0, pos);
	parsirajToken(token,vrijednosti);
	parametri.push_back(vrijednosti);
	
	if(parametri.size()!=3||parametri[2].size()==0) return;
	vrijednosti.clear();
	for(pos=0; pos<parametri[0].size(); pos++)
		if(parametri[0][pos]==0.0)
			vrijednosti.push_back(0.0);
		else
			vrijednosti.push_back(parametri[2][0]/parametri[0][pos]);
	parametri.push_back(vrijednosti);
}

int main(int argc, char **argv)
{
	vector< vector<double> > parametri;
	vector< vector<double> >::iterator it1;
	vector<double>::iterator it2;
	vector<int>::iterator it3;
	vector<int> rjesenje;
	
	string unos;
	bool petlja;
    char *av[] = {imePrologPrograma, NULL};
	functor_t varijable_functor;
	term_t h0, v0;
    int i,broj_vrijednosti,rval,r;
	
	locale mylocale("");
	cout.imbue(mylocale);

	
    if( ! PL_initialise(argc,argv))
    {
        cerr<<"Greska pri inicijalizaciji."<<endl;
        PL_halt(1);
		petlja=false;
    }
	else
		petlja=true;

	h0 = PL_new_term_refs(6);
	predicate_t ranac_predikat = PL_predicate("ranac_pozivC", 6, "ranac");
	
	while(petlja)
	{
		cin >> unos;
		
		if(!strcmp(unos.c_str(),"\\q")||!strcmp(unos.c_str(),"\\quit"))
			break;
		parsirajUnos(unos,parametri); 
		if(parametri.size()!=4) continue; //velicine, vrijednosti, kapacitet, ogranicenja
		broj_vrijednosti=parametri[0].size();
		if(broj_vrijednosti<2||parametri[1].size()!=broj_vrijednosti) continue;
		/*
		for(it1=parametri.begin(); it1!=parametri.end(); ++it1)
		{
			for(it2=it1->begin(); it2!=it1->end(); ++it2) cout << *it2 << ";";
			cout << endl;
		}
		*/
	
		fid_t frameId=PL_open_foreign_frame();
		rval=kreirajListu(h0,parametri[0]);
		rval=kreirajListu(h0+1,parametri[3]);
		rval=PL_put_integer(h0+2,parametri[2][0]);
		rval=kreirajListu(h0+3,parametri[1]);
		rval=kreirajImenaVarijabli(h0+4,parametri[0].size());
		
		varijable_functor = PL_new_functor(PL_new_atom("varijable"),broj_vrijednosti);
		v0 = PL_new_term_refs(broj_vrijednosti);
		for(i=0; i<broj_vrijednosti; i++)
			rval=PL_put_variable(v0+i);
		rval=PL_cons_functor_v(h0+5,varijable_functor,v0);

		qid_t query = PL_open_query(NULL, PL_Q_NORMAL, ranac_predikat, h0); 
		rval = PL_next_solution(query); 
		if(rval)
		{
			rjesenje.clear();
			rval = PL_get_functor(h0+5,&varijable_functor);
			rval = PL_unify_compound(v0,varijable_functor);
			for(i=0; i<broj_vrijednosti; i++)
			{
				rval=PL_get_integer(v0+i,&r);
				rjesenje.push_back(r);
			}
		}
		PL_close_query(query); 
		PL_discard_foreign_frame(frameId);
		for(it3=rjesenje.begin(); it3!=rjesenje.end(); ++it3)
			cout << *it3 << ";";
		cout << endl;
	
	}
	return 0;
}

