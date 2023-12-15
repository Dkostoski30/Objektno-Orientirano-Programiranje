#include <iostream>
#include <cstring>
using namespace std;
#define MAX 50
enum typeC{
    standarden,
    lojalen,
    vip
};
class UserExistsException{
public:
    const char* what()const noexcept{
        return "The user already exists in the list!\n";
    }
};
class Customer{
    char ime[50];
    char e_address[50];
    typeC vid;
    static int popust;
    static int dopolnitelenPopust;
    int brKupeniProizvodi;
public:
    Customer(const char* name="", const char *e_adress="", const typeC vid=standarden, const int brKupeniProizvodi=0): vid(vid), brKupeniProizvodi(brKupeniProizvodi){
        strcpy(this->ime, name);
        strcpy(this->e_address, e_adress);
    }
    const char *getIme() const {
        return ime;
    }
    const char *getEAddress() const {
        return e_address;
    }
    typeC getVid() const {
        return vid;
    }
    void setVid(typeC vid) {
        Customer::vid = vid;
    }
    static int getPopust() {
        return popust;
    }
    static void setDiscount1(int popust) {
        Customer::popust = popust;
    }
    static int getDopolnitelenPopust() {
        return dopolnitelenPopust;
    }
    int getBrKupeniProizvodi() const {
        return brKupeniProizvodi;
    }
    void setBrKupeniProizvodi(int brKupeniProizvodi) {
        Customer::brKupeniProizvodi = brKupeniProizvodi;
    }

    bool operator==(const Customer &rhs) const;

    bool operator!=(const Customer &rhs) const;

    friend ostream &operator<<(ostream &os, const Customer &customer);
};
int Customer::popust=10;
int Customer::dopolnitelenPopust=20;

ostream &operator<<(ostream &os, const Customer &customer) {
    os<<customer.ime<<endl;
    os<<customer.e_address<<endl;
    os<<customer.brKupeniProizvodi<<endl;
    if(customer.vid==lojalen){
        os<<"loyal "<<Customer::popust<<endl;
    }
    else if(customer.vid==vip){
        os<<"vip "<<Customer::dopolnitelenPopust+Customer::popust<<endl;
    }
    else
        os<<"standard 0"<<endl;
    return os;
}

bool Customer::operator==(const Customer &rhs) const {
    return strcmp(e_address, rhs.e_address)==0;
}

bool Customer::operator!=(const Customer &rhs) const {
    return !(rhs == *this);
}

class FINKI_bookstore{
    Customer *customer;
    unsigned int brCustomer;
protected:
    void copy(const FINKI_bookstore& dr){
        brCustomer=dr.brCustomer;
        customer=new Customer[brCustomer];
        for (int i = 0; i < brCustomer; ++i) {
            customer[i]=dr.customer[i];
        }
    }
public:
    FINKI_bookstore(const Customer* customer= nullptr, const unsigned brCustomer=0):brCustomer(brCustomer){
        this->customer=new Customer[brCustomer];
        for (int i = 0; i < brCustomer; ++i) {
            this->customer[i]=customer[i];
        }
    }
    ~FINKI_bookstore(){
        delete[] customer;
    }
    void setCustomers(const Customer* customer, const unsigned brCustomer){
        this->brCustomer=brCustomer;
        this->customer=new Customer[brCustomer];
        for (int i = 0; i < brCustomer; ++i) {
            this->customer[i]=customer[i];
        }
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &bookstore) {
        for (int i = 0; i < bookstore.brCustomer; ++i) {
            cout<<bookstore.customer[i];
        }
        return os;
    }
    FINKI_bookstore& operator+=(const Customer& nov){
        try
        {
            for (int i = 0; i < brCustomer; ++i) {
                if (customer[i] == nov) {
                    throw UserExistsException();
                }
            }
            Customer *tmp = new Customer[brCustomer + 1];
            for (int i = 0; i < brCustomer; ++i) {
                tmp[i] = customer[i];
            }
            tmp[brCustomer++] = nov;
            delete[] customer;
            customer = tmp;
        }
        catch(const UserExistsException & exception) {
            cout<<exception.what();
        }
        return *this;
    }
    void update(){
        for (int i = 0; i < brCustomer; ++i) {
            if(customer[i].getBrKupeniProizvodi()>5 && customer[i].getVid()==standarden){
                customer[i].setVid(lojalen);
            }
            else if(customer[i].getBrKupeniProizvodi()>10 && customer[i].getVid()==lojalen){
                customer[i].setVid(vip);
            }
        }
    }
};
int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
