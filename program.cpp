#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

// Structura care descrie un articol din lista de cumparaturi
// Contine numele produsului, cantitatea, pretul unitar si categoria

struct Articol {
    string nume;
    int cantitate;
    double pretUnitar;
    string categorie;
};

// Afiseaza toate comenzile disponibile pentru utilizator
// Este apelata cand utilizatorul scrie "help"

void printHelp() {
    cout << "Comenzi disponibile:\n";
    cout << "  help\n";
    cout << "  add <nume> <cantitate> <pret> <categorie>\n";
    cout << "  del <nume>\n";
    cout << "  list [sort=nume|pret|categorie]\n";
    cout << "  filter <categorie>\n";
    cout << "  total\n";
    cout << "  export <fisier.csv>\n";
    cout << "  exit\n";
}

// Verifica daca datele introduse pentru un articol sunt valide
// Cantitatea trebuie sa fie > 0
// Pretul trebuie sa fie >= 0

bool validArticol(int cantitate, double pret) {
    if (cantitate <= 0) return false;
    if (pret < 0) return false;
    return true;
}

// Adauga un articol nou in lista daca datele sunt valide
// Daca datele sunt gresite, afiseaza mesaj de eroare

void addArticol(vector<Articol>& articole, const string& nume, int cantitate, double pret, const string& categorie) {
    if (!validArticol(cantitate, pret)) {
        cout << "Date invalide! Cantitatea trebuie > 0, pretul >= 0.\n";
        return;
    }

    Articol a;
    a.nume = nume;
    a.cantitate = cantitate;
    a.pretUnitar = pret;
    a.categorie = categorie;

    articole.push_back(a);
    cout << "Articol adaugat.\n";
}

// Sterge toate articolele care au un anumit nume
// Foloseste remove_if pentru a elimina din vector

void deleteByName(vector<Articol>& articole, const string& nume) {
    auto oldSize = articole.size();
    articole.erase(
        remove_if(articole.begin(), articole.end(),
            [&](const Articol& a) { return a.nume == nume; }),
        articole.end()
    );

    if (articole.size() == oldSize) {
        cout << "Nu s-a gasit niciun articol cu numele '" << nume << "'.\n";
    }
    else {
        cout << "Articol(e) sters(e).\n";
    }
}

void printHeader() {
    cout << left << setw(15) << "Nume"
        << setw(10) << "Cant"
        << setw(12) << "Pret"
        << setw(15) << "Categorie"
        << setw(12) << "Total" << "\n";
    cout << string(64, '-') << "\n";
}

// Afiseaza articolele din lista
// Optional le poate sorta dupa nume, pret sau categorie

void listArticole(const vector<Articol>& articole, const string& sortKey) {
    vector<Articol> v = articole; // copie pentru sortare

    if (sortKey == "nume") {
        sort(v.begin(), v.end(), [](const Articol& a, const Articol& b) { return a.nume < b.nume; });
    }
    else if (sortKey == "pret") {
        sort(v.begin(), v.end(), [](const Articol& a, const Articol& b) { return a.pretUnitar < b.pretUnitar; });
    }
    else if (sortKey == "categorie") {
        sort(v.begin(), v.end(), [](const Articol& a, const Articol& b) { return a.categorie < b.categorie; });
    }

    if (v.empty()) {
        cout << "Lista este goala.\n";
        return;
    }

    printHeader();
    for (const auto& a : v) {
        double total = a.cantitate * a.pretUnitar;
        cout << left << setw(15) << a.nume
            << setw(10) << a.cantitate
            << setw(12) << fixed << setprecision(2) << a.pretUnitar
            << setw(15) << a.categorie
            << setw(12) << fixed << setprecision(2) << total
            << "\n";
    }
}

// Afiseaza doar articolele dintr-o anumita categorie

void filterByCategory(const vector<Articol>& articole, const string& categorie) {
    vector<Articol> filtered;
    for (const auto& a : articole) {
        if (a.categorie == categorie) filtered.push_back(a);
    }

    if (filtered.empty()) {
        cout << "Nu exista articole in categoria '" << categorie << "'.\n";
        return;
    }

    listArticole(filtered, "nume");   // le sortam dupa nume
}

// Calculeaza costul total al tuturor articolelor

void printTotals(const vector<Articol>& articole) {
    if (articole.empty()) {
        cout << "Lista este goala.\n";
        return;
    }

    double totalGeneral = 0.0;

    // pastram subtotal pe categorii 
    vector<string> categorii;
    vector<double> subtotaluri;

    for (const auto& a : articole) {
        double t = a.cantitate * a.pretUnitar;
        totalGeneral += t;

        // cauta categoria
        auto it = find(categorii.begin(), categorii.end(), a.categorie);
        if (it == categorii.end()) {
            categorii.push_back(a.categorie);
            subtotaluri.push_back(t);
        }
        else {
            int idx = (int)(it - categorii.begin());
            subtotaluri[idx] += t;
        }
    }

    cout << fixed << setprecision(2);
    cout << "Total general: " << totalGeneral << "\n";
    cout << "Subtotaluri pe categorii:\n";

    for (size_t i = 0; i < categorii.size(); i++) {
        cout << "  " << categorii[i] << ": " << subtotaluri[i] << "\n";
    }
}

// Exporta lista de articole intr-un fisier CSV

bool exportCSV(const vector<Articol>& articole, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) return false;

    out << "nume,cantitate,pret,categorie\n";
    out << fixed << setprecision(2);

    for (const auto& a : articole) {
        out << a.nume << ","
            << a.cantitate << ","
            << a.pretUnitar << ","
            << a.categorie << "\n";
    }

    out.close();
    return true;
}

// Functia principala a programului
// Citeste comenzi de la utilizator si le executa
// Programul ruleaza pana cand utilizatorul scrie "exit"

int main() {
    vector<Articol> articole;

    cout << "Gestionare articole (tasteaza 'help' pentru comenzi)\n";

    string line;
    while (true) {
        cout << "\n> ";
        getline(cin, line);

        if (line.empty()) continue;

        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "help") {
            printHelp();
        }
        else if (cmd == "add") {
            string nume, categorie;
            int cantitate;
            double pret;

            ss >> nume >> cantitate >> pret >> categorie;

            if (nume.empty() || categorie.empty() || ss.fail()) {
                cout << "Utilizare: add <nume> <cantitate> <pret> <categorie>\n";
            }
            else {
                addArticol(articole, nume, cantitate, pret, categorie);  //adauga un articol in lista
            }
        }
        else if (cmd == "exit") {
            cout << "La revedere!\n";
            break;
        }
        else if (cmd == "del") {
            string nume;
            ss >> nume;

            if (nume.empty()) {
                cout << "Utilizare: del <nume>\n";
            }
            else {
                deleteByName(articole, nume);        //sterge un articol din lista
            }
        }
        else if (cmd == "list") {
            string opt;
            ss >> opt;           // poate fi gol sau sort
            string sortKey = ""; // default: fara sortare

            if (!opt.empty()) {
                // asteptam format sort=ceva

                if (opt.rfind("sort=", 0) == 0) {
                    sortKey = opt.substr(5);
                }
                else {
                    cout << "Utilizare: list [sort=nume|pret|categorie]\n";     //afiseaza lista in functie de nume/pret/categorie
                    continue;
                }
            }

            listArticole(articole, sortKey);
        }
        else if (cmd == "filter") {
            string categorie;
            ss >> categorie;

            if (categorie.empty()) {
                cout << "Utilizare: filter <categorie>\n";                    //afiseaza lista dupa o anumita categorie
            }
            else {
                filterByCategory(articole, categorie);
            }
        }
        else if (cmd == "total") {
            printTotals(articole);                                           //calculeaza totalul 
        }
        else if (cmd == "export") {
            string filename;
            ss >> filename;

            if (filename.empty()) {
                cout << "Utilizare: export <fisier.csv>\n";                 //lista este exportata intr un fisier CSV
            }
            else {
                if (exportCSV(articole, filename)) {
                    cout << "Export realizat in '" << filename << "'.\n";
                }
                else {
                    cout << "Eroare la export. Verifica numele fisierului.\n";
                }
            }
        }
            else if (cmd == "exit") {
                    cout << "La revedere!\n";
                    break;
            }
            else {
                     cout << "Comanda necunoscuta. Tasteaza 'help' pentru lista de comenzi.\n";
            }
        }

       return 0;

    }
