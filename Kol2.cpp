#include "Wybor.h"
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

#ifdef Kol_2

class Wlasciciel {
};

class Samochod {
public:
    enum StanDopuszczenia { Dopuszczony, Niedopuszczony };

private:
    char numerRejestracyjny[10];
    int licznik;
    StanDopuszczenia stan;
    const Wlasciciel& wlasciciel;
    static Samochod* instancjaWzorcowa;
    static constexpr double WAR_POCZ = 10000.0;

    void genNumerRejestracyjny(const char* xxx) {
        if (strlen(xxx) < 9) {
            strcpy(numerRejestracyjny, xxx);
        }
        else {
            cerr << "Numer rejestracyjny za długi." << endl;
        }
    }

public:
    Samochod(const char* xxx, int licznik, StanDopuszczenia stan, const Wlasciciel& wlasciciel)
        : wlasciciel(wlasciciel) {
        genNumerRejestracyjny(xxx);
        setLicznik(licznik);
        this->stan = stan;
    }

    Samochod() : wlasciciel(*instancjaWzorcowa->wlasciciel) {
        if (instancjaWzorcowa == nullptr) {
            cerr << "Brak instancji wzorcowej." << endl;
        }
        genNumerRejestracyjny(instancjaWzorcowa->numerRejestracyjny);
        setLicznik(instancjaWzorcowa->licznik);
        this->stan = instancjaWzorcowa->stan;
    }

    const char* getNumerRejestracyjny() const {
        return numerRejestracyjny;
    }

    int getLicznik() const {
        return licznik;
    }

    void setLicznik(int licznik) {
        if (licznik < 0) {
            cerr << "Licznik nie może być ujemny." << endl;
        }
        else {
            this->licznik = licznik;
        }
    }

    StanDopuszczenia getStan() const {
        return stan;
    }

    void setStan(StanDopuszczenia stan) {
        this->stan = stan;
    }

    const Wlasciciel& getWlasciciel() const {
        return wlasciciel;
    }

    virtual int zasieg() const {
        if (stan == Niedopuszczony) {
            cerr << "Samochód niedopuszczony do jazdy." << endl;
        }
        return 800;
    }

    operator double() const {
        double wspSparw = (stan == Dopuszczony) ? 1.0 : 0.2;
        double wartosc = (WAR_POCZ - 0.2 * licznik) * wspSparw;
        return (wartosc < 400.0) ? 400.0 : wartosc;
    }

    bool operator!=(const Samochod& other) const {
        return (licznik - other.licznik > 20 || licznik - other.licznik < -20) || stan != other.stan;
    }

    static void setInstancjaWzorcowa(Samochod* wzorcowa) {
        instancjaWzorcowa = wzorcowa;
    }
};

Samochod* Samochod::instancjaWzorcowa = nullptr;

class SamochodElektryczny : public Samochod {
private:
    int stanBaterii;

    void validateStanBaterii(int stanBaterii) {
        if (stanBaterii < 0 || stanBaterii > 100) {
            cerr << "Stan baterii musi być wyrazony w procentach." << endl;
        }
    }

public:
    SamochodElektryczny(const char* xxx, int licznik, StanDopuszczenia stan, const Wlasciciel& wlasciciel, int stanBaterii)
        : Samochod(xxx, licznik, stan, wlasciciel) {
        validateStanBaterii(stanBaterii);
        this->stanBaterii = stanBaterii;
    }

    int getStanBaterii() const {
        return stanBaterii;
    }

    void setStanBaterii(int stanBaterii) {
        validateStanBaterii(stanBaterii);
        this->stanBaterii = stanBaterii;
    }

    int zasieg() const override {
        if (getStan() == Niedopuszczony) {
            cerr << "Samochód niedopuszczony do jazdy." << endl;
        }
        return static_cast<int>(2.5 * stanBaterii);
    }

    operator double() const {
        double wartosc = Samochod::operator double() * 0.7;
        return (wartosc < 400.0) ? 400.0 : wartosc;
    }
};

int main() {
   
    Wlasciciel wlasciciel; 
    Samochod wzorcowy("ABC1234", 5000, Samochod::Dopuszczony, wlasciciel);
    Samochod::setInstancjaWzorcowa(&wzorcowy);

    SamochodElektryczny samochod("DEF5678", 3000, Samochod::Dopuszczony, wlasciciel, 80);

    cout << "Numer rejestracyjny: " << samochod.getNumerRejestracyjny() << endl;
    cout << "Licznik: " << samochod.getLicznik() << endl;
    cout << "Stan baterii: " << samochod.getStanBaterii() << "%" << endl;
    cout << "Zasięg: " << samochod.zasieg() << " km" << endl;
    cout << "Wartość: " << static_cast<double>(samochod) << " PLN" << endl;

    return 0;
}

#endif
```
