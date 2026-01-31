#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Articol {
    string nume;
    int cantitate;
    double pretUnitar;
    string categorie;
};

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

bool validArticol(int cantitate, double pret) {
    if (cantitate <= 0) return false;
    if (pret < 0) return false;
    return true;
}

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
                addArticol(articole, nume, cantitate, pret, categorie);
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
                deleteByName(articole, nume);
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
                    cout << "Utilizare: list [sort=nume|pret|categorie]\n";
                    continue;
                }
            }

            listArticole(articole, sortKey);
        }
        else {
            cout << "Comanda necunoscuta. Tasteaza 'help'.\n";
             }
        }
      
     return 0;
}












int main() {

	cout << "Lista de cumparaturi:\n";
	cout << "Studenta Stancioni Rebeca\n";







	return 0;
}