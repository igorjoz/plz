#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

fstream accidentsFile, insurersAndAccidentsFile, policeAndAccidentsFile;
fstream insurersFile, policeFile, accidentsCompleteFile, accidentsDateFile;

const int INSURERS_QUANTITY = 6;
const int POLICE_QUANTITY = 8;
const int ACCIDENTS_QUANTITY = 60;

string insurersNames[INSURERS_QUANTITY];
string policeNames[POLICE_QUANTITY];

vector<vector<string>> insurersAndAccidents;
vector<vector<string>> policeAndAccidents;

struct accident {
    int ID;
    int insurer = 0; // podstawowa wartoœæ, jeœli nie mia³ ubezpieczyciela, to pozostaje
    int police;
    string date;
    int day;
    int month;
    int year;
    string licensePlate;
    int receivedMoney;
};

// accidents[0].ID == 1
accident accidents[ACCIDENTS_QUANTITY] = {};

string date;
int day, month, year;

string headersTab = "Nr\tData wypadku\tNr rejestracyjny\tWyplacone ubezpieczenie"; // tytu³y oddzielone tabami
string headersSpace = "Nr Data wypadku Nr rejestracyjny Wyplacone ubezpieczenie"; // tytu³y oddzielone spacjami


int main()
{
    // a), przygotowanie do c)
    // Zalacznik-Zadanie2-dane1.txt
    insurersAndAccidentsFile.open("Zalacznik-Zadanie2-dane1.txt", ios::in);
    if (insurersAndAccidentsFile.good()) {
        for (int i = 0; i < INSURERS_QUANTITY; i++) {
            string temp, line;
            insurersAndAccidentsFile >> insurersNames[i];
            //cout << insurersNames[i] << endl;
            insurersAndAccidentsFile >> temp;

            vector<string> lineAccidentsIDs;
            getline(insurersAndAccidentsFile, line);
            istringstream iss(line);
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(lineAccidentsIDs));
            insurersAndAccidents.push_back(lineAccidentsIDs);
        }
        
        for (int i = 0; i < INSURERS_QUANTITY; i++) {
            //cout << "(" << i + 1 << ")";
            for (int k = 0; k < insurersAndAccidents[i].size(); k++) {
                //cout << insurersAndAccidents[i][k] << " ";
                int accidentID = stoi(insurersAndAccidents[i][k]);
                accidents[accidentID - 1].insurer = i + 1;
            }
            //cout << endl;
        }

        insurersFile.open("ubezpieczyciele.txt", ios::out);
        if (insurersFile.good()) {
            insurersFile << "Idu Nazwa_ubezp" << endl;
            for (int i = 0; i < INSURERS_QUANTITY; i++) {
                insurersFile << i + 1 << " " << insurersNames[i] << endl;
            }
        }
        else {
            cout << "Problem z otworzeniem pliku \"ubezpieczyciele.txt\"";
        }
        insurersFile.close();
    }
    else {
        cout << "Problem z otworzeniem pliku \"Zalacznik-Zadanie2-dane1.txt\"";
    }
    insurersAndAccidentsFile.close();


    // b), przygotowanie do c)
    // Zalacznik-Zadanie2-dane2.txt
    policeAndAccidentsFile.open("Zalacznik-Zadanie2-dane2.txt", ios::in);
    if (policeAndAccidentsFile.good()) {
        for (int i = 0; i < POLICE_QUANTITY; i++) {
            string temp, line;
            policeAndAccidentsFile >> policeNames[i];
            //cout << policeNames[i] << endl;
            policeAndAccidentsFile >> temp;

            vector<string> lineAccidentsIDs;
            getline(policeAndAccidentsFile, line);
            istringstream iss(line);
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(lineAccidentsIDs));
            policeAndAccidents.push_back(lineAccidentsIDs);
        }

        for (int i = 0; i < POLICE_QUANTITY; i++) {
            //cout << "(" << i + 1 << ")";
            for (int k = 0; k < policeAndAccidents[i].size(); k++) {
                //cout << policeAndAccidents[i][k] << " ";
                int accidentID = stoi(policeAndAccidents[i][k]);
                //cout << "[" << accidentID << "]" << i + 1 << " ";
                accidents[accidentID - 1].police = i + 1;
                //cout << accidentPolice[accidentID];
            }
            //cout << endl;
        }

        policeFile.open("policja.txt", ios::out);
        if (policeFile.good()) {
            policeFile << "Idp Nazwisko" << endl;
            for (int i = 0; i < POLICE_QUANTITY; i++) {
                policeFile << i + 1 << " " << policeNames[i] << endl;
            }
        }
        else {
            cout << "Problem z otworzeniem pliku \"policja.txt\"";
        }
        policeFile.close();
    }
    else {
        cout << "Problem z otworzeniem pliku \"Zalacznik-Zadanie2-dane2.txt\"";
    }
    policeAndAccidentsFile.close();


    // c), d)
    // Zalacznik-Zadanie2-wypadki.txt
    accidentsFile.open("Zalacznik-Zadanie2-wypadki.txt", ios::in);
    if (accidentsFile.good()) {
        accidentsCompleteFile.open("wypadki-uzupelnione.txt", ios::out);

        if (accidentsCompleteFile.good()) {

            string line;
            getline(accidentsFile, line);

            headersTab += "\tNr_ubezp\tNr_polic";
            headersSpace += " Nr_ubezp Nr_polic";
            accidentsCompleteFile << headersSpace << endl;

            for (int i = 0; i < ACCIDENTS_QUANTITY; i++) {
                // c)
                string temp;

                accidentsFile >> temp;
                accidents[i].ID = stoi(temp);

                accidentsFile >> accidents[i].date;
                accidentsFile >> accidents[i].licensePlate;

                accidentsFile >> temp;
                accidents[i].receivedMoney = stoi(temp);

                accidentsCompleteFile << accidents[i].ID << " ";
                accidentsCompleteFile << accidents[i].date << " ";
                accidentsCompleteFile << accidents[i].licensePlate << " ";
                accidentsCompleteFile << accidents[i].receivedMoney << " ";

                accidentsCompleteFile << accidents[i].insurer << " ";
                accidentsCompleteFile << accidents[i].police << endl;

                // d)
                temp = accidents[i].date[0];
                temp += accidents[i].date[1];
                accidents[i].day = stoi(temp);

                temp = accidents[i].date[3];
                temp += accidents[i].date[4];
                accidents[i].month = stoi(temp);

                temp = accidents[i].date[6];
                temp += accidents[i].date[7];
                temp += accidents[i].date[8];
                temp += accidents[i].date[9];
                accidents[i].year = stoi(temp);

                //cout << accidents[i].date << " " << accidents[i].day << "-" << accidents[i].month << "-" << accidents[i].year << endl;
            }

        }
        else {
            cout << "Problem z otworzeniem pliku \"wypadki-uzupelnione.txt\"";
        }
        accidentsCompleteFile.close();
    }
    else {
        cout << "Problem z otworzeniem pliku \"Zalacznik-Zadanie2-wypadki.txt\"";
    }
    accidentsFile.close();

    // d)
    accidentsDateFile.open("wypadki-data.txt", ios::out);
    if (accidentsDateFile.good()) {
        cout << "Podaj date (format dd.mm.yyyy): ";
        cin >> date;

        string temp;

        temp = date[0];
        temp += date[1];
        day = stoi(temp);

        temp = date[3];
        temp += date[4];
        month = stoi(temp);

        temp = date[6];
        temp += date[7];
        temp += date[8];
        temp += date[9];
        year = stoi(temp);

        //cout << date << " " << day << "-" << month << "-" << year << endl;

        accidentsDateFile << headersTab << endl;
        for (int i = 0; i < ACCIDENTS_QUANTITY; i++) {

            if ((accidents[i].year > year) ||
                (accidents[i].year == year && accidents[i].month > month) ||
                (accidents[i].year == year && accidents[i].month == month && accidents[i].day > day)) {

                accidentsDateFile << accidents[i].ID << "\t";
                accidentsDateFile << accidents[i].date << "\t";
                accidentsDateFile << accidents[i].licensePlate << "\t";
                accidentsDateFile << accidents[i].receivedMoney << "\t";
                accidentsDateFile << accidents[i].insurer << "\t";
                accidentsDateFile << accidents[i].police << endl;
            }
        }
    }
    else {
        cout << "Problem z otworzeniem pliku \"wypadki-data.txt\"";
    }
}