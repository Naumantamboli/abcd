% Facts for males
male(bansilal).
male(bharatlal).
male(shalikram).
male(dilip).
male(sanjay).
male(pramod).
male(prakash).
male(sachin).
male(jitendra).  
male(vinod).
male(kapil).
male(rajesh).
male(rajkumar).
male(jayesh).
male(saurabh).
male(om).
male(shlok).
male(rohit).
male(satyam).
male(ishan).
male(pranit).
male(shaurya).
male(atharva).
male(lekraj).

% Facts for females
female(shobhabai).
female(meerabai).
female(rajshree).
female(kamlabai)
female(rampyaribai)
female(manisha).
female(rita).
female(pushpa).
female(jyoti).
female(ashwini).
female(priyanka).
female(namrata).
female(rachita).
female(nutan).
female(chaitali).
female(vaishnavi).
female(snehal).
female(pranjal).
female(pragati).
female(payal).
female(anushka).
female(bhakti).
female(prachi).
female(shagun).
female(ridhhima).

% Parent relationships
parent(bansilal, bharatlal).
parent(bansilal, shalikram).
parent(bansilal, rampyaribai).
parent(bansilal, kamlabai).
parent(bharatlal, sachin).
parent(bharatlal, jitendra).
parent(bharatlal, namrata).
parent(bhikulal, ashwini).
parent(bhikulal, nutan).
parent(bhikulal, rachita).
parent(bhikulal, kapil).
parent(shalikram, dilip).
parent(shalikram, sanjay).
parent(shalikram, pramod).
parent(shalikram, prakash).

parent(dilip, jayesh).
parent(dilip, vaishnavi).
parent(vinod, snehal).
parent(vinod, shlok).
parent(sanjay, saurabh).
parent(sanjay, rohit).
parent(pramod, pranjal).
parent(pramod, satyam).
parent(prakash, anushka).
parent(prakash, pragati).
parent(prakash, payal).
parent(sachin, om).
parent(sachin, bhakti).
parent(jitendra, ishan).
parent(jitendra, pranit). 

parent(kapil, lekraj).
parent(kapil, ridhhima).
parent(rajkumar, shagun).
parent(rajkumar, shaurya).
parent(rajesh, prachi).
parent(rajesh, atharva).

% Husband-wife relationships
husband(bharatlal, shobhabai).
husband(shalikram, meerabai).
husband(bhikulal, rajshree).
husband(dilip, manisha).
husband(sanjay, rita).
husband(pramod, pushpa).
husband(prakash, jyoti).
husband(sachin, ashwini).
husband(jitendra, priyanka).
husband(vinod, namrata).
husband(kapil, chaitali).
husband(rajkumar, nutan).
husband(rajesh, rachita).

% Rules
wife(X, Y) :- husband(Y, X).

child(X, Y) :- parent(Y, X).
child(X, Y) :- husband(Y, Z), parent(Z, X).
child(X, Y) :- wife(Y, Z), parent(Z, X).

father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- female(X), parent(W, Y), wife(X,W).

% Sibling and cousin rules
sibling(X, Y) :- (parent(Z, X), parent(Z, Y), X \= Y).
cousin(X, Y) :- parent(Z, X), parent(W, Y), sibling(Z, W).
scousin(X, Y) :- parent(Z, X), parent(W, Y), cousin(Z, W).

% Brother and sister rules with parentheses for or logic
maternal_brother(X, Y) :- 
    male(X),              
    mother(Z, X),
    parent(W,Y),
    (sibling(W,Z);cousin(W,Z)).
maternal_sister(X, Y) :- 
    female(X),              
    mother(Z, X),
    parent(W,Y),
    (sibling(W,Z);cousin(W,Z)).
brother(X, Y) :- male(X), (sibling(X, Y); cousin(X, Y); scousin(X, Y); maternal_brother(X, Y)).
sister(X, Y) :- female(X), (sibling(X, Y); cousin(X, Y); scousin(X, Y); maternal_sister(X, Y)).
% Grandparent and great-grandparent rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- male(X), parent(X, Z), parent(Z, Y).
grandmother(X, Y) :- female(X), parent(X, Z), parent(Z, Y).
grandchild(X,Y):- child(Z,Y),child(X,Z).
grandson(X,Y):- child(Z,Y),child(X,Z),male(X).
granddaughter(X,Y):- child(Z,Y),child(X,Z),female(X).

greatgrandfather(X, Y) :- male(X), parent(X, Z), parent(Z, W), parent(W, Y).
greatgrandmother(X, Y) :- female(X), parent(X, Z), parent(Z, W), parent(W, Y).

% Maternal relationships
maternal_grandparent(X, Y) :- parent(X, Z), mother(Z, Y).
maternal_grandfather(X, Y) :- male(X), parent(X, Z), mother(Z, Y).
maternal_grandmother(X, Y) :- female(X), parent(X, Z), mother(Z, Y).

% Maternal uncles and aunts
maternal_uncle(X, Y) :- male(X), sibling(X, Z), mother(Z, Y).
maternal_aunt(X, Y) :- female(X), sibling(X, Z), mother(Z, Y).
uncle(X,Y):- male(X),(cousin(X,W);sibling(X,W)),parent(W,Y).
aunt(X,Y):-female(X),(sibling(W,Z);cousin(W,Z)),parent(W,Y),wife(X,Z).
% Maternal cousins (cousins from the mother's side)
maternal_cousin(X, Y) :- parent(Z, X), sibling(Z, W), mother(W, Y).

% Maternal great-grandparents
maternal_greatgrandfather(X, Y) :- male(X), parent(X, Z), parent(Z, W), mother(W, Y).
maternal_greatgrandmother(X, Y) :- female(X), parent(X, Z), parent(Z, W), mother(W, Y).