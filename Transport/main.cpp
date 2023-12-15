#include <iostream>
#include <cstring>
using namespace std;
// вашиот код треба да биде тука
class Transport{
    char destinacija[20];
    int osnovnaCena, rastojanie;
public:
    Transport(const char *destinacija="", const int osnovnaCena=0, const int rastojanije=0):osnovnaCena(osnovnaCena), rastojanie(rastojanije){
        strcpy(this->destinacija, destinacija);
    }
    virtual int cenaTransport()const=0;

    const char *getDestinacija() const {
        return destinacija;
    }

    int getOsnovnaCena() const {
        return osnovnaCena;
    }

    void setOsnovnaCena(int osnovnaCena) {
        Transport::osnovnaCena = osnovnaCena;
    }

    int getRastojanie() const {
        return rastojanie;
    }

    void setRastojanie(int rastojanie) {
        Transport::rastojanie = rastojanie;
    }
    bool operator<(const Transport& dr) const{
        return rastojanie<dr.rastojanie;
    }

    friend ostream &operator<<(ostream &os, const Transport &transport) {
        os << transport.destinacija <<" "<< transport.rastojanie << " "
           << transport.cenaTransport();
        return os;
    }
};
class AvtomobilTransport: public Transport{
    bool shofer;
public:
    AvtomobilTransport(const char *destinacija="", const int osnovnaCena=0, const int rastojanije=0, const bool shofer= false):
            Transport(destinacija, osnovnaCena, rastojanije), shofer(shofer){}
    int cenaTransport()const{
        int newCena=getOsnovnaCena();
        if(shofer){
            newCena*=1.2;
        }
        return newCena;
    }

    bool isShofer() const {
        return shofer;
    }

    void setShofer(bool shofer) {
        AvtomobilTransport::shofer = shofer;
    }
};
class KombeTransport: public Transport{
    int brPatnici;
public:
    KombeTransport(const char *destinacija="", const int osnovnaCena=0, const int rastojanije=0, const int brPatnici=0):
            Transport(destinacija, osnovnaCena, rastojanije), brPatnici(brPatnici){}
    int cenaTransport()const{
        return getOsnovnaCena()-brPatnici*200;;
    }

    int getBrPatnici() const {
        return brPatnici;
    }

    void setBrPatnici(int brPatnici) {
        KombeTransport::brPatnici = brPatnici;
    }
};

void pecatiPoloshiPonudi(Transport ** niza, int n, Transport &nov){
    Transport **temp=new Transport*[n];
    int brojac=0;
    for (int i = 0; i < n; ++i) {
        if(nov.cenaTransport()<niza[i]->cenaTransport())
        {
            temp[brojac++]=niza[i];
        }
    }
    n=brojac;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (*temp[j]<*temp[i]) {
                Transport& tmp=*temp[i];
                temp[i]=temp[j];
                temp[j]=&tmp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout<<*temp[i]<<endl;
    }

}
int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    //ponudi= nullptr;
    return 0;
}
