#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

//string generatePalindrome() {
//
//}

void display2DVector(vector<vector<char>> vec, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\'" << vec[i][j] << "\'" << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    string unencrypted, encrypted;
    int length;
    int linesQuantity;
    int key;
    vector<vector<char>> chars;

    fstream outputMessage, outputNums;
    outputMessage.open("../Wiadomoœæ bia³a/output-message.txt", ios::out);
    outputNums.open("../Wiadomoœæ bia³a/output-key.txt", ios::out);

    if (outputMessage.good() and outputNums.good()) {
        // get
        cout << "Podaj zdanie do zaszyfrowania: ";
        getline(cin, unencrypted);
        length = unencrypted.length();

        cout << "Podaj klucz (liczbe, ktorej kwadrat jest wiekszy lub rowny dlugosci wiadomosci): ";
        cin >> key;

        // generate k
        /*
        !
        */


        // encrypt
        for (int i = 0; i < key; i++) {
            vector<char> line(key);
            chars.push_back(line);
        }

        int index = 0;
        for (int i = 0; i < key; i++) {
            for (int j = 0; j < key; j++) {
                if (index < length) {
                    chars[i][j] = unencrypted[index++];
                }
                else {
                    chars[i][j] = '*';
                }
            }
        }
        display2DVector(chars, key);

        for (int i = 0; i < key; i++) {
            for (int j = 0; j < key; j++) {
                if (chars[j][i] != '*') {
                    encrypted += chars[j][i];
                }
            }
        }
        cout << endl << encrypted << endl;

        // to spaces & tabs
        linesQuantity = count(encrypted.begin(), encrypted.end(), ' ') + 1;
        outputMessage << linesQuantity << '\n';

        for (int i = 0; i < length; i++) {
            if (encrypted[i] >= 'a' and encrypted[i] <= 'z') {
                int spacesQuantity = (int)encrypted[i] - 96;
                string spaces = "";
                spaces.append(spacesQuantity, ' ');
                outputMessage << spaces << '\t';
            }
            else if (encrypted[i] == ' ') {
                outputMessage << '\n';
            }
            else {
                cout << "niedozwolony znak!";
                return -1;
            }
        }
    }
    else {
        cout << "Problem z plikami";
    }

    outputMessage.close();
    outputNums.close();
}