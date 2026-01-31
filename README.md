# Gestionare aplicatie lista de cumparaturi - C++

Aplicație de tip consolă pentru gestionarea unei liste de cumparaturi.
Permite adăugarea, ștergerea, afișarea, filtrarea și exportul articolelor, precum și calculul costului total și al subtotalurilor pe categorii.

## Autor

- **Nume:** Stancioni Rebeca Emanuela
- **Grupă:** informatica , anul 2, grupa 3.1
- **Email:** rebeca-emanuela.stancioni@student.upt.ro
- **An academic:** 2025–2026

## Descriere

Aplicația permite gestionarea unei liste de articole dintr-un magazin/aprozar.
Utilizatorul poate introduce articole cu nume, cantitate, preț unitar și categorie, le poate șterge după nume, le poate afișa sortate, poate filtra după categorie și poate exporta lista într-un fișier CSV.

Scopul aplicației este de a oferi o soluție simplă pentru organizarea și vizualizarea articolelor iar totodata a  costurilor asociate acestora.

## Tehnologii folosite

- **Limbaj:** C++ 
- **Biblioteci standard:** 
  - `<iostream>` pentru input/output
  - `<vector>` pentru stocarea articolelor
  - `<string>` pentru manipularea șirurilor de caractere
  - `<algorithm>` pentru sortare
  - `<fstream>` pentru operații cu fișiere
  - `<iomanip>` pentru formatarea output-ului
- **Tools:** Git, GitHub, Dockerfile 

## Cerințe sistem

- Compilator C++ cu suport C++17 (g++, clang, MSVC)
- Sistem de operare: Windows , IDE: Visual Studio
- Nu există dependențe externe

## Instalare

```bash
git clone https://github.com/username/proiect.git
 cd proiect

##Build

Compilare:
g++ program.cpp -o program

Rulare:
./program

În aplicație se pot introduce comenzile direct din consolă.

Pentru lista de comenzi: folosim comanda help

## Comenzi disponibile

add <nume> <cantitate> <pret> <categorie>

del <nume>

list

list sort=nume

list sort=pret

list sort=categorie

filter <categorie>

total

export <fisier.csv>

exit

## Exemple de utilizare și output așteptat

Exemplul 1 – Adăugare articole

> add paine 2 3.5 alimente
Articol adaugat.
> add lapte 1 4.2 alimente
Articol adaugat.

Exemplul 2 – Afișare listă sortată după nume

> list sort=nume
Nume           Cant      Pret        Categorie      Total
----------------------------------------------------------------
lapte          1         4.20        alimente       4.20
paine          2         3.50        alimente       7.00

Exemplul 3 – Filtrare după categorie

> filter alimente
Nume           Cant      Pret        Categorie      Total
----------------------------------------------------------------
lapte          1         4.20        alimente       4.20
paine          2         3.50        alimente       7.00

Exemplul 4 – Cost total și subtotaluri

> total
Total general: 11.20
Subtotaluri pe categorii: alimente: 11.20

Exemplul 5 – Export CSV

> export articole.csv
Export realizat in 'articole.csv'.


Fișierul articole.csv va conține:

nume,cantitate,pret,categorie
exemplu:
paine,2,3.50,alimente
lapte,1,4.20,alimente

Funcționalități implementate in codul nostru:

 **Adăugare articole cu validare date

 **Ștergere articole după nume

 **Listare articole cu sortare

 **Filtrare după categorie

 **Calcul total și subtotaluri pe categorii

 **Export în fișier CSV

 **Meniu de ajutor (help)

## Structura proiectului

project/
├── .github/
│   └── workflows/
│       └── build.yml  
├── Dockerfile     -configuratie Docker 
├── program.cpp    -codul sursa
├── README.md      -documentatia proiectului
├── .gitignore     -ignorare fisiere
├── csv/           -folder pentru fisiere csv exportate

## Decizii de design

^^Structura de date:

Pentru stocarea articolelor am folosit un vector<Articol>, deoarece:

-numărul de articole este relativ mic

-este ușor de parcurs și sortat

-este suficient pentru o aplicație de tip consolă

^^Sortarea articolelor:

Sortarea se realizează folosind std::sort cu funcții lambda pentru fiecare criteriu (nume, preț, categorie).
Această soluție este simplă și clară pentru nivelul proiectului.

^^Calculul subtotalurilor

Subtotalurile pe categorii sunt calculate folosind două vectori simpli(unul pentru categorii și unul pentru sume), fără a folosi structuri mai avansate,
pentru a păstra codul ușor de înțeles.

## Probleme întâlnite și soluții

PROBLEMA: validarea datelor introduse de utilizator.
SOLUTIE: a fost creată o funcție separată care verifică dacă prețul este negativ și dacă
cantitatea este mai mică sau egală cu zero.

PROBLEMA: afișarea sortată fără a modifica lista originală.
SOLUTIE: s-a lucrat pe o copie a vectorului de articole înainte de sortare.

## Testare

Testarea s-a realizat manual, prin rularea aplicației și verificarea următoarelor cazuri:

**adăugare articole valide

**introducerea unei cantități zero sau a unui preț negativ

**ștergerea unui articol inexistent

**listarea cu fiecare tip de sortare

**filtrarea după o categorie inexistentă

**exportul într-un fișier CSV

## Export CSV

Comanda pentru export:
- `export <fisier.csv>`

Fișierele CSV se salvează în folderul proiectului.
Pentru organizare, folosim folderul `csv/`.

Exemplu:
- `export csv/articole.csv`

## Rulare rapidă cu Docker

Aplicația poate fi rulată rapid folosind Docker, fără a fi necesară compilarea locală.

### Comandă de rulare:

```bash
docker run -it rebecaema/lista_cumparaturi

Docker image published via GitHub Actions.

## Resurse folosite

https://en.cppreference.com

https://cplusplus.com

## Licență

Proiect educațional realizat pentru facultate.

## Contact

Pentru întrebări: 
email: rebeca-emanuela.stancioni@student.upt.ro

Multumesc!
