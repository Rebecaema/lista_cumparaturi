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