#include <iostream>
#include <SWI-Prolog.h>

static char imePrologPrograma[]="ranac.pl";
using namespace std;

/* kompiliranje: swipl-ld -D_REENTRANT -mthread -o ranac.exe ranac.cpp ranac.pl */

int kreirajListu(term_t l, int *vrijednosti, int n)
{
	int i, povratna;
	term_t t = PL_new_term_ref();
	PL_put_nil(l);
	for(i=n-1; i>=0; i--)
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

void ispisiListu(term_t l, int n)
{
	int i;
	int vrijednost, povratna;
	term_t t = PL_new_term_ref();
	for(i=0; i<n; i++)
	{
		povratna=PL_get_list(l,t,l);
		povratna=PL_get_integer(t,&vrijednost);
		cout << vrijednost << endl;
	}
}

int main(int argc, char **argv)
{
	/* privremeno */
	static int velicine[]={6,4,1,2};
	static int cijene[]={100,5,2,5};
	static int kapacitet = 29;
	static int ogranicenja[4];	
	static int rjesenje[4];
	/* kraj */
    char *av[] = {imePrologPrograma, NULL};
	functor_t varijable_functor;
	term_t h0, v0;
    int i,rval;
    if( ! PL_initialise(argc,argv))
    {
        cout<<"Greska pri inicijalizaciji."<<endl;
        PL_halt(1);
    }
	else
    {
        cout << "Prolog je uspjesno inicijaliziran." << endl;
    }
	h0 = PL_new_term_refs(6);
	predicate_t ranac_predikat = PL_predicate("ranac_pozivC", 6, "ranac");
	
	
	for(i=0; i<4; i++)
		ogranicenja[i]=kapacitet/velicine[i];
	rval=kreirajListu(h0,velicine,4);
	rval=kreirajListu(h0+1,ogranicenja,4);
	rval=PL_put_integer(h0+2,kapacitet);
	rval=kreirajListu(h0+3,cijene,4);
	rval=kreirajImenaVarijabli(h0+4,4);
	
	varijable_functor = PL_new_functor(PL_new_atom("varijable"),4);
	v0 = PL_new_term_refs(4);
	for(i=0; i<4; i++)
		rval=PL_put_variable(v0+i);
	rval=PL_cons_functor_v(h0+5,varijable_functor,v0);

	qid_t query = PL_open_query(NULL, PL_Q_NORMAL, ranac_predikat, h0); 
	rval = PL_next_solution(query); 
	if(rval)
	{
		rval = PL_get_functor(h0+5,&varijable_functor);
		rval = PL_unify_compound(v0,varijable_functor);
		cout << "Ispis iz C++ programa:" << endl;
		for(i=0; i<4; i++)
		{
			rval=PL_get_integer(v0+i,rjesenje+i);
			cout << "x(" << i << ") = " << rjesenje[i] << ", ";
		}
		cout << endl;
	}
	PL_close_query(query); 
	
	
	return 0;
}

