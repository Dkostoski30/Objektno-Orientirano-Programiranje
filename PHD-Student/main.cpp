#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::iostream;
class Exception: public std::exception{
public:
    char *poraka()const{
        return "Ne moze da se vnese dadeniot trud\n";
    }
};
class PhDStudentNotFound: public std::exception{
    int index;
public:
    PhDStudentNotFound(const int index=0):index(index){}
    void poraka()const{
        cout<<"Ne postoi PhD student so index "<<index<<endl;
    }
};
class Trud{
    char tip;

    unsigned int godina;
public:
    Trud(const char tip='0', const unsigned int godina=0):godina(godina), tip(tip){}
    friend std::istream& operator>>(std::istream& is, Trud& trud){
        is>>trud.tip>>trud.godina;
        return is;
    }

    char getTip() const {
        return tip;
    }

    void setTip(char tip) {
        Trud::tip = tip;
    }


    unsigned int getGodina() const {
        return godina;
    }

    void setGodina(unsigned int godina) {
        Trud::godina = godina;
    }
};
class Student{
    char ime[31];
    int index;
    int godina;
    int *ocenki;
    int brOcenki;
protected:
    void copy(const Student& dr){
        index=dr.index;
        strcpy(ime, dr.ime);
        godina=dr.godina;
        brOcenki=dr.brOcenki;
        ocenki=new int[brOcenki];
        for (int i = 0; i < brOcenki; ++i) {
            ocenki[i]=dr.ocenki[i];
        }
    }
public:
    Student(const char* ime="", const int index=0, const int godina=0, const int *oceni= nullptr, const int brOceni=0):
            index(index), brOcenki(brOceni), godina(godina){
        strcpy(this->ime, ime);
        this->ocenki=new int[brOceni];
        for (int i = 0; i < brOceni; ++i) {
            this->ocenki[i]=oceni[i];
        }
    }
    Student(const Student& dr){
        copy(dr);
    }
    Student& operator=(const Student& dr){
        if(this!=&dr)
        { copy(dr); }
        return *this;
    }
    ~Student(){
        delete[] ocenki;
    }
    virtual double rang()const{
        double zb=0.0;
        //int br=0;
        for (int i = 0; i < brOcenki; ++i) {

            zb +=ocenki[i];
        }
        return zb/brOcenki;
    }

    const char *getIme() const {
        return ime;
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        Student::index = index;
    }

    int getGodina() const {
        return godina;
    }

    void setGodina(int godina) {
        Student::godina = godina;
    }

    int *getOcenki() const {
        return ocenki;
    }

    void setOcenki(int *ocenki) {
        Student::ocenki = ocenki;
    }

    int getBrOcenki() const {
        return brOcenki;
    }

    void setBrOcenki(int brOcenki) {
        Student::brOcenki = brOcenki;
    }

    friend std::ostream &operator<<(std::ostream &os, const Student &student) {
        os<<student.index<<" "<<student.ime<<" "<<student.godina<<" "<<student.rang()<<endl;
        return os;
    }
};
class PhDStudent: public Student{
    Trud* trud;
    static int cTrud, jTrud;
    int brTrudovi;
protected:
    void copy(const PhDStudent& dr){
        brTrudovi=dr.brTrudovi;
        trud=new Trud[brTrudovi];
        for (int i = 0; i < brTrudovi; ++i) {
            trud[i]=dr.trud[i];
        }
    }
public:
    PhDStudent(const char* ime="", const int index=0, const int godina=0, const int *oceni= nullptr, const int brOceni=0, const Trud* trud= nullptr, const int brTrudovi=0):
            Student(ime, index, godina, oceni, brOceni), brTrudovi(brTrudovi){
        this->trud=new Trud[brTrudovi];
        for (int i = 0; i < brTrudovi; ++i) {
            try {
                *this += trud[i];
            }
            catch (const Exception &exception) {
                cout << exception.poraka();
            }
        }
    }
    PhDStudent(const PhDStudent& dr): Student(dr){
        copy(dr);
    }
    PhDStudent& operator=(const PhDStudent& dr){
        if(this!=&dr){
            Student::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    ~PhDStudent(){
        delete[] trud;
    }

    Trud *getTrud() const {
        return trud;
    }

    void setTrud(Trud *trud) {
        PhDStudent::trud = trud;
    }

    static int getCTrud() {
        return cTrud;
    }

    static void setCTrud(int cTrud) {
        PhDStudent::cTrud = cTrud;
    }

    static int getJTrud() {
        return jTrud;
    }

    static void setJTrud(int jTrud) {
        PhDStudent::jTrud = jTrud;
    }

    int getBrTrudovi() const {
        return brTrudovi;
    }

    void setBrTrudovi(int brTrudovi) {
        PhDStudent::brTrudovi = brTrudovi;
    }

    double rang()const{
        double zb=Student::rang();
        for (int i = 0; i < brTrudovi; ++i) {
            if(tolower(trud[i].getTip())=='c'){
                zb+=cTrud;
            }
            else if(tolower(trud[i].getTip())=='j'){
                zb+=jTrud;
            }
        }
        return zb;
    }
    PhDStudent& operator+=(const Trud& nov){
        if(nov.getGodina()<getGodina()){
            throw Exception();
        }
        Trud* tmp=new Trud[brTrudovi+1];
        for (int i = 0; i < brTrudovi; ++i) {
            tmp[i]=trud[i];
        }
        tmp[brTrudovi++]=nov;
        delete[] trud;
        trud=tmp;
        return *this;
    }
};
int PhDStudent::cTrud=1;
int PhDStudent::jTrud=3;
int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool flag= true;
        for (int i = 0; i < m; ++i) {
            PhDStudent* tmp=dynamic_cast<PhDStudent*>(niza[i]);
            if(indeks==niza[i]->getIndex() && tmp!= nullptr){
                flag=false;
                try {
                    *tmp += t;
                }
                catch (const Exception& exception) {
                    cout<<exception.poraka()<<endl;
                }
            }
        }
        if(flag){
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

        bool flag= true;
        for (int i = 0; i < m; ++i) {
            PhDStudent* tmp=dynamic_cast<PhDStudent*>(niza[i]);
            if(indeks==niza[i]->getIndex() && tmp!= nullptr){
                flag=false;
                try {
                    *tmp += t;
                }
                catch (const Exception& exception) {
                    cout<<exception.poraka()<<endl;
                }
            }
        }
        if(flag){
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        bool flag= true;
        for (int i = 0; i < m; ++i) {
            PhDStudent* tmp=dynamic_cast<PhDStudent*>(niza[i]);
            if(indeks==niza[i]->getIndex() && tmp!= nullptr){
                flag=false;
                try {
                    *tmp += t;
                }
                catch (const Exception& exception) {
                    cout<<exception.poraka();
                }
            }
        }
        if(flag){
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setCTrud(conf);
        PhDStudent::setJTrud(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    return 0;
}