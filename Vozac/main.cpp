// vashiot kod ovde
#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
    char ime[101];
    int vozrast;
    int brTrki;
    bool veteran;
    void copy(const Vozac& dr){
        strcpy(ime, dr.ime);
        vozrast=dr.vozrast;
        brTrki=dr.brTrki;
        veteran=dr.veteran;
    }
public:
    Vozac(const char *ime="", const int vozrast=0, const int brTrki=0, bool veteran=false):
            vozrast(vozrast), brTrki(brTrki), veteran(veteran){
        strcpy(this->ime, ime);
    }
    Vozac(const Vozac& dr){
        copy(dr);
    }
    Vozac& operator=(const Vozac& dr){
        if(this!=&dr){ copy(dr); }
        return *this;
    }

    bool operator==(const Vozac &rhs);

    bool operator!=(const Vozac &rhs);

    const char *getIme() const {
        return ime;
    }

    int getVozrast() const {
        return vozrast;
    }

    void setVozrast(int vozrast) {
        Vozac::vozrast = vozrast;
    }

    int getBrTrki() const {
        return brTrki;
    }

    void setBrTrki(int brTrki) {
        Vozac::brTrki = brTrki;
    }

    bool isVeteran() const {
        return veteran;
    }

    void setVeteran(bool veteran) {
        Vozac::veteran = veteran;
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os<<vozac.ime<<endl;
        os<<vozac.vozrast<<endl;
        os<<vozac.brTrki<<endl;
        if(vozac.veteran){os<<"VETERAN"<<endl;}
        return os;
    }

     virtual double zarabotuvackaPoTrka()const{
        return 0.0;
    };
     virtual double danok()const{
         return 0.0;
     };
};
class Avtomobilist: public Vozac{
    double cenaAvtomobil;
    void copy(const Avtomobilist& dr){
        cenaAvtomobil=dr.cenaAvtomobil;
    }
public:
    Avtomobilist(const char *ime="", const int vozrast=0, const int brTrki=0, const bool veteran=false, const double cenaAvtomobil=0.0):
            Vozac(ime, vozrast, brTrki, veteran), cenaAvtomobil(cenaAvtomobil){}
    Avtomobilist(const Avtomobilist& dr): Vozac(dr){
        copy(dr);
    }
    Avtomobilist& operator=(const Avtomobilist& dr){
        if(this!=&dr)
        {
            Vozac::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    double zarabotuvackaPoTrka()const{
        return (cenaAvtomobil/5.0);
    }
    double danok()const{
        if(getBrTrki()>10){
            return (zarabotuvackaPoTrka())*0.15;
        }
        else
            return (zarabotuvackaPoTrka())*0.1;
    }
    bool operator==(const Avtomobilist& dr) const{
        return zarabotuvackaPoTrka()==dr.zarabotuvackaPoTrka();
    }
    bool operator!=(const Avtomobilist& dr) const{
        return zarabotuvackaPoTrka()!=dr.zarabotuvackaPoTrka();
    }
};
class Motociklist: public Vozac{
    double mokjnost;
    void copy(const Motociklist& dr){
        mokjnost=dr.mokjnost;
    }
public:
    Motociklist(const char *ime="", const int vozrast=0, const int brTrki=0, const bool veteran=false, const double mokjnost=0.0):
            Vozac(ime, vozrast, brTrki, veteran), mokjnost(mokjnost){}
    Motociklist(const Motociklist& dr): Vozac(dr){
        copy(dr);
    }
    Motociklist& operator=(const Motociklist& dr){
        if(this!=&dr)
        {
            Vozac::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    double zarabotuvackaPoTrka()const{
        return mokjnost*20.0;
    }
    double danok()const{
        if(isVeteran()){
            return (zarabotuvackaPoTrka())*0.25;
        }
        else
            return (zarabotuvackaPoTrka())*0.2;
    }
    bool operator==(const Motociklist& dr) const{
        return zarabotuvackaPoTrka()==dr.zarabotuvackaPoTrka();
    }
    bool operator!=(const Motociklist& dr) const{
        return zarabotuvackaPoTrka()!=dr.zarabotuvackaPoTrka();
    }
};
int soIstaZarabotuvachka(Vozac **vozac, int brVozaci, Vozac *drVozac){
    int index=0;
    for (int i = 0; i < brVozaci; ++i) {
        if(vozac[i]->zarabotuvackaPoTrka()==drVozac->zarabotuvackaPoTrka()){
            index++;
        }
    }
    return index;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}