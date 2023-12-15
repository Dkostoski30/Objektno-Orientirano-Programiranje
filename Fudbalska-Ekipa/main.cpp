#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class FudbalskaEkipa{
    char trener[100];
    int brGolovi[10];//last 10 games
protected:
    void copy(const FudbalskaEkipa& dr){
        strcpy(trener, dr.trener);

        for (int i = 0; i < 10; ++i) {
            brGolovi[i]=dr.brGolovi[i];
        }
    }
public:
    FudbalskaEkipa(const char *trener="", const int *brGolovi=nullptr) {
        strcpy(this->trener, trener);

        for (int i = 0; i < 10; ++i) {
            this->brGolovi[i] = brGolovi[i];
        }
    }

    const char *getTrener() const {
        return trener;
    }

    int sumOfGolovi()const{
        int a=0;
        for (int i = 0; i < 10; ++i) {
            a+=brGolovi[i];
        }
        return a;
    }
    FudbalskaEkipa& operator+=(const int goloj){
        for (int i = 1; i < 10; ++i) {
            brGolovi[i-1]=brGolovi[i];
        }
        brGolovi[9]=goloj;
        return *this;
    }
    virtual int uspeh() =0;
    virtual char *getIme()=0;
    friend ostream&operator<<(ostream&out, FudbalskaEkipa &k)
    {
        out<<k.getIme()<<endl;
        out<<k.trener<<endl;
        out<<k.uspeh()<<endl;
        return out;
    }
};
class Klub: public FudbalskaEkipa{
    char *ime;
    int brTituli;
protected:
    void copy(const Klub& dr){
        ime=new char[strlen(dr.ime)+1];
        strcpy(ime, dr.ime);
        brTituli=dr.brTituli;
    }
public:
    Klub(const char *trener="", const int *brGolovi=nullptr, const char* ime="", int brTituli=0):FudbalskaEkipa(trener, brGolovi), brTituli(brTituli){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
    }
    ~Klub(){
        delete[] ime;
    }
    int uspeh(){
        return sumOfGolovi()*3+brTituli*1000;
    }
    char *getIme(){
        return ime;
    }

};
class Reprezentacija: public FudbalskaEkipa{
    char *ime;
    int brNastapi;
protected:
    void copy(const Reprezentacija& dr){
        ime=new char[strlen(dr.ime)+1];
        strcpy(ime, dr.ime);
        brNastapi=dr.brNastapi;
    }
public:
    Reprezentacija(const char *trener="", const int *brGolovi=nullptr, const char* ime="", const int brNastapi=0):
            FudbalskaEkipa(trener, brGolovi), brNastapi(brNastapi){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
    }
    Reprezentacija& operator+=(int goloj){
        FudbalskaEkipa::operator+=(goloj);
        return *this;
    }
    ~Reprezentacija(){
        delete[] ime;
    }
    char *getIme(){
        return ime;
    }
    int uspeh(){
        return sumOfGolovi()*3+brNastapi*50;
    }
    ostream& operator<<(ostream& out){
        out << this->ime << endl;
        out << static_cast<const FudbalskaEkipa*>(this); // Call the base class stream output operator
        out << "Broj tituli: " << this->brNastapi << endl;
        return out;
    }
    //generate a derived ostream operator
};
void najdobarTrener(FudbalskaEkipa** ekipa, int n){
    int index=0;
    for (int i = 1; i < n; ++i) {
        if(ekipa[i]->uspeh()>ekipa[index]->uspeh()){
            index=i;
        }
    }
    cout<<*ekipa[index]<<endl;
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}