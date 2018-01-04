% Author:
% Date: 26.12.2017.

:- use_module(library(simplex)).

mul_list([X],[Y],LR) :- R = X*Y, LR=[R].
mul_list([GX|RX],[GY|RY],LR) :- mul_list(RX,RY,LR1), R = GX*GY, LR=[R|LR1].

ogranicenja_list([X],[Y],LR) :- LR=[([X]=<Y)].
ogranicenja_list([GX|RX],[GY|RY],LR) :- ogranicenja_list(RX,RY,LR1), LR=[([GX]=<GY)|LR1].

cjelobrojni_list([X],LR) :- LR = [integral(X)].
cjelobrojni_list([GX|RX],LR) :- cjelobrojni_list(RX,LR1), LR=[integral(GX)|LR1].

ranac_ogranicenja(Stanje,Velicine,Ogranicenja,Kapacitet,Varijable) :-
        mul_list(Velicine,Varijable,M),
        ogranicenja_list(Varijable,Ogranicenja,ListaOgranicenja),
        gen_state(PocetnoStanje),
        foldl(constraint,[(M=<Kapacitet)|ListaOgranicenja],PocetnoStanje,Stanje).

ranac_integral(Stanje,Velicine,Ogranicenja,Kapacitet,Cijene,Varijable) :-
        cjelobrojni_list(Varijable,C),
        mul_list(Cijene,Varijable,M),
        ranac_ogranicenja(PocetnoStanje,Velicine,Ogranicenja,Kapacitet,Varijable),
        foldl(constraint,C,PocetnoStanje,ZavrsnoStanje),
        maximize(M, ZavrsnoStanje, Stanje).  /* cijene */

/*upit: ranac_integral(S,[6,4,1],[4,7,29],29,[8,5,1],[x(1),x(2),x(3)]), variable_value(S, x(1), Kolicina_1), variable_value(S, x(2), Kolicina2), variable_value(S, x(3), Kolicina3). */