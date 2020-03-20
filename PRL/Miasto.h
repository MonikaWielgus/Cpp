//Monika Wielgus
#ifndef __MIASTO_H__
#define __MIASTO_H__
#include "source.cpp"

struct Miasto{
    int liczba_sklepow_miesnych;
    int liczba_sklepow_zczekolada;
    Sklep *SklepyMiesne;
    Sklep *SklepyZCzekolada;

    Miasto(int m, int cz){
        liczba_sklepow_miesnych=m;
        liczba_sklepow_zczekolada=cz;
        SklepyMiesne=new Sklep[liczba_sklepow_miesnych];
        SklepyZCzekolada=new Sklep[liczba_sklepow_zczekolada];
    };
};

#endif
