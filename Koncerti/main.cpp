#include <iostream>
#include <cstring>
using namespace std;
class Koncert{
    char naziv[20], lokacija[20];
    float cenaBilet;
    static double sezonskiPopust;
public:
  Koncert(const char *naziv="", const char *lokacija="", const float cena=0.0f):cenaBilet(cena){
      strcpy(this->naziv, naziv);
      strcpy(this->lokacija, lokacija);
  }

    const char *getNaziv() const {
        return naziv;
    }

    const char *getLokacija() const {
        return lokacija;
    }

    float getCenaBilet() const {
        return cenaBilet;
    }

    void setCenaBilet(float cena) {
        Koncert::cenaBilet = cena;
    }

    static double getSezonskiPopust() {
        return sezonskiPopust;
    }

    static void setSezonskiPopust(double popust) {
        Koncert::sezonskiPopust = popust;
    }
    virtual double cena()const{
      return double(cenaBilet)-(cenaBilet*getSezonskiPopust());
  }

    friend ostream &operator<<(ostream &os, const Koncert &koncert) {
        os << koncert.naziv << " " << koncert.cena();
        return os;
    }

    bool operator==(const Koncert &rhs) const;
};


bool Koncert::operator==(const Koncert &rhs) const {
    return strcmp(naziv, rhs.naziv)==0;
}


class ElektronskiKoncert: public Koncert{
    char *DJ;
    double vremetraenje;
    bool dnevna;
    void copy(const ElektronskiKoncert& dr){
        DJ=new char[strlen(dr.DJ)+1];
        strcpy(DJ, dr.DJ);
        vremetraenje=dr.vremetraenje;
        dnevna=dr.dnevna;
    }
public:
    ElektronskiKoncert(const char *naziv="", const char *lokacija="", const float cena=0.0, const char* DJ="", const double vremetraenje=0.0, const bool dnevna=false):
            Koncert(naziv, lokacija, cena), vremetraenje(vremetraenje), dnevna(dnevna){
        this->DJ=new char[strlen(DJ)+1];
        strcpy(this->DJ, DJ);
    }
    ElektronskiKoncert(const ElektronskiKoncert& dr): Koncert(dr), vremetraenje(dr.vremetraenje), dnevna(dr.dnevna){
        copy(dr);
    }
    ElektronskiKoncert& operator=(const ElektronskiKoncert& dr){
        if(this!=&dr){
            Koncert::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    ~ElektronskiKoncert(){
        delete[] DJ;
    }

    char *getDj() const {
        return DJ;
    }

    void setDj(char *dj) {
        DJ = dj;
    }

    double getVremetraenje() const {
        return vremetraenje;
    }

    void setVremetraenje(double vremetraenje) {
        ElektronskiKoncert::vremetraenje = vremetraenje;
    }

    bool isDnevna() const {
        return dnevna;
    }

    void setDnevna(bool dnevna) {
        ElektronskiKoncert::dnevna = dnevna;
    }

    double cena()const{
       double newCena=Koncert::cena();
      // cout<<"Za "<<getNaziv()<<"pocetna cena so popust e: "<<newCena;
        if(vremetraenje>5.0 && vremetraenje<=7.0){
            newCena+=150.0;
            //cout<<endl<<"Se dodava 150"<<endl;
        }
        else if(vremetraenje>7.0){
            newCena+=360.0;
            //cout<<endl<<"Se dodava 150"<<endl;
        }
        if(isDnevna()){
            newCena-=50.0;
           // cout<<endl<<"Se odzema 50"<<endl;
        }
        else {
            newCena+=100.0;
            //cout<<endl<<"Se dodava 100"<<endl;
        }
        return newCena;
    }
};
void najskapKoncert(Koncert ** koncerti, int n){
    int index=0, counter=0;
    for (int i = 0; i < n; ++i) {
        Koncert *tmp=dynamic_cast<ElektronskiKoncert* >(koncerti[i]);
        if(tmp!= nullptr){counter++;}
        if(koncerti[index]->cena()<koncerti[i]->cena()){
            index=i;
        }
    }
    cout<<"Najskap koncert: "<<*koncerti[index]<<endl;
    cout<<"Elektronski koncerti: "<<counter<<" od vkupno "<<n<<endl;
}
bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    bool flag=false;
    for (int i = 0; i < n; ++i) {
        if(elektronski){
            ElektronskiKoncert *tmp=dynamic_cast<ElektronskiKoncert* >(koncerti[i]);
            if(tmp!= nullptr && strcmp(tmp->getNaziv(), naziv)==0){
                cout<<*tmp<<endl;
                flag= true;
                break;
            }
        }
        else{
            if(strcmp(koncerti[i]->getNaziv(), naziv)==0){
                cout<<*koncerti[i]<<endl;
                flag= true;
                break;
            }
        }
    }
    return flag;
}
double Koncert::sezonskiPopust=0.2;
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
