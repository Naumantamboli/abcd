% Facts for males
male(nauman).
male(jakir).
male(javid).
male(jamir).
male(sameer).
male(sajid).
male(rafiq).
male(naushad).
male(mahmud).
male(babu).
male(manik).
male(saud).
male(adnaan).
male(hammad).

% Facts for females
female(najma).
female(rubina).
female(rizwana).
female(farzin).
female(alfiya).
female(farhat).
female(fayza).
female(madiha).
female(sadiya).
female(tarannum).
female(dulhan).


% Parent relationships
parent(jakir, nauman).
parent(jakir, farhat).
parent(rubina, nauman).
parent(rubina, farhat).
parent(javid, alfiya).
parent(rizwana, alfiya).

% Husband-wife relationships
husband(jakir, rubina).
husband(javid, rizwana).
husband(mahmud, najma).
husband(babu, dulhan).


% Rules

wife(X, Y) :- husband(Y, X).

child(X ,Y) :- husband(Y, Z), parent(Z ,X).

father(X ,Y) :- male(X), 
