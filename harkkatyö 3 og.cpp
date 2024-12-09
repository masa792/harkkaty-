//  harkkaty�
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale.h> // setlocale-funktiota varten
using namespace std;

const int MIN_VARAUS_NUMERO = 10000;     // vakioita ohjelmaa varten
const int MAX_VARAUS_NUMERO = 99999;

// Tietorakenne varauksille
struct varaukset {
    int huonenumero;
    int y�t;
    int hinta;
    string asiakkaan nimi;
};

// Apufunktiot
int getRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

template <typename T>
T getValidatedInput(const string& prompt, T min, T max) {
   T value;
   while (true) {
   cout << prompt;
   cin >> value;
   if (cin.fail() || value < min || value > max) {
   cin.clear();
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   cout << "Virheellinen sy�te! Yrit� uudelleen.\n";
   }
   else {
   cin.ignore(numeric_limits<streamsize>::max(), '\n');
   return value;
   }
   }
}

string getValidatedStringInput(const string& prompt) {
   string value;
   while (true) {
   cout << prompt;
   getline(cin, value);
   if (value.empty()) {
   cout << "Virheellinen sy�te! Nimi ei voi olla tyhj�.\n";
   }
   else {
   return value;
   }
   }
}

// Aliohjelmat
void (vector<bool>& yhdenhengenhuoneet, vector<bool>& kahdenhengenhuoneet, int& hinta1hh, int& hinta2hh) {
    int huoneet = getRandomNumber(30, 70);
    int yhdenhengenhuone = huoneet / 2;
    int kahdenhengenhuone = huoneet - yhden hengen huone;

    hinta1hh = getRandomNumber(80, 100);
    hinta2hh = getRandomNumber(120, 150);

    yhdenhengenhuoneet.resize(yhdenhengenhuone, false);
    kahdenhengenhuoneet.resize(kahdenhengenhuone, false);

    cout << "Hotellissa on " << yhdenhengenhuone << " yhden hengen huonetta ja " << kahdenhengenhuone << " kahden hengen huonetta.\n"
        << "1hh: " << hinta1hh << " EUR per y�\n"
        << "2hh: " << hinta2hh << " EUR per y�\n";
}

int findRandomAvailableRoom(const vector<bool>& huoneet) {
    vector<int> vapaathuoneet;
    for (size_t i = 0; i < huoneen.koko(); ++i) {
    if (!huoneet[i]) {
    vapaathuoneet.push_back(static_cast<int>(i) + 1);
    }
    }
    if (vapaathuoneet.empty()) {
    return -1;        // Ei vapaita huoneita
    }
    int randomIndex = getRandomNumber(0, static_cast<int>(vapaathuoneet.size() - 1));
    return vapaathuoneet[randomIndex];
}

void varaahuoneita(vector<bool>& yhdenhengenhuoneet, vector<bool>& kahdenhengenhuoneet, int hinta1hh, int hinta2hh, map<int, varaukset>& varaukset) {
    cout << "Valitse huonetyyppi:\n1. Yhden hengen huone\n2. Kahden hengen huone\n";
    int huoneenmalli = getValidatedInput<int>("Valintasi: ", 1, 2);

    int huonenumero = -1;
    int hintapery� = 0;

    if (huoneenmalli == 1) {
    huonenumero = findRandomAvailableRoom(yhdenhengenhuoneet);
    hintapery� = hinta1hh;
    if (huonenumero != -1) {
    yhdenhengenhuoneet[huonenumero - 1] = true;
    }
    }
    else if (huoneenmalli == 2) {
    huonenumero = findRandomAvailableRoom(kahdenhengenhuoneet);
    hintapery� = hinta2hh;
    if (huonenumero != -1) {
    kahdenhengenhuoneet[huonenumero - 1] = true;
        }
    }

    if (huonenumero == -1) {
    cout << "Valitsemasi huonetyyppi ei ole saatavilla.\n";
    return;
    }

    // Varaus
    int y�t = getValidatedInput<int>("Anna �iden m��r�: ", 1, 365);
    string asiakkaannimi = getValidatedStringInput("Anna varaajan nimi: ");
    int varausnumero = getRandomNumber(MIN_VARAUS_NUMERO, MAX_VARAUS_NUMERO);
    int kokohinta = hintapery� * y�t;

    varaukset[varausnumero] = { huonenumero, y�t, kokohinta, asiakkaannimi };

    cout << "Varaus onnistui! Varausnumero: " << varausnumero << "\n"
        << "Huone: " << huonenumero << "\n"
        << "Varaaja: " << asiakkaannimi << "\n"
        << "�iden m��r�: " << y�t << "\n"
        << "Loppusumma: " << kokohinta << " EUR\n";
}

// P��ohjelma
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Asetetaan ��kk�set n�kyviin
    setlocale(LC_ALL, "fi_FI");

    vector<bool> yhdenhengenhuoneet;
    vector<bool> kahdenhengenhuoneet;
    int hinta1hh, hinta2hh;
    map<int, varaukset> varaukset;

    initializeHotel(yhdenhengenhuoneet, kahdenhengenhuoneet, hinta1hh, hinta2hh);

    bool running = true;
    while (running) {
    cout << "\nValitse toiminto:\n"
            << "1. Varaa huone\n"
            << "2. Lopeta ohjelma\n";
    int choice = getValidatedInput<int>("Valintasi: ", 1, 2);

    switch (choice) {
    case 1:
    varaahuoneita(yhdenhengenhuoneet, kahdenhengenhuoneet, hinta1hh, hinta2hh, varaukset);
    break;
    case 2:
    running = false;
    break;
    default:
    cout << "Virheellinen valinta!\n";
    break;
    }
    }

    cout << "Kiitos k�yt�st�, ohjelma suljetaan!\n";
    return 0;
}
