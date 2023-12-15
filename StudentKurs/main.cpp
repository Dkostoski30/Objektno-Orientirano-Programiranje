#include<iostream>
#include<cstring>
using namespace std;
class BadInputException: public exception{
public:
    const char * poraka() const {
        return "Greshna opisna ocenka\0";
    }
};
class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
    static int MINOCENKA;
public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата
    const char *getIme() const {
        return ime;
    }

    virtual int getOcenka() const {
        return ocenka;
    }

    static int getMinocenka() {
        return MINOCENKA;
    }

    void setOcenka(int ocenka) {
        StudentKurs::ocenka = ocenka;
    }

    bool isDaliUsno() const {
        return daliUsno;
    }

    static int getMax() {
        return MAX;
    }
    static void setMax(int max) {
        MAX = max;
    }
    friend ostream& operator<<(ostream& izlez, const StudentKurs& student){
        izlez<<student.ime<<" --- ";
        if(student.getOcenka()>MAX){
            izlez<<MAX;
        }
        else
        {
            izlez<<student.getOcenka();
        }
        izlez<<endl;
        return izlez;
    }
};

class StudentKursUsno: public StudentKurs{
    char *opisnaOcenka;
protected:
    void copy(const StudentKursUsno& dr){
        opisnaOcenka=new char[strlen(dr.opisnaOcenka)+1];
        strcpy(opisnaOcenka, dr.opisnaOcenka);
    }
public:
    StudentKursUsno(char* ime,int finalenIspit): StudentKurs(ime, finalenIspit){
        daliUsno=true;
        opisnaOcenka="";
    }
    StudentKursUsno(const StudentKursUsno& dr): StudentKurs(dr){
        copy(dr);
    }
    StudentKursUsno& operator=(const StudentKursUsno& dr){
        if(this!=&dr){
            StudentKurs::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    ~StudentKursUsno(){
        delete[] opisnaOcenka;
    }
    StudentKursUsno &operator+=(char *oo)
    {
        //cout<<ime<<"+="<<oo<<endl;
        for(int i = 0; i < strlen(oo); i++)
        {
            if(!isalpha(oo[i]))
            {
                throw BadInputException();
            }
        }
        delete [] opisnaOcenka;
        opisnaOcenka = new char[strlen(oo) + 1];
        strcpy(opisnaOcenka, oo);
        return *this;
    }
    int getOcenka()const{
        if(strcmp(opisnaOcenka, "odlicen\0")==0){
            return ocenka+2;
        }
        else if(strcmp(opisnaOcenka, "dobro\0")==0){
            return ocenka+1;
        }
        else if(strcmp(opisnaOcenka, "losho\0")==0){
            return ocenka-1;
        }
            return ocenka;
    }

};
//вметни го кодот за StudentKursUsno

char* izbrisiCifri(char *string){
    int novBrojac=0;
    char *novString=new char[strlen(string)+1];
    for (int i = 0; i < strlen(string); ++i) {
        if(isalpha(string[i])){
            novString[novBrojac++]=string[i];
        }
    }
    novString[novBrojac]='\0';
    return novString;
}
class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->isDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti()const{
        cout<<"Kursot "<<naziv<<" go polozile: "<<endl;
        for (int i = 0; i < broj; ++i) {
            if(studenti[i]->getOcenka()>=StudentKurs::getMinocenka()){
                cout<<*studenti[i];
            }
        }
    }
    void postaviOpisnaOcenka(const char* ime, char* opisnaOcena){
        //int index=-1;
        for (int i = 0; i < broj; ++i) {
            if(strcmp(studenti[i]->getIme(), ime)==0){
                if(studenti[i]->isDaliUsno()){
                    StudentKursUsno* tmp=dynamic_cast<StudentKursUsno*>(studenti[i]);
                    if(tmp)
                        *tmp+=opisnaOcena;
                }
            }
        }

    }
    //дополни ја класата
};
int StudentKurs::MAX=10;
int StudentKurs::MINOCENKA=6;
int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
        catch(const BadInputException& badInput){
            cout<<badInput.poraka()<<endl;
            programiranje.postaviOpisnaOcenka(ime, izbrisiCifri(opisna));
        }
    }

    StudentKurs::setMax(9);

    programiranje.pecatiStudenti();

}
