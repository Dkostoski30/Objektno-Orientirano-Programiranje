#include <iostream>
#include <cstring>

using namespace std;
enum tip{
    smartphone,
    laptop
};
class InvalidProductionDate: public std::exception{
    char *poraka;
public:
    InvalidProductionDate(const char* poraka=""){
        this->poraka=new char[strlen(poraka)+1];
        strcpy(this->poraka, poraka);
    }
    ~InvalidProductionDate(){
        delete[] poraka;
    }
    char *what()const noexcept {
        return poraka;
    }
};
class Device{
    char name[100];
    tip typeOfDevice;
    static double pocetniCasovi;
    unsigned int godinaProizvodstvo;
public:
    Device(const char *name="", const tip typeOfDevice=smartphone, const int godinaProizvodstvo=0): typeOfDevice(typeOfDevice), godinaProizvodstvo(godinaProizvodstvo){
        strcpy(this->name, name);
    }

    static double getPocetniCasovi() {
        return pocetniCasovi;
    }

    static void setPocetniCasovi(double pocetniCasovi) {
        Device::pocetniCasovi = pocetniCasovi;
    }

    const char *getName() const;

    tip getTypeOfDevice() const;

    void setTypeOfDevice(tip typeOfDevice);

    unsigned int getGodinaProizvodstvo() const;

    void setGodinaProizvodstvo(unsigned int godinaProizvodstvo);

    double proverka()const{
        double pr=pocetniCasovi;
        if(godinaProizvodstvo>2015){
            pr+=2.0;

        }
        if(typeOfDevice==laptop){
            pr+=2.0;
        }
        return pr;
    }

    friend ostream &operator<<(ostream &os, const Device &device) {
        os<<device.name<<endl;
        if(device.typeOfDevice==laptop)
            os<<"Laptop"<<" ";
        else
            os<<"Mobilen ";
        os<<device.proverka();
        return os;
    }

};
double Device::pocetniCasovi=1.0;

const char *Device::getName() const {
    return name;
}

tip Device::getTypeOfDevice() const {
    return typeOfDevice;
}

void Device::setTypeOfDevice(tip typeOfDevice) {
    Device::typeOfDevice = typeOfDevice;
}

unsigned int Device::getGodinaProizvodstvo() const {
    return godinaProizvodstvo;
}

void Device::setGodinaProizvodstvo(unsigned int godinaProizvodstvo) {
    Device::godinaProizvodstvo = godinaProizvodstvo;
}

class MobileServis{
    char adress[100];
    Device *device;
    unsigned int numOfDevices;
protected:
    void copy(const MobileServis& dr){
        strcpy(adress, dr.adress);
        numOfDevices=dr.numOfDevices;
        device=new Device[numOfDevices];
        for (int i = 0; i < numOfDevices; ++i) {
            device[i]=dr.device[i];
        }
    }
public:
    MobileServis(const char* adress="", const Device* device= nullptr, const unsigned int numOfDevices=0):numOfDevices(numOfDevices){
        strcpy(this->adress, adress);
        this->device=new Device[numOfDevices];
        for (int i = 0; i < numOfDevices; ++i) {
            this->device[i]=device[i];
        }
    }
    MobileServis(const MobileServis& dr){
        copy(dr);
    }
    MobileServis& operator=(const MobileServis& dr){
        if(this!=&dr){ copy(dr); }
        return *this;
    }
    ~MobileServis(){
        delete[] device;
    }
    MobileServis& operator+=(const Device& dr){

        try
        {
            if(dr.getGodinaProizvodstvo()>2019 || dr.getGodinaProizvodstvo()<2000) {
                throw InvalidProductionDate();
            }
            Device* tmp=new Device[numOfDevices+1];
            for (int i = 0; i < numOfDevices; ++i) {
                tmp[i]=device[i];
            }
            tmp[numOfDevices++]=dr;
            delete[] device;
            device=tmp;
            return *this;
        }
        catch (const InvalidProductionDate& e) {
            // handle the exception
            cout<<"Невалидна година на производство"<<endl;
        }
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adress<<endl;
        for (int i = 0; i < numOfDevices; ++i) {
            cout<<device[i]<<endl;
        }
    }
};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

