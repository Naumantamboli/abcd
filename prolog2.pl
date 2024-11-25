% Facts: Symptoms and corresponding diseases
symptom(fever).
symptom(cough).
symptom(sore_throat).
symptom(headache).
symptom(chills).
symptom(rash).
symptom(nausea).

% Rules: Disease diagnosis based on symptoms
disease(flu) :- symptom(fever), symptom(cough), symptom(sore_throat).
disease(cold) :- symptom(cough), symptom(sore_throat), \+ symptom(fever).
disease(chickenpox) :- symptom(rash), syKmptom(fever).
disease(malaria) :- symptom(fever), symptom(chills), symptom(nausea).
disease(migraine) :- symptom(headache), \+ symptom(fever).
