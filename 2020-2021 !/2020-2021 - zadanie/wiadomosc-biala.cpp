#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


// 0 -> not palindrome at all; 1 -> exact palindrome; 2 -> approximate palindrome
int isExactOrApproximatePalindrome(string text, int errors = 1) {
    int length = text.length();
    int errorsCounter = 0;

    for (int i = 0; i < length / 2; i++) {
        if (text[i] != text[length - i - 1]) {
            errorsCounter++;
        }
        if (errorsCounter > errors) {
            return 0;
        }
    }

    if (errorsCounter == 0) {
        return 1;
    }
    else if (errorsCounter == errors) {
        return 2;
    }
}

void display2DVector(vector<vector<char>> vec, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\'" << vec[i][j] << "\'" << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

string decipherTransposition(string encrypted, int key) {
    int length = encrypted.length();
    int lackingToSquare = key * key - length;
    string answer = "";

    cout << "encrypted: \"" << encrypted << "\"" << endl;
    cout << "lacking to square: " << lackingToSquare << endl << endl;

    vector<vector<char>> chars;
    for (int i = 0; i < key; i++) {
        vector<char> line(key);
        chars.push_back(line);
    }

    int col = key - 1; // column index
    int line = key - 1; // line index
    int counter = 0;
    for (int i = 0; i < lackingToSquare; i++) {
        if (col == -1) {
            line--;
            col = key - 1;
            counter = 0;
        }

        chars[col--][line] = '*';
    }
    
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < key; j++) {
            if (index < length and chars[i][j] != '*') {
                chars[i][j] = encrypted[index++];
            }
        }
    }
    display2DVector(chars, key);

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < key; j++) {
            if (chars[j][i] != '*') {
                answer += chars[j][i];
            }
        }
    }

    return answer;
}


int main()
{
    fstream messageFile, keyFile, outputFile;
    messageFile.open("wiadomosc.txt", ios::in);
    keyFile.open("klucz.txt", ios::in);
    outputFile.open("wynik.txt", ios::out);

    int linesQuantity;
    string encrypted = "";

    int numsQuantity;
    int exactPalindromesCounter = 0; // a
    int approximatePalindromesCounter = 0; // b
    int key; // k

    string answer;

    if (messageFile.good() and keyFile.good() and outputFile.good()) {
        // wiadomosc.txt
        string line;
        messageFile >> linesQuantity;

        getline(messageFile, line); // to move to next line in the file (skip number)

        for (int i = 0; i < linesQuantity; i++) {
            getline(messageFile, line);
            int lineLength = line.length();
            int counter = 0;

            if (lineLength > 0) {
                for (int j = 0; j < lineLength; j++) {
                    if (line[j] == ' ') {
                        counter++;
                    }
                    else if (line[j] == '\t') {
                        encrypted += (char)(64 + counter); // 65 -> 'A' in ASCII
                        counter = 0;
                    }
                }

                if (i + 1 < linesQuantity) {
                    encrypted += ' ';
                } 
            }
            else {
                encrypted += ' ';
            } 
        }
        cout << "encrypted: \"" << encrypted << "\"" << endl;

        // klucz.txt
        keyFile >> numsQuantity;
        for (int i = 0; i < numsQuantity; i++) {
            string num;
            keyFile >> num;

            int isPalindrome = isExactOrApproximatePalindrome(num);
            cout << num << ":" << isPalindrome << " ";

            if (isPalindrome == 1) {
                exactPalindromesCounter++;
            }
            else if (isPalindrome == 2) {
                approximatePalindromesCounter++;
            }
        }
        cout << endl << endl;

        cout << "a = " << exactPalindromesCounter << "\tb = " << approximatePalindromesCounter << endl;
        key = approximatePalindromesCounter - exactPalindromesCounter; // b - a
        cout << "k = " << approximatePalindromesCounter << " - " << exactPalindromesCounter << " = " << key << endl << endl;

        answer = decipherTransposition(encrypted, key);

        cout << "wynik: " << endl << "\"" << answer << "\"" << endl;
        outputFile << answer;
    }
    else {
        cout << "Problem z plikiem wejsciowym/wyjsciowym";
    }

    messageFile.close();
    keyFile.close();
    outputFile.close();
}