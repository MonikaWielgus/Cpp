//Monika Wielgus
#include <iostream>
#include "Miasto.h"
using namespace std;

double limit_dziecko[2]={0.5, 0.1};
double limit_robotnik[2]={2.5, 0.25};
double limit_kobieta_w_ciazy[2]={4.0, 0.5};
int main(){
    cout << ludnosc << endl;
    Miasto Krakow(1,1);
    Krakow.SklepyZCzekolada[0].symbol = 'C';
    Krakow.SklepyZCzekolada[0].towar = 10;
    Krakow.SklepyZCzekolada[0].ustawKlientaNaKoniec(0);
    cout << Krakow.SklepyZCzekolada[0].sprwadzObecnosc() << endl;

    Krakow.SklepyZCzekolada[0].ustawKlientaNaKoniec(1);
    Krakow.SklepyZCzekolada[0].ustawKlientaNaKoniec(2);
    Krakow.SklepyZCzekolada[0].ustawKlientaNaKoniec(1);
    Krakow.SklepyZCzekolada[0].ustawKlientaNaPoczatek(2);
    cout << Krakow.SklepyZCzekolada[0].sprwadzObecnosc() << endl;
    cout << ludnosc << endl;
    Krakow.SklepyZCzekolada[0].usunKlienta(2);

    cout << Krakow.SklepyZCzekolada[0].sprwadzObecnosc() << endl;
    Krakow.SklepyZCzekolada[0].ustawZaKlientem(8,1);
    cout << ludnosc << endl;
    Krakow.SklepyZCzekolada->odwrocKolejnosc();
    cout << Krakow.SklepyZCzekolada[0].sprwadzObecnosc() << endl;

    cout << Krakow.SklepyZCzekolada[0].sprwadzObecnosc() << endl;

    return 0;
}
