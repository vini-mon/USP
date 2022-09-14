/* Facts */
male(edmar).	% male = genero masculino da familia %
male(vinicius).
male(dionisio).
male(cleiton).
female(leila).	% female = genero feminino da familia %
female(leiris).
female(madalena).

parentOf(edmar, vinicius).	% input1 é parente de input2 %
parentOf(edmar, leiris).
parentOf(leila, leiris).
parentOf(leila, vinicius).
parentOf(dionisio, edmar).
parentOf(dionisio, cleiton).
parentOf(madalena, edmar).
parentOf(madalena, cleiton).

/*
 * dionisio é pai de edmar e cleiton
 * madalena é mae de edmar e cleiton
 * edmar é pai de vinicius e leiris
 * leila é mae de vinicius e leiris
 * leiris é irma de vinicius
 * vinicius é irmao de leiris
 * */
 
/* Rules */

fatherOf(F, S):-	% F é pai de S, sendo que F deve ser masculino e F deve ser parente de S %
    male(F),	
    parentOf(F, S).

motherOf(M,S):-		% M é mãe de S, sendo que M deve ser feminino e M deve ser parente de S %
    female(M),
    parentOf(M, S).
 
sisterOf(X,Y):- 	% X é irmã de Y, sendo que X deve ser femino, X e Y devem ter o mesmo pai F e a mesma mae M %
    female(X),
    fatherOf(F, Y),
    fatherOf(F, X),
    motherOf(M, Y),
    motherOf(M, X),
    X \= Y.
 
brotherOf(X,Y):- 	% X é irmão de Y, sendo que X deve ser masculino, X e Y devem ter o mesmo pai F e a mesma mae M %
    male(X),
    fatherOf(F, Y),
    fatherOf(F, X),
    motherOf(M, Y),
    motherOf(M,X),X \= Y,
    X \= Y.