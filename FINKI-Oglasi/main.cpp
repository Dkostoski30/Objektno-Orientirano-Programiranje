#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

//место за вашиот код
class NegativnaVrednost{
public:
    static const char* what()noexcept{
        return "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!";
    }
};
class Oglas{
    char naslov[50], kategorija[30], opis[100];
    double cena;//evra
public:
    Oglas(const char* naslov="", const char* kategorija="", const char* opis="", const double cena=0.0):cena(cena){
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
    }

    const char *getNaslov() const {
        return naslov;
    }

    const char *getKategorija() const {
        return kategorija;
    }

    const char *getOpis() const {
        return opis;
    }

    double getCena() const {
        return cena;
    }

    void setCena(double cena) {
        Oglas::cena = cena;
    }

    bool operator>(const Oglas &rhs) const {
        return cena > rhs.cena;
    }

    friend ostream &operator<<(ostream &os, const Oglas &oglas) {
        os<<oglas.naslov<<endl;
        os<<oglas.opis<<endl;
        os<<oglas.cena<<" evra"<<endl;
        return os;
    }
};
class Oglasnik{
    char ime[20];
    Oglas* oglas;
    unsigned int brOglasi;
protected:
    void copy(const Oglasnik &dr){
        strcpy(ime, dr.ime);
        brOglasi=dr.brOglasi;
        oglas=new Oglas[brOglasi];
        for (int i = 0; i < brOglasi; ++i) {
            oglas[i]=dr.oglas[i];
        }
    }
public:
    Oglasnik(const char *ime="", const Oglas* oglas= nullptr, const unsigned int brOglasi=0):brOglasi(brOglasi){
        strcpy(Oglasnik::ime, ime);
        Oglasnik::oglas=new Oglas[brOglasi];
        for (int i = 0; i < brOglasi; ++i) {
            Oglasnik::oglas[i]=oglas[i];
        }
    }
    Oglasnik (const Oglasnik& dr) {
        copy(dr);
    }
    Oglasnik& operator= (const Oglasnik& dr) {
        if(this!=&dr){ copy(dr); }
        return *this;
    }
    ~Oglasnik(){
        delete[] oglas;
    }
    Oglasnik& operator+=(const Oglas &dr){
        try{
            if(dr.getCena()<0){throw NegativnaVrednost();}

            Oglas* tmp=new Oglas[brOglasi+1];
            for (int i = 0; i < brOglasi; ++i) {
                tmp[i]=oglas[i];
            }
            tmp[brOglasi++]=dr;
            delete[] oglas;
            oglas=tmp;
        }
        catch (const NegativnaVrednost& negativnaVrednost) {
            cout<<NegativnaVrednost::what()<<endl;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Oglasnik &oglasnik) {
        os  << oglasnik.ime << endl;
        for (int i = 0; i < oglasnik.brOglasi; ++i) {
            os<<oglasnik.oglas[i]<<endl;
        }
        return os;
    }
    void najniskaCena()const{
        int index=0;
        for (int i = 0; i < brOglasi; ++i) {
            if(oglas[index]>oglas[i])
                index=i;
        }
        cout<<oglas[index]<<endl;
    };
    void oglasiOdKategorija(const char *kategorija)const{
        for (int i = 0; i < brOglasi; ++i) {
            if(strcmp(oglas[i].getKategorija(), kategorija)==0){
                cout<<oglas[i]<<endl;
            }
        }
    }
};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
