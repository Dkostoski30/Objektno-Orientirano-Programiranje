#include<iostream>
#include<cstring>
using namespace std;
class OutOfBoundException: public exception{
public:
    const char* poraka(){
        return "Brojot na pin kodovi ne moze da go nadmine dozvolenoto\0";
    }
};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    const static int P;
public:
    Karticka(char* smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    bool getDopolnitelenPin()const{
        return povekjePin;
    }
    virtual int tezinaProbivanje()const{
        int counter=0;
        int temp=pin;
        while(temp){
            temp/=10;
            counter++;
        }
        return counter;
    }
    friend ostream& operator<<(ostream& izlez, Karticka& karticka){
        izlez<<karticka.smetka<<": "<<karticka.tezinaProbivanje();
        return izlez;
    }

    const char *getSmetka() const {
        return smetka;
    }
    static int getP(){
        return P;
    }
    int getPin() const {
        return pin;
    }

    void setPin(int pin) {
        Karticka::pin = pin;
    }


    virtual ~Karticka(){}
    // дополниете ја класата
};

//вметнете го кодот за SpecijalnaKarticka

class SpecijalnaKarticka: public Karticka{
    int *dopolnitelenPin;
    int brPins;
protected:
    void copy(const SpecijalnaKarticka& dr){
        dopolnitelenPin=new int[dr.brPins];
        brPins=dr.brPins;
        for (int i = 0; i < brPins; ++i) {
            dopolnitelenPin[i]=dr.dopolnitelenPin[i];
        }
    }
public:
    SpecijalnaKarticka(char* smetka, int pin): Karticka(smetka, pin){
        this->dopolnitelenPin= nullptr;
        this->povekjePin=true;
        this->brPins=0;
    }
    SpecijalnaKarticka(const SpecijalnaKarticka& dr): Karticka(dr){
        copy(dr);
    }
    SpecijalnaKarticka& operator=(const SpecijalnaKarticka& dr){
        if(this!=&dr){
            Karticka::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    ~SpecijalnaKarticka(){
        delete[] dopolnitelenPin;
    }

    int tezinaProbivanje()const{
        return Karticka::tezinaProbivanje()+brPins;
    }
    SpecijalnaKarticka& operator+=(const int pin){
        if(brPins==getP())
            throw OutOfBoundException();
        int *tmp = new int[brPins + 1];
        for (int i = 0; i < brPins; ++i) {
            tmp[i] = dopolnitelenPin[i];
        }
        tmp[brPins++] = pin;
        delete[] dopolnitelenPin;
        dopolnitelenPin = tmp;
        povekjePin=true;
        return *this;
    }
};
const int Karticka::P=4;


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата
    static void setLIMIT(int x){
        LIMIT=x;
    }
    static int getLIMIT(){
        return LIMIT;
    }
    void pecatiKarticki()const{
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite: "<<endl;
        for (int i = 0; i < broj; ++i) {
            if(karticki[i]->tezinaProbivanje()<=LIMIT){
                cout<<*karticki[i]<<endl;
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for (int i = 0; i < broj; ++i) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka *tmp=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(tmp!= nullptr)
                    *tmp += novPin;
            }
        }
    }
};
int Banka::LIMIT=0;


int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        try {
            cin>>smetka>>pin;
            komercijalna.dodadiDopolnitelenPin(smetka, pin);
        }
        catch (OutOfBoundException& exception) {
            cout<<exception.poraka();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
