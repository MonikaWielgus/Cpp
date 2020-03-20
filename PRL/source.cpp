//Monika Wielgus
#include <iostream>
using namespace std;

extern double limit_dziecko[];
extern double limit_kobieta_w_ciazy[];
extern double limit_robotnik[];

enum Grupa{dziecko, kobieta_w_ciazy, robotnik, bez_grupy};
static unsigned int ludnosc=0;

struct Kartka
{
    double mieso;
    double czekolada;
};
struct Obywatel
{
    int NIP;
    Grupa grupa;
    Kartka kartka;
    Obywatel *nastepny;
    Obywatel *poprzedni;
    Obywatel()
    {
        NIP=0;
        grupa=bez_grupy;
        kartka.mieso=0.0;
        kartka.czekolada=0.0;
        nastepny=NULL;
        poprzedni=NULL;
    }
    Obywatel(int g)
    {
        nastepny=NULL;
        poprzedni=NULL;
        NIP=ludnosc+1;
        ludnosc++;
        if(dziecko==g)
        {
            grupa=dziecko;
            kartka.mieso=*(limit_dziecko);
            kartka.czekolada=*(limit_dziecko+1);
        }
        if(kobieta_w_ciazy==g)
        {
            grupa=kobieta_w_ciazy;
            kartka.mieso=*(limit_kobieta_w_ciazy);
            kartka.czekolada=*(limit_kobieta_w_ciazy+1);
        }
        if(robotnik==g)
        {
            grupa=robotnik;
            kartka.mieso=*(limit_robotnik);
            kartka.czekolada=*(limit_robotnik+1);
        }
    }

};

struct Sklep
{
    char symbol; //M-sklep miesny, C-sklep z czekolada
    double towar; //ile miesa lub czekolady dany sklep moze sprzedac
    Obywatel *pierwszy;
    Obywatel *ostatni;
    Sklep()
    {
        pierwszy=NULL;
        ostatni=NULL;
    }
    Sklep(char s, double x) // s to C albo M
    {
        pierwszy=NULL;
        ostatni=NULL;
        symbol=s;
        towar=x;
    }
    void dostawa(double g)
    {
        towar+=g;
    }
    void ustawKlientaNaKoniec(int g)
    {
        Obywatel *nowy=new Obywatel(g);
        if (pierwszy==nullptr)
        {
            pierwszy=nowy;
            ostatni=nowy;
        }
        else
        {
            Obywatel *tymczasowy=ostatni;
            ostatni=nowy;
            tymczasowy->nastepny=ostatni;
        }
    }
    void ustawKlientaNaPoczatek(int g)
    {
        Obywatel* nowy = new Obywatel(g);
        nowy->poprzedni=nullptr;
        nowy->nastepny=pierwszy;
        if (pierwszy==nullptr)
        {
            pierwszy=nowy;
            ostatni=nowy;
        }
        else
        {
            pierwszy=nowy;
        }
    }
    void ustawZaKlientem(int k, int g)
    {
        Obywatel *nowy = new Obywatel(g);
        Obywatel *tymczasowy=pierwszy;
        for(int i=2; i<=k; i++)
        {
            if(tymczasowy!=nullptr)
            {
                tymczasowy=tymczasowy->nastepny;
            }
            else
            {
                break;
            }
        }
        if(tymczasowy!=nullptr&&tymczasowy->nastepny!=nullptr)
        {
            nowy->nastepny=tymczasowy->nastepny;
            nowy->poprzedni=tymczasowy;
            tymczasowy->nastepny=nowy;

        }
        else if(tymczasowy!=nullptr&&tymczasowy->nastepny==nullptr)
        {
            ostatni=nowy;
            tymczasowy->nastepny=nowy;
            nowy->poprzedni=tymczasowy;
        }
        else
        {
            nowy->poprzedni=ostatni;
            ostatni->nastepny=nowy;
            ostatni=nowy;
        }

    }
    void usunKlienta(int n)
    {
        struct Obywatel *tymczasowy;
        struct Obywatel *tymczasowy2;

        if(pierwszy->NIP==n) //pierwszy
        {
            tymczasowy=pierwszy;
            pierwszy=pierwszy->nastepny;
            pierwszy->poprzedni=nullptr;
            delete tymczasowy;
            ludnosc--;
        }
        tymczasowy2=pierwszy;
        while(tymczasowy2->nastepny->nastepny!=nullptr) //srodkowy, musza byc za nim dwa elementy, bo tsk dziala ten algorytm
        {
            if(tymczasowy2->nastepny->NIP==n)
            {
                tymczasowy=tymczasowy2->nastepny;
                tymczasowy2->nastepny=tymczasowy->nastepny;
                tymczasowy->nastepny->poprzedni=tymczasowy2;
                delete tymczasowy;
                ludnosc--;
            }
            tymczasowy2=tymczasowy2->nastepny;

        }
        if(tymczasowy2->nastepny->NIP==n) //ostatni
        {
            tymczasowy=tymczasowy2->nastepny;
            delete tymczasowy;
            tymczasowy2->nastepny=nullptr;
            ludnosc--;
        }

    }
    bool towarWydano(double x, Obywatel* o)
    {
        if(symbol=='C')
        {
            if(towar>0)
            {
                if(towar>=x)
                {
                    if(o->kartka.czekolada>=x)
                    {
                        towar-=x;
                        o->kartka.czekolada-=x;
                    }
                    else
                    {
                        o->kartka.czekolada=0;
                        towar-=o->kartka.czekolada;
                    }
                }
                else
                {
                    if(o->kartka.czekolada>=x)
                    {
                        towar=0;
                        o->kartka.czekolada-=towar;
                    }
                    else
                    {
                        if(towar>=o->kartka.czekolada)
                        {
                            towar-=x;
                            o->kartka.czekolada-=x;
                        }
                        else
                        {
                            towar=0;
                            o->kartka.czekolada-=x;
                        }
                    }
                }
            return true;
            }
            else return false;
        }
        else if(symbol=='M')
        {
            if(towar>0)
            {
                if(towar>=x)
                {
                    if(o->kartka.mieso>=x)
                    {
                        towar-=x;
                        o->kartka.mieso-=x;
                    }
                    else
                    {
                        o->kartka.mieso=0;
                        towar-=o->kartka.mieso;
                    }
                }
                else
                {
                    if(o->kartka.mieso>=x)
                    {
                        towar=0;
                        o->kartka.mieso-=towar;
                    }
                    else
                    {
                        if(towar>=o->kartka.mieso)
                        {
                            towar-=x;
                            o->kartka.mieso-=x;
                        }
                        else
                        {
                            towar=0;
                            o->kartka.mieso-=x;
                        }
                    }
                }
            return true;
            }
            else return false;
        }
    }
    void sprzedaz(double x)
    {
        Obywatel *tymczasowy=pierwszy;

        while(tymczasowy!=nullptr)
        {
            if(towarWydano(x,tymczasowy)==true)
            {
                if(tymczasowy->nastepny!=nullptr)
                {
                    usunKlienta(tymczasowy->NIP);
                    tymczasowy=pierwszy;
                }
                else
                    usunKlienta(tymczasowy->NIP);
            }
            else
                break;
        }
    }
    void odwrocKolejnosc()
    {
        Obywatel *obecny=pierwszy;
        Obywatel *tpoprzedni=nullptr;
        Obywatel *tnastepny=nullptr;
        while(obecny)
        {
            tnastepny=obecny->nastepny;
            obecny->nastepny=tpoprzedni;
            obecny->poprzedni=tnastepny;
            tpoprzedni=obecny;
            obecny=tnastepny;
        }
        pierwszy=tpoprzedni;
    }
    int sprwadzObecnosc()
    {
        Obywatel *tymczasowy=pierwszy;
        int ludzie=0;
        while(tymczasowy!=nullptr)
        {
            cout << tymczasowy->NIP << " " <<tymczasowy->grupa << " " << tymczasowy->kartka.mieso << " " << tymczasowy->kartka.czekolada;
            cout << endl;
            ludzie++;
            tymczasowy=tymczasowy->nastepny;
        }
        return ludzie;
    }
    void dolaczKolejke(Sklep &sklep2)
    {
        if(sklep2.symbol==symbol)
        {
            sklep2.odwrocKolejnosc();
            ostatni->nastepny=sklep2.pierwszy;
        }
    }
    ~Sklep()
    {

    }

};

