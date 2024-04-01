#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int GATES_QUANTITY = 5;

struct arrival {
    float arrivalTime;
    int suggestedGate;
    int actualGate;
};

arrival arrivals[150];

struct gate {
    bool free = true;
    float serviceStart = 0;
    float serviceFinish = 0;
};

gate gates[GATES_QUANTITY];

float t = 0; // duration of simulation
int arrivalIndex = 0;
float serviceTime;
string headers = "Czas_przybycia_pojazdu_do_punktu_poboru_oplat\tBramka_proponowana_przez_system_automatyczny\tBramka,_ktora_faktycznie_zrealizowala obsluge_pojazdu";

int precision = 1000;

void handleChoosenGate(int gateIndex, int arrivalIndex, float arrivalTime, float serviceTime) {
    arrivals[arrivalIndex].actualGate = gateIndex;  
    gates[gateIndex].free = false;
    gates[gateIndex].serviceStart = arrivalTime;
    gates[gateIndex].serviceFinish = arrivalTime + serviceTime;
}

void newCarArrival() {
    cout << arrivalIndex << ":\t";

    // sprawdzenie dostepnosci bramek
    for (int i = 1; i < GATES_QUANTITY; i++) {
        if (gates[i].serviceFinish <= t) {
            gates[i].free = true;
            cout << i << " ";
        }
        else if (gates[i].free == false) {
            cout << i << "x";
        }
        cout << " ";
    }

    // zapis o czasie przybycia pojazdu do punktu poboru oplat
    arrivals[arrivalIndex].arrivalTime = t;

    // wylosowanie przez automatyczny system wolnej bramki i zapis
    int suggestedGate = rand() % 4 + 1;
    arrivals[arrivalIndex].suggestedGate = suggestedGate;

    // wybor bramki rzeczywistej i zapis
    bool foundFreeGate = false;
    if (gates[suggestedGate].free) {
        foundFreeGate = true;
        handleChoosenGate(suggestedGate, arrivalIndex, t, serviceTime);
    }
    else {
        for (int i = 1; i < GATES_QUANTITY; i++) {
            if (gates[i].free) {
                foundFreeGate = true;
                handleChoosenGate(i, arrivalIndex, t, serviceTime);
                break;
            }
        }
    }
    if (!foundFreeGate) {
        arrivals[arrivalIndex].actualGate = 0;
    }

    cout << "\tt: " << arrivals[arrivalIndex].arrivalTime;
    if (arrivalIndex > 0) {
        cout << "\tdelta: " << arrivals[arrivalIndex].arrivalTime - arrivals[arrivalIndex - 1].arrivalTime;
    }
    cout << "\tsug: " << arrivals[arrivalIndex].suggestedGate << "\tact: " << arrivals[arrivalIndex].actualGate;
    if (arrivals[arrivalIndex].suggestedGate != arrivals[arrivalIndex].actualGate) {
        cout << "\t !!!";
    }
    cout << endl;
    float temp = rand() % (precision * 4) + precision;
    temp /= precision;
    t += temp;

    arrivalIndex++;
}

int main()
{
    srand((unsigned)time(NULL));

    float randomNumbers[10];
    for (int i = 0; i < 10; i++) {
        randomNumbers[i] = rand() % (precision * 3) + precision;
        randomNumbers[i] /= precision;
    }
    int randomIndex = rand() % 10;

    serviceTime = randomNumbers[randomIndex];
    cout << "service time: " << serviceTime << endl;

    while (t < 150) {
        newCarArrival();
    }
    newCarArrival();

    // zapis do pliku
    fstream output;
    output.open("Zadanie 3a.txt", ios::out);
    if (output.good()) {
        output << headers << endl;
        for (int i = 0; i < arrivalIndex; i++) {
            output << arrivals[i].arrivalTime << "\t";
            output << arrivals[i].suggestedGate << "\t";
            output << arrivals[i].actualGate << endl;
        }
    }
    else {
        cout << endl << "Problem z plikiem \"Zadanie 3a.txt\"";
    }
}

// bramki: 1, 2, 3, 4; 0 (jeœli 1-4 nie by³y wolne)
// odstêpy czasu do wylosowania: od 1 do 5
// automatyczny system kieruje pojazd do jednej z czterch bramek, ale czasami bramka jest ju¿ zajêta -->
// w takim wypadku kierowca zaczyna sprawdzaæ kolejno od 1. do 4. bramki, jeœli ka¿da jest zajêta, to jedzie do bramki 0
// czas obs³ugi to losowa liczba z zakresu 1 do 4 i jest identyczny dla ka¿dej bramki!!