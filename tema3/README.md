Functia main:
Declaram instruction, adresa unde se afla instructiunea, alocam memorie
Declaram un pointer la o structura de tip Tbmp
Declaram un element de tip TPixel, ce contine Red, Green, Blue, de tip char
Se citeste instructiunea cu fgets si se elimina '\n'
Instructiunea se imparte in cuvinte cu strtok, se compara pe rand primul cuvant
Daca primim comanda "save", se creeaza fisierul de tip binar
Apelam functia writeBmp, in care se scrie fisierul binar dat ca parametru
La scrierea fisierului sunt folosite datele din structura bmp
Daca primim comanda "edit", deschidem fisierul si citim a datelor din fisier
Sunt citite elementele pozei, printre care si bitMap, eliminand paddingul
Daca primim comanda "insert", deschidem fisierul
Facem un pointer la o structura de tip Tbmp
Inseram poza la coordonatele date, verificand sa nu se scrie in zone nealocate
La final dezalocam memoria pentru poza inserata
Daca primim comanda "set", asignam valori pentru R, G, B din struct RGB
Daca primim comanda "line_width", grosimea liniei va fi stocata in variabila x
Daca primim comanda "draw", avem mai multe cazuri:
1. Cazul "draw line":
- primeste ca parametri coordonatele celor 2 puncte intre care se afla linia
- se apeleaza functia de desenare a liniei intre cele 2 puncte date
2. Cazul "draw rectangle":
- primeste coordonatele de stanga jos ale dreptunghiului, lungimea, latimea
- afla toate coordonatele dreptunghiului si apeleaza de 4 ori functia "draw"
3. Cazul "draw triangle":
- primeste coordonatele celor 3 colturi ale triunghiului
- apeleaza de 3 ori functia "draw", desenand astfel laturile triunghiului
Functia "draw":
- verifica daca distanta dintre x2 si x1 e mai mare decat cea dintre y2 si y1.
- daca este asa, atunci se verifica daca x1 e mai mare decat x2
- daca e adevarat, folosim functia "swap" pentru inversarea variabilelor
- calculam pentru elementele aflate intre x1 si x2 yCenter prin formula data
- bitMap-ul se modifica cu ajutorul functiei "insertDot"
- daca distanta dintre y2 si y1 e mai mare, atunci se actioneaza analog
Functia "insertDot":
- calculeaza elementul de stanga jos al punctului
- modifica celelalte elemente ale matricei x*x in functie de latimea x
- se verifica sa nu se iasa in afara spatiului alocat dinamic
Daca primim comanda "fill":
- se obtin cu strtok si atoi coordonatele punctului dat
- se creeaza o structura de tip TPixel (noua culoare)
- functia "fill" umple zona cu pixeli identici din jurul punctului dat
Functia "fill":
- functie recursiva
- umple punctul dat
- umple suprafata neintrerupta din jurul punctului ce are aceeasi culoare
Daca primim comanda "quit":
- utilizam functia deallocate pt a dezaloca memoria pt structura cu datele pozei
- se dezaloca si spatiul utilizat de instructiune
