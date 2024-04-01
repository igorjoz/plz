#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int sequencesQuantity;

fstream input, output;

struct sequence {
    int ID = 0;
    int length = 0;
    vector<int> str;
    vector<vector<string>> subStr;
    vector<int> primesStr;
    int ascPrimesStreak = 0;
    int sSimilarity = 0;
    int pSimilarity = 0;
    bool notDescending = true; // flaga pocz¹tkowo true, potem ta w³aœciwoœæ jest sprawdzana
    bool usedInHierarchy = false; // flaga, czy ju¿ wypisano do pliku z hierarchi¹ podobieñstwa ci¹gów
};

bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    else if (number % 2 == 0) {
        return (number == 2);
    }

    int root = (int)sqrt((double)number);
    for (int i = 3; i <= root; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

int main()
{
    input.open("ciagi.txt", ios::in);
    if (input.good()) {

        input >> sequencesQuantity;
        sequencesQuantity++; // zwiêkszenie o 1, aby uwzglêdniæ przy pobieraniu ci¹g wzorcowy
        sequence* s = new sequence[sequencesQuantity]; // s[0] to glowny ciag, jego ID to 0;

        // pobranie ci¹gów
        for (int i = 0; i < sequencesQuantity; i++) {
            input >> s[i].length;
            s[i].ID = i;

            for (int k = 0; k < s[i].length; k++) {
                int sequenceNumber;
                input >> sequenceNumber;
                s[i].str.push_back(sequenceNumber);
                //cout << s[i].str[k] << " ";
            }
            //cout << endl;

            // stworzenie podci¹gów
            int numbersQuantity = 3;
            int startIndex = 0;
            vector<string> subStrings;

            while (true) {

                if (numbersQuantity > s[i].length) {
                    break;
                }

                string subString = "";
                for (int k = startIndex; k < startIndex + numbersQuantity; k++) {
                    subString += to_string(s[i].str[k]);
                    subString += " ";
                }
                //cout << subString << endl;
                subStrings.push_back(subString);

                startIndex++;

                if (startIndex + numbersQuantity > s[i].length) {
                    numbersQuantity++;
                    //cout << "zerowanie indexu startowego" << endl;
                    startIndex = 0;
                    s[i].subStr.push_back(subStrings);
                    subStrings.clear();
                }
            }
            //cout << endl << endl;
        }
        //cout << endl << endl << endl;

        // sprawdzenie czy ci¹g jest podobny
        for (int i = 1; i < sequencesQuantity; i++) { // i = 1, ¿eby nie sprawdzaæ pierwszego ci¹gu
            int maxSubStrSize = 0;

            NEW_SEQUENCE:
            // okreœlenie maksymalnej d³ugoœci podci¹gu, tym samym maksymalnego podobieñstwa
            if (s[0].length > s[i].length) {
                maxSubStrSize = s[i].subStr.size();
            }
            else {
                maxSubStrSize = s[0].subStr.size();
            }

            for (int subStrType = maxSubStrSize - 1; subStrType >= 0; subStrType--) { // index typu podci¹gu, zaczêcie od najd³u¿szego mo¿liwego; typ podci¹gu to iloœæ liczb na który siê sk³ada
                for (int subStrMain = 0; subStrMain < s[0].subStr[subStrType].size(); subStrMain++) { // index podci¹gu w poszczególnym typie podci¹gu ci¹gu g³ównego
                    //cout << "glowny: " << s[0].subStr[subStrType][subStrMain] << endl;
                    for (int subStr = 0; subStr < s[i].subStr[subStrType].size(); subStr++) { // index podci¹gu w poszczególnym typie podci¹gu porównywanym do g³ównego

                        //cout << s[i].subStr[subStrType][subStr] << "   ";

                        if (s[i].subStr[subStrType][subStr] == s[0].subStr[subStrType][subStrMain]) {
                            s[i].sSimilarity = subStrType + 3;
                            //cout << " --- ZNALEZIONO PODOBIENSTWO S --- " << s[i].sSimilarity << endl;

                            if (i + 1 == sequencesQuantity) {
                                goto SUBSTRINGS_CHECK_END;
                            }
                            else {
                                i++;
                                goto NEW_SEQUENCE;
                            }

                        }
                    }
                    //cout << endl;
                }
            }
            //cout << endl;
        }
        //cout << endl << endl;
        SUBSTRINGS_CHECK_END:
        //cout << endl << endl;

        // wyszukiwanie liczb pierwszych
        for (int i = 0; i < sequencesQuantity; i++) {
            //cout << "ciag: " << i << ", podciag liczb pierwszych:" << endl;

            for (int numIndex = 0; numIndex < s[i].str.size(); numIndex++) { // index liczby w ci¹gu
                if (isPrime(s[i].str[numIndex])) {
                    //cout << s[i].str[numIndex] << " ";
                    s[i].primesStr.push_back(s[i].str[numIndex]);
                }
            }
            //cout << endl;
        }
        //cout << endl << endl << endl;

        // dlugosc najdluzszego podciagu rosnacego liczb pierwszych
        for (int i = 0; i < sequencesQuantity; i++) {
            //cout << "ciag: " << i << endl;
            int currentStreak = 1;

            for (int numIndex = 1; numIndex < s[i].primesStr.size(); numIndex++) { // index liczby w ci¹gu

                if (s[i].primesStr[numIndex - 1] < s[i].primesStr[numIndex]) {
                    currentStreak++;
                }
                else {
                    if (s[i].ascPrimesStreak < currentStreak) {
                        s[i].ascPrimesStreak = currentStreak;
                    }

                    currentStreak = 1;
                }
                //cout << s[i].primesStr[numIndex] << " -- " << s[i].primesStr[numIndex - 1] << " s: " << currentStreak << endl;
            }

            if (currentStreak > s[i].ascPrimesStreak) {
                s[i].ascPrimesStreak = currentStreak;
            }
            //cout << "max: " << s[i].ascPrimesStreak << endl << endl;

            // przypisanie wartoœci do struktury
            if (s[i].ascPrimesStreak == s[0].ascPrimesStreak && s[i].ascPrimesStreak >= 2) {
                s[i].pSimilarity = s[i].ascPrimesStreak;
            }
        }

        // ciag NIEMALEJACY
        for (int i = 1; i < sequencesQuantity; i++) { // od i = 1, ¿eby nie sprawdzaæ wzorcowego (zbêdne)
            for (int numIndex = 1; numIndex < s[i].str.size(); numIndex++) { // index liczby w ci¹gu
                if (s[i].str[numIndex - 1] > s[i].str[numIndex]) {
                    s[i].notDescending = false;
                    //cout << "ciag o ID: " << s[i].ID << " NIE JEST jest niemalejacy" << endl;
                    break;
                }
            }
        }
        //cout << endl << endl << endl;

        // wynik
        /*
        hierarchia podobieñstwa:
        1. Sn, n jak najwy¿sze
        2. Pn, n jak najwy¿sze
        * przy równych n (Sn i Sn, Pn i Pn) podobieñstwo jest nierozró¿nialne
        3. ci¹g niemalej¹cy
        4. numer porz¹dkowy (kolejnoœæ wejœcia)
        */
        output.open("wynik.txt", ios::out);
        if (output.good()) {

            // informacje o ciagach
            for (int i = 0; i < sequencesQuantity; i++) {
                cout << "ciag " << s[i].ID << endl;

                for (int k = 0; k < s[i].str.size(); k++) {
                    cout << s[i].str[k] << " ";
                }
                cout << endl << "S" << s[i].sSimilarity << ", " << "P" << s[i].pSimilarity << endl;
                cout << "niemalejacy: " << s[i].notDescending << endl << endl;
            }

            for (int round = 1; round < sequencesQuantity; round++) {
                int maxS = 0, maxSID;
                int maxP = 0, maxPID;
                int firstNotDecreasingID = -1;
                int firstFreeID = -1;

                for (int i = 1; i < sequencesQuantity; i++) {

                    if (s[i].usedInHierarchy == false) {

                        if (s[i].sSimilarity > maxS) {
                            maxS = s[i].sSimilarity;
                            maxSID = s[i].ID;
                        } else if (s[i].pSimilarity > maxP) {
                            maxP = s[i].pSimilarity;
                            maxPID = s[i].ID;
                        } else if (s[i].notDescending == true && firstNotDecreasingID == -1) {
                            firstNotDecreasingID = s[i].ID;
                        } else if (s[i].usedInHierarchy == false && firstFreeID == -1) {
                            firstFreeID = s[i].ID;
                        }
                    }
                }

                if (maxS != 0) {
                    cout << maxSID << " S" << maxS;
                    output << maxSID;
                    s[maxSID].usedInHierarchy = true;
                }
                else if (maxP != 0) {
                    cout << maxPID << " P" << maxP;
                    output << maxPID;
                    s[maxPID].usedInHierarchy = true;
                }
                else if (firstNotDecreasingID != -1) {
                    cout << firstNotDecreasingID << " niemalejacy";
                    output << firstNotDecreasingID;
                    s[firstNotDecreasingID].usedInHierarchy = true;
                }
                else if (firstFreeID != -1) {
                    cout << firstFreeID << " brak podobienstwa";
                    output << firstFreeID;
                    s[firstFreeID].usedInHierarchy = true;
                }
                cout << endl;
                output << endl;
            }
        }
        else {
            cout << "Problem z plikiem wyjsciowym \"wynik.txt\"";
        }
        output.close();
    }
    else {
        cout << "Problem z otworzeniem pliku wejsciowego \"ciagi.txt\"";
    }
    input.close();
}