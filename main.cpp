#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Definicja klasy Uzytkownik
class Uzytkownik {
public:
    int id;
    string imie;
    string komputer;
    string ip;

    Uzytkownik(int id, string imie, string komputer, string ip)
        : id(id), imie(imie), komputer(komputer), ip(ip) {}
};

// Definicja klasy Komputer
class Komputer {
public:
    int id;
    string nazwa;
    string ip;
    int uzytkownik_id;
    Uzytkownik* uzytkownik;

    Komputer(int id, string nazwa, string ip, int uzytkownik_id, Uzytkownik* uzytkownik)
        : id(id), nazwa(nazwa), ip(ip), uzytkownik_id(uzytkownik_id), uzytkownik(uzytkownik) {}
};


class Aplikacja {
private:
    vector<Uzytkownik> uzytkownicy;
    vector<Komputer> komputery;

// Funkcja generujaca nowe ID uzytkownika
    int pobierzNoweIDUzytkownika() {
        if (uzytkownicy.empty()) {
            return 1;
        }
        return uzytkownicy.back().id + 1;
    }

public:

    void uruchom() {
        int wybor;
        while (true) {
            cout << "1. Wyswietl uzytkownikow\n2. Wyszukaj uzytkownika\n";
            cout << "3. Dodaj uzytkownika\n4. Eksportuj dane do pliku CSV\n";
            cout << "5. Importuj dane z pliku CSV\n6. Wyjscie\n  Twoj wybor: ";
            cin >> wybor;

            switch (wybor) {
            case 1:
                wyswietlUzytkownikow();
                break;
            case 2:
                wyszukajUzytkownika();
                break;
            case 3:
                dodajUzytkownika();
                break;
            case 4:
                eksportujDoCsv();
                break;
            case 5:
                importujZCsv();
                break;
            case 6:
                cout << "Wyjscie...\n";
                return;
            default:
                cout << "Nieprawidlowy wybor.\n";
                break;
            }
        }
    }

// Funkcja wyswietlajaca liste uzytkownikow
    void wyswietlUzytkownikow(const vector<Uzytkownik>& uzytkownicy) {
        for (const auto& uzytkownik : uzytkownicy) {
            cout << "Imie: " << uzytkownik.imie << ", ID: " << uzytkownik.id << endl;
        }
        if (uzytkownicy.empty()) {
            cout << "Brak uzytkownikow w bazie danych.\n";
        }
    }
    void wyswietlUzytkownikow() {
        wyswietlUzytkownikow(uzytkownicy);

    }

   // Funkcja wyswietlajaca liste komputerow
    void wyswietlKomputery() {
        for (const auto& komputer : komputery) {
            cout << "Nazwa: " << komputer.nazwa << ", ID: " << komputer.id << endl;
        }
        if (komputery.empty()) {
            cout << "Brak komputerow w bazie danych.\n";
        }
    }

// Funkcja wyświetlająca listę adresów IP
    void wyswietlAdresyIP() {
        for (const auto& uzytkownik : uzytkownicy) {
            cout << "Adres IP uzytkownika: " << uzytkownik.ip << endl;
        }
        for (const auto& komputer : komputery) {
            cout << "Adres IP komputera: " << komputer.ip << endl;
        }
    }

// Funkcja wyszukiwania użytkownika
    void wyszukajUzytkownika() {
        string frazaWyszukiwania;
        cout << "Wpisz szukana faraze (imie): ";
        cin >> frazaWyszukiwania;

        bool znaleziono = false;
        for (const auto& uzytkownik : uzytkownicy) {
            if (uzytkownik.imie == frazaWyszukiwania || to_string(uzytkownik.id) == frazaWyszukiwania) {
                cout << "Znaleziono uzytkownika: " << uzytkownik.imie << ", ";
                cout << "ID: " << uzytkownik.id << endl;
                cout << "Komputer: " << uzytkownik.komputer << endl;
                cout << "Adres IP: " << uzytkownik.ip << endl;
                znaleziono = true;
                break;
            }
        }
        if (!znaleziono) {
            cout << "Nie znaleziono uzytkownika.\n";
        }
    }

// Funkcja dodawania użytkownika
    void dodajUzytkownika() {
        string imie, komputer, ip;
        cout << "Wprowadz imie uzytkownika: ";
        getline(cin >> ws, imie);
        cout << "Wprowadz nazwe komputera: ";
        getline(cin >> ws, komputer);
        cout << "Wprowadz adres IP uzytkownika: ";
        getline(cin >> ws, ip);

        int noweID = pobierzNoweIDUzytkownika();
        uzytkownicy.push_back(Uzytkownik(noweID, imie, komputer, ip));
        cout << "Uzytkownik " << imie << " został dodany.\n";
    }

// Funkcja eksportu do CSV
    void eksportujDoCsv() {
        ofstream plik("uzytkownicy.csv");
        plik << "Imie,ID,Komputer,Adres IP\n";
        for (const auto& uzytkownik : uzytkownicy) {
            plik << uzytkownik.imie << "," << uzytkownik.id << "," << uzytkownik.komputer << "," << uzytkownik.ip << "\n";
        }
        plik.close();
        cout << "Dane zostaly wyeksportowane do pliku uzytkownicy.csv.\n";
    }

// Funkcja importu z CSV
    void importujZCsv() {
        ifstream plik("uzytkownicy.csv");
        string linia;
        getline(plik, linia); // Pominięcie nagłówka
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string imie, komputer, ip;
            int id;
            ss >> imie >> id >> komputer >> ip;
            uzytkownicy.push_back(Uzytkownik(id, imie, komputer, ip));
        }
        plik.close();
        cout << "Dane zostaly zaimportowane z pliku uzytkownicy.csv.\n";
    }
};

int main() {
    Aplikacja aplikacja;
    aplikacja.uruchom();
    return 0;
}