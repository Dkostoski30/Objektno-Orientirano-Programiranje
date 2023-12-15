#include <iostream>
#include <cstring>
using namespace std;
class SMS{
    double cenaNaPoraka;
    char broj[14];

protected:
    void copy(const SMS& dr){
        cenaNaPoraka=dr.cenaNaPoraka;
        strcpy(broj, dr.broj);
    }
public:
    SMS(const double cenaNaPoraka=0, const char *broj=""):cenaNaPoraka(cenaNaPoraka){
        strcpy(this->broj, broj);
        this->broj[13]='\0';
    }
    SMS(const SMS& dr){
        copy(dr);
    }
    SMS& operator=(const SMS& dr){
        if(this!=&dr){ copy(dr); }
        return *this;
    }
    virtual double SMS_cena()const=0;
    friend ostream& operator<<(ostream& os, const SMS& poraka){
        os<<"Tel: "<<poraka.broj<<" - cena: "<<poraka.SMS_cena()<<"den."<<endl;
        return os;
    }

    double getCenaNaPoraka() const {
        return cenaNaPoraka;
    }

    void setCenaNaPoraka(double cenaNaPoraka) {
        SMS::cenaNaPoraka = cenaNaPoraka;
    }

    const char *getBroj() const {
        return broj;
    }
};
class RegularSMS: public SMS{
    bool roaming;
    static double rProcent;
    char *msg;
protected:
    void copy(const RegularSMS& dr){
        roaming=dr.roaming;
        msg=new char[strlen(dr.msg)+1];
        strcpy(msg, dr.msg);
    }
public:
    RegularSMS(const char *broj="", const double cenaNaPoraka=0, const char *msg="", const bool roaming=false): SMS(cenaNaPoraka, broj), roaming(roaming){
        this->msg= new char[strlen(msg)];
        strcpy(this->msg, msg);
    }
    RegularSMS(const RegularSMS& dr): SMS(dr){
        copy(dr);
    }
    RegularSMS& operator=(const RegularSMS& dr){
        if(this!=&dr){
            SMS::operator=(dr);
            copy(dr);
        }
        return *this;
    }

    static void set_rProcent(double rProcent) {
        RegularSMS::rProcent = rProcent/100.0;
    }

    double SMS_cena()const{
        int dolzinaPoraka;
        if(strlen(msg)%160==0){
            dolzinaPoraka=strlen(msg)/160;
        }
        else{
            dolzinaPoraka=(strlen(msg)/160)+1;
        }
        if(roaming){
            return getCenaNaPoraka()*(rProcent+1)*dolzinaPoraka;
        }
        else{
            return getCenaNaPoraka()*1.18*dolzinaPoraka;
        }
    }
};
class SpecialSMS: public SMS{
    bool charity;
    static double sProcent;
public:
    SpecialSMS(const char *broj="", const double cenaNaPoraka=0, const bool charity=false): SMS(cenaNaPoraka, broj), charity(charity){}

    static void set_sProcent(double sProcent) {
        SpecialSMS::sProcent = sProcent/100.0;
    }

    double SMS_cena()const{
        double newCena=getCenaNaPoraka();
        if(!charity){
            newCena*=(sProcent+1);
        }
        return newCena;
    }
};
void vkupno_SMS(SMS** poraka, int n){
    int brRegularSMS=0, brSpecialSMS=0;
    double vkRegularCena=0.0, vkSpeciajCena=0.0;
    for (int i = 0; i < n; ++i) {
        RegularSMS* tmp=dynamic_cast<RegularSMS*>(poraka[i]);
        if(tmp!= nullptr) {
            brRegularSMS++;
            vkRegularCena+=tmp->SMS_cena();
        }
        else {
            brSpecialSMS++;
            vkSpeciajCena+=poraka[i]->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<brRegularSMS<<" regularni SMS poraki i nivnata cena e: "<<vkRegularCena<<endl;
    cout<<"Vkupno ima "<<brSpecialSMS<<" specijalni SMS poraki i nivnata cena e: "<<vkSpeciajCena<<endl;

}
double RegularSMS::rProcent=3;
double SpecialSMS::sProcent=1.5;
int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
