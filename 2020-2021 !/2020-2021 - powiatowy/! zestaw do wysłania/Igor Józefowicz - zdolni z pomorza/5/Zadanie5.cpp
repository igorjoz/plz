#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

fstream inputFormula, inputFloors, output;

struct formula {
    // wspolne wlasciowosci
    char type;
    vector<int> possibleFloorsUp;
    vector<int> possibleFloorsDown;

    // dla typu 'W'
    string formula;
    int mpyConst;
    int addConst;
    int n;
    bool squaredN = false; // flaga, czy we wzorze jest n*n
    
    // dla typu 'D'
    int floorsQuantity;
};

formula f[2];

int floorsQuantity;

struct level {
    int floor;
    bool important = false; // flaga, korygowana przy wczytywaniu danych
    bool visited = false; // flaga
};

struct variants {
    string name;
    int issuesQuantity = 0;
};

variants v[4];

void analyzeVariant(int variantIndex, int ascIndex, int descIndex, level l[]) {

    // wjazd
    for (int i = 0; i < floorsQuantity; i++) {
        l[i].visited = false;

        for (int k = 0; k < f[ascIndex].possibleFloorsUp.size(); k++) {

            if ((l[i].floor == f[ascIndex].possibleFloorsUp[k] && l[i].important) ||
                (l[i].floor == f[ascIndex].possibleFloorsUp[k] && !(l[i].important) && count(f[descIndex].possibleFloorsDown.begin(), f[descIndex].possibleFloorsDown.end(), l[i].floor))) {

                l[i].visited = true;
                //cout << l[i].floor << " - " << f[ascIndex].possibleFloorsUp[k] << " znaleziono, ALE NIE; ";
                //cout << (l[i].floor == f[ascIndex].possibleFloorsUp[k] && !(l[i].important) && count(f[descIndex].possibleFloorsDown.begin(), f[descIndex].possibleFloorsDown.end(), l[i].floor));
                //cout << " " << count(f[ascIndex].possibleFloorsDown.begin(), f[ascIndex].possibleFloorsDown.end(), l[i].floor);
                //cout << endl;
                break;
            }
            else if (l[i].floor == f[ascIndex].possibleFloorsUp[k] && !(l[i].important)) {

                v[variantIndex].issuesQuantity++;
                //cout << l[i].floor << " - " << f[ascIndex].possibleFloorsUp[k] << " znaleziono robote do domu, razem: " << v[variantIndex].issuesQuantity << endl;
                break;
            }

        }
    }
    //cout << endl;

    // zjazd
    for (int i = 0; i < floorsQuantity; i++) {
        for (int k = 0; k < f[descIndex].possibleFloorsDown.size(); k++) {

            if (l[i].floor == f[descIndex].possibleFloorsDown[k] && !(l[i].visited)) {

                v[variantIndex].issuesQuantity++;
                //cout << l[i].floor << " - " << f[descIndex].possibleFloorsDown[k] << " znaleziono robote do domu, razem: " << v[variantIndex].issuesQuantity << endl;
                break;
            }

        }
    }
    //cout << endl << endl;
}

// main

int main()
{
    inputFormula.open("profesor.txt", ios::in);
    if (inputFormula.good()) {

        inputFloors.open("wozny.txt", ios::in);
        if (inputFloors.good()) {
            
            // typ wzoru
            for (int i = 0; i < 2; i++) {
                inputFormula >> f[i].type;
                //cout << f[i].type << " ";

                // wzór W
                if (f[i].type == 'W') {
                    inputFormula >> f[i].formula;
                    inputFormula >> f[i].n;
                    //cout << f[i].formula << " " << f[i].n << endl;

                    int formulaSize = f[i].formula.length();
                    int asteriksCounter = 0;

                    // multiplyConstant
                    if (f[i].formula[2] == '*') {
                        string temp = "";
                        temp += f[i].formula[0];
                        temp += f[i].formula[1];

                        f[i].mpyConst = stoi(temp);
                    }
                    else {
                        string temp = "";
                        temp += f[i].formula[0];

                        f[i].mpyConst = stoi(temp);
                    }
                    
                    // squared n
                    for (int k = 0; k < formulaSize; k++) {
                        if (f[i].formula[k] == '*') {
                            asteriksCounter++;
                        }
                    }
                    if (asteriksCounter == 2) {
                        f[i].squaredN = true;
                    }

                    // add Constant
                    if (f[i].formula[formulaSize - 3] == '+') {
                        string temp = "";
                        temp += f[i].formula[formulaSize - 2];
                        temp += f[i].formula[formulaSize - 1];

                        f[i].addConst = stoi(temp);
                    }
                    else {
                        string temp = "";
                        temp += f[i].formula[formulaSize - 1];

                        f[i].addConst = stoi(temp);
                    }

                    // wypisanie wzoru
                    if (f[i].squaredN) {
                        cout << f[i].type << " " << f[i].mpyConst << "*" << f[i].n << "*" << f[i].n << "+" << f[i].addConst;
                    }
                    else {
                        //cout << f[i].type << " " << f[i].mpyConst << "*" << f[i].n << "+" << f[i].addConst;
                    }
                    //cout << endl;

                    // mo¿liwe piêtra WJAZD i ZJAZD
                    for (int k = 1; k <= f[i].n; k++) {
                        int possibleFloor;
                        if (f[i].squaredN) {
                            possibleFloor = f[i].mpyConst * k * k + f[i].addConst;
                        }
                        else {
                            possibleFloor = f[i].mpyConst * k + f[i].addConst;
                        }

                        if (possibleFloor < 100) {
                            f[i].possibleFloorsUp.push_back(possibleFloor);
                            //cout << "@" << possibleFloor << " ";
                        }

                        if (101 - possibleFloor > 0 && 101 - possibleFloor < 100) {
                            f[i].possibleFloorsDown.push_back(101 - possibleFloor);
                            //cout << "&" << 101 - possibleFloor << " ";
                        }
                    }
                    //cout << endl;
                }

                // wzór D
                else {
                    inputFormula >> f[i].floorsQuantity;

                    for (int k = 0; k < f[i].floorsQuantity; k++) {
                        int temp;
                        inputFormula >> temp;
                        f[i].possibleFloorsUp.push_back(temp);
                        f[i].possibleFloorsDown.push_back(101 - temp);
                        //cout << "@" << temp << " " << "&" << 101 - temp << " ";
                    }
                }
                //cout << endl;
            }
            //cout << endl;

            // piêtra i sprawy
            inputFloors >> floorsQuantity;
            level* l = new level[floorsQuantity];

            for (int i = 0; i < floorsQuantity; i++) {
                inputFloors >> l[i].floor;

                char temp;
                inputFloors >> temp;

                if (temp == 'P') {
                    l[i].important = true;
                }

                //cout << l[i].floor << " " << l[i].important << "-" << temp << endl;
            }
            //cout << endl;


            // ---
            // analiza warinatów
            // ---

            // kolejnoœæ testowanych kombinacji:
            v[0].name = "WW";
            v[1].name = "DD";
            v[2].name = "DW";
            v[3].name = "WD";

            int wI; // wzor - W
            int dI; // dowolny - D

            if (f[0].type == 'W') {
                wI = 0;
                dI = 1;
            }
            else {
                wI = 1;
                dI = 0;
            }

            // WW - wjazd
            //cout << "WW:" << endl;
            analyzeVariant(0, wI, wI, l);

            // DD - wjazd
            //cout << "DD:" << endl;
            analyzeVariant(1, dI, dI, l);

            // DW
            //cout << "DW:" << endl;
            analyzeVariant(2, dI, wI, l);

            // WD - wjazd
            //cout << "WD:" << endl;
            analyzeVariant(3, wI, dI, l);

            output.open("dokumenty.txt", ios::out);
            if (output.good()) {
                int minIssues = 999;
                int minIssuesIndex;

                for (int i = 0; i < 4; i++) {
                    if (v[i].issuesQuantity < minIssues) {
                        minIssues = v[i].issuesQuantity;
                        minIssuesIndex = i;
                    }
                }

                cout << endl << v[minIssuesIndex].name << " " << v[minIssuesIndex].issuesQuantity << endl;

                output << v[minIssuesIndex].name << " " << v[minIssuesIndex].issuesQuantity;
            }
            else {
                cout << "Problem z otworzeniem pliku wyjsciowego \"dokumenty.txt\"";
            }

            output.close();
        }
        else {
            cout << "Problem z otworzeniem pliku wejsciowego \"wozny.txt\"";
        }

        inputFloors.close();
    }
    else {
        cout << "Problem z otworzeniem pliku wejsciowego \"profesor.txt\"";
    }

    inputFormula.close();
}

/*
zasady profesora:
1. piêtro i sprawa --> bierze
    nie piêtro i sprawa --> ignoruje (nawet jeœli PILNE)
2. oddaje PILNE sprawy --> zatrzymuje siê specjalnie na piêtrach przy POWROCIE (nawet jeœli ALGORYTM tego nie przewidywa³)
3. PILNA sprawa przy powrocie --> zabiera do domu
4. NIEPILNE --> zabiera do domu
    jeœli algorytm przewiduje odwiedzenie piêtra zarówno przy wjezdzie i zarówno przy zjezdzie, to wtedy ODDAJE NIEPILN¥

Inne:
1. nigdy nie ma wiêcej ni¿ jednej sprawy na piêtrze --> czyli na pewno nie trafi na to samo piêtro przy powrocie z czekaj¹c¹ now¹ spraw¹ (kiedy ju¿ odwiedzi³ to piêtro przy wjeŸdzie)
*/