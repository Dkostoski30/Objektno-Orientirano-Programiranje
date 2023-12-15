#include<iostream>
#include<cstring>
using namespace std;

//место за вашиот код
class Delo{
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(const char *ime="", const int godina=0, const char *zemja=""):godina(godina){
        strcpy(this->ime, ime);
        strcpy(this->zemja, zemja);
    }
    const char *getIme() const {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    void setGodina(int godina) {
        Delo::godina = godina;
    }

    const char *getZemja() const {
        return zemja;
    }
    bool operator==(const Delo &rhs) const {
        return strcmp(ime, rhs.ime)==0;
    }
};
class Pretstava{
    Delo delo;
    int brKarti;
    char data[15];
public:
    Pretstava(const Delo& delo=nullptr, const int brKarti=0, const char data[]=""): delo(delo), brKarti(brKarti){
        strcpy(this->data, data);
    }
    const Delo &getDelo() const {
        return delo;
    }
    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }
    int getBrKarti() const {
        return brKarti;
    }
    void setBrKarti(int brKarti) {
        Pretstava::brKarti = brKarti;
    }

    const char *getData() const {
        return data;
    }
    virtual int cena(){
        int cena=0;
        if(delo.getGodina()>=1901){
            cena+=50;
        }
        else if(delo.getGodina()<1901 && delo.getGodina()>=1801){
            cena +=75;
        }
        else if(delo.getGodina()<1801){
            cena+=100;
        }
        if(strcmp(delo.getZemja(),"Italija")==0){
            cena+=100;
        }
        else if(strcmp(delo.getZemja(),"Rusija")==0){
            cena+=150;
        }
        else
        {
            cena+=80;
        }
        return cena;
    }
};
class Balet: public Pretstava{
    static int cenaBalet;
public:
    Balet(const Delo& delo=nullptr, const int brKarti=0, const char data[]=""): Pretstava(delo, brKarti, data){}
    static int getCenaBalet() {
        return cenaBalet;
    }
    static void setCenaBalet(int cenaBalet) {
        Balet::cenaBalet = cenaBalet;
    }
    int cena(){
        return (Pretstava::cena()+cenaBalet);
    }
};
class Opera: public Pretstava{
public:
    Opera(const Delo& delo=nullptr, const int brKarti=0, const char data[]=""): Pretstava(delo, brKarti, data){}
};
int Balet::cenaBalet=150;
int prihod(Pretstava** pretstava, int n){
    int vkPrihod=0;
    for (int i = 0; i < n; ++i) {
        vkPrihod+=pretstava[i]->cena()*pretstava[i]->getBrKarti();
    }
    return vkPrihod;
}
int brojPretstaviNaDelo(Pretstava** pretstava, int n, const Delo& delo)
{
    int counter=0;
    for (int i = 0; i < n; ++i) {
        if(pretstava[i]->getDelo()==delo){
            counter++;
        }
    }
    return counter;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
