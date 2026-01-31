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
        else if (cmd == "exit") {
            cout << "La revedere!\n";
            break;
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