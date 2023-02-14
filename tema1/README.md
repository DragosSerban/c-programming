Task 1:
- Am folosit o functie pentru a transforma numarul decimal primit de la tastatura in binar.
- Initializam N = 0 si cu ajutorul operatiei "sau" pe biti gasim valoarea lui N, reprezentata de cei mai semnificativi biti ai numarului + 1.
- Convertim cele N grupuri de cate 2 biti in N operatori.
- Initializam dim = 0 si cu ajutorul operatiei "sau" pe biti gasim valoarea lui dim, reprezentata de cei mai putini semnificativi biti ai numarului + 1.

Task 2:
- Am realizat un vector de operanzi in care am asociat fiecarui operator pe rand cate o valoare de la 0 la 3 (0 - suma, 1 - diferenta, 2 - produs, 3 - raport).
- Calculam cate numere trebuie citite de la tastatura prin formulele date, urmand se le citim.
- Luam pe rand fiecare numar citit si ii asociem un vector care reprezinta scrierea acestuia pe biti, cu ajutorul functiei utilizate si la Task 1.
- Urmeazaza descompunerea numerelor in mai multe numere mai mici incluse in vectorul operand[i].
- Variabila count este folosita pentru a se adauga dim de fiecare data cand din cadrul numarului actual s-a format cate un numar mai mic.
- Daca j diferit de count, atunci se formeaza prin operatii pe biti si cu ajutorul variabilei pozitieBit primul operand.
- Daca j este egal cu count, asta inseamna ca formarea primului operand s-a finalizat, trecem la urmatorul (pozitieBit devine din nou dim-1, se scade 1 din j - pentru ca la incrementarea cu 1 din "for", j sa ramana egal cu ceea ce a fost inainte de incrementare, count devine count +dim, iar indexul creste - urmatorul operand va fi scris pe o pozitie mai mare in vector).
- index devine index+1 la final, deoarece, j fiind luat de la 0 la dimBytesShort*8, neinclusiv, acesta nu devine niciodata 16. Daca nu scriem la final "index += 1;" programul nu va stii sa treaca la un nou element al vectorului operand[i], asa ca atunci cand se trece la urmatorul numar, primul operand reesit din acesta va fi rescris in locul ultimului operand al numarului precedent.
- Prin variabila "rezultat" vom ajunge la rezultatul final, folosindu-ne de vectorul de operanzi si cel de operatori.

Task 4:
- Luam de la 0 la k fiecare operator si verificam prima oara daca elementul din vector reprezinta "inmultit" sau "impartit", si daca da, atunci se realizeaza operatia resprectiva intre operand[i] si operand[i+1] si se scrie in elementul operand[i+1], urmand ca mai apoi sa se stearga elementele operand[i] si operator[i], iar elementele urmatoare din vectori sa coboare cu cate o pozitie.
-Acelasi procedeu se repeta cu operatiile de "adunare" si "scadere".