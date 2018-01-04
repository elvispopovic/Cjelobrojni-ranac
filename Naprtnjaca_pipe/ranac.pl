% Author: Elvis Popovic
% Date: 26.12.2017.

:- use_module(library(simplex)).

/* pretvara imena iz tekstualnog oblika u C-u u oznaku terma u prologu */
termi_list([X],LR) :- term_string(T,X), LR=[T].
termi_list([GX|RX],LR) :- termi_list(RX,LR1), term_string(T,GX), LR=[T|LR1].

/* stvaranje liste totalnog ogranièenja svih elemenata zajedno */
mul_list([X],[Y],LR) :- R = X*Y, LR=[R].
mul_list([GX|RX],[GY|RY],LR) :- mul_list(RX,RY,LR1), R = GX*GY, LR=[R|LR1].

/* stvaranje liste ogranicenja pojedinih elemenata */
ogranicenja_list([X],[Y],LR) :- LR=[([X]=<Y)].
ogranicenja_list([GX|RX],[GY|RY],LR) :- ogranicenja_list(RX,RY,LR1), LR=[([GX]=<GY)|LR1].

/* stvaranje liste cjelobrojnih parametara */
cjelobrojni_list([X],LR) :- LR = [integral(X)].
cjelobrojni_list([GX|RX],LR) :- cjelobrojni_list(RX,LR1), LR=[integral(GX)|LR1].

/* stvara listu rjesenja */
vrijednosti_lista(S,[X],LR) :- variable_value(S,X,V), LR=[V].
vrijednosti_lista(S,[GX|RX],LR) :- vrijednosti_lista(S,RX,LR1), variable_value(S,GX,V), LR=[V|LR1].

/* postavljanje ogranicenja za elemente u ruksaku kao i kapacitet ruksaka */
ranac_ogranicenja(Stanje,Velicine,Ogranicenja,Kapacitet,Varijable) :-
        mul_list(Velicine,Varijable,M),
        ogranicenja_list(Varijable,Ogranicenja,ListaOgranicenja),
        gen_state(PocetnoStanje),
        foldl(constraint,[(M=<Kapacitet)|ListaOgranicenja],PocetnoStanje,Stanje).

/* glavni predikat kojega treba pozvati */
ranac_integral(Stanje,Velicine,Ogranicenja,Kapacitet,Cijene,Varijable) :-
        cjelobrojni_list(Varijable,C),
        mul_list(Cijene,Varijable,M),
        ranac_ogranicenja(PocetnoStanje,Velicine,Ogranicenja,Kapacitet,Varijable),
        foldl(constraint,C,PocetnoStanje,ZavrsnoStanje),
        maximize(M, ZavrsnoStanje, Stanje). 

/* predikat za pozivanje iz stranog programa, konkretno C++ */          
ranac_pozivC(Velicine,Ogranicenja,Kapacitet,Cijene,ImenaVarijabli,Rjesenje) :-
        termi_list(ImenaVarijabli,Varijable),
        ranac_integral(S,Velicine,Ogranicenja,Kapacitet,Cijene,Varijable),
                vrijednosti_lista(S,Varijable,L), 
                                term_variables(Rjesenje,L).
                                /*writeln('Ispis iz prologa: '),write(Varijable),write('='),writeln(L).*/

/*upit: ranac_integral(S,[6,4,1],[4,7,29],29,[8,5,1],[x(1),x(2),x(3)]), variable_value(S, x(1), Kolicina_1), variable_value(S, x(2), Kolicina2), variable_value(S, x(3), Kolicina3). */
/*upit2: ranac_integral(S,[6,4,1,2],[4,7,29,14],29,[16,5,2,5],[x(1),x(2),x(3),x(4)]), variable_value(S, x(1), Kolicina_1), variable_value(S, x(2), Kolicina2), variable_value(S, x(3), Kolicina3),variable_value(S, x(4), Kolicina4). */