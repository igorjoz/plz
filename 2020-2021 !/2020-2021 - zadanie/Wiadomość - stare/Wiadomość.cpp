#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char spacesToLetter(int spacesQuantity) {
    if (spacesQuantity > 0 and spacesQuantity <= 26) {
        return (char)(96 + spacesQuantity); // 97 -> 'a' in ASCII
    }
    else return '!';
}

bool isPalindrome(string text) {
    int length = text.length();

    for (int i = 0; i < length / 2; i++) {
        if (text[i] != text[length - i - 1]) {
            return false;
        }
    }

    return true;
}

bool isApproximatePalindrome(string text, int maxErrors = 2) {
    int length = text.length();
    int errors = 0;

    for (int i = 0; i < length / 2; i++) {
        if (text[i] != text[length - i - 1]) {
            errors += 2;
        }
        if (errors > maxErrors) {
            return false;
        }
    }

    return true;
}

string caesarCipher(string text, int key) {
    string decrypted = "";

    for (int i = 0; i < text.length(); i++) {
        int charCode = (int)text[i];

        if (charCode >= 97 and charCode + key <= 122) {
            decrypted += (char)(charCode + key);
        }
        else if (text[i] >= 'a' and text[i] <= 'z') {
            decrypted += (char)(charCode + key - 26); // charCode - 122 + 96 + key
        }
        else {
            decrypted += text[i];
        }
    }

    return decrypted;
}

int main()
{
    fstream messageFile, keyFile;
    messageFile.open("output.txt", ios::in);
    keyFile.open("klucz.txt", ios::in);

    int textLines;
    vector <string> lines;
    string encryptedSentence = "";
    
    vector <int> nums;
    int numsQuantity; // n
    int exactPalindromeCounter = 0; // a
    int approximatePalindromeCounter = 0; // b
    int key; // k

    string answer;
    

    if (messageFile.good() and keyFile.good()) {
        // wiadomosc.txt
        string line;
        messageFile >> textLines;
        lines.reserve(textLines);

        getline(messageFile, line); // to move to next line in the file (skip number)

        for (int i = 0; i < textLines; i++) {
            getline(messageFile, line);
            lines.push_back(line);

            int counter = 0;
            int lineLength = lines[i].length();

            for (int j = 0; j < lineLength; j++) {
                if (lines[i][j] == ' ') {
                    //cout << ".";
                    counter++;
                }
                else if (lines[i][j] == '\t') {
                    cout << spacesToLetter(counter);
                    encryptedSentence += spacesToLetter(counter);
                    counter = 0;
                }
            }
            cout << " ";
            encryptedSentence += " ";
        }
        cout << endl << endl;
        cout << encryptedSentence;

        // klucz.txt
        keyFile >> numsQuantity;
        nums.reserve(numsQuantity);
        for (int i = 0; i < numsQuantity; i++) {
            int temp;
            keyFile >> temp;
            nums.push_back(temp);

            string numStr = to_string(nums[i]);

            cout << numStr << ":" << isPalindrome(numStr) << "," << isApproximatePalindrome(numStr) << " ";
            if (isPalindrome(numStr)) exactPalindromeCounter++;
            else if (isApproximatePalindrome(numStr)) approximatePalindromeCounter++;
        }
        cout << endl << endl;

        cout << "n = " << numsQuantity << "\ta = " << exactPalindromeCounter << "\tb = " << approximatePalindromeCounter << endl;
        key = (numsQuantity * exactPalindromeCounter + 2 * approximatePalindromeCounter) % 26;
        cout << "k = " << numsQuantity * exactPalindromeCounter + 2 * approximatePalindromeCounter << " mod 26 = " << key << endl << endl;
        answer = caesarCipher(encryptedSentence, 26 - key);
        cout << answer;

        cout << endl << endl << caesarCipher("gclhq greub zvcbvwnlp", 26 - 3);
    }
    else {
        cout << "Invalid input files";
    }
}