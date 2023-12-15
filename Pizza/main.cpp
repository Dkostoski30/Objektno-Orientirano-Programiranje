#include <cstring>
#include <iostream>
using namespace std;
enum Size{Mala, Golema, Familijarna=2};
// Your Code goes here
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;
public:
    Pizza(char *ime="", char *sostojki="", float cena=0.0f)
    {
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);
        this->cena=cena;
    }
    ~Pizza(){}
    virtual float price()const=0;
    bool operator<(Pizza &dr) const
    {
        return price()<dr.price();
    }

};
class FlatPizza : public Pizza{
protected:
    Size size1;
public:
    FlatPizza(char *ime="", char *sostojki="", float cena=0.0f, Size size1=Mala):
            Pizza(ime, sostojki, cena), size1(size1){}

    float price()const
    {
        if(size1==Mala)
        {
            return cena*1.1;
        }
        else if(size1==Golema)
        {
            return cena*1.2;
        }
        else if(size1==Familijarna)
        {
            return cena*1.3;
        }
    }
    friend ostream& operator<<(ostream& out, FlatPizza& dr)
    {
        out<<dr.ime<<": "<<dr.sostojki<<", ";
        if(dr.size1==Mala)
        {
            out<<"small - ";
        }
        else if(dr.size1==Golema)
        {
            out<<"big - ";
        }
        else if(dr.size1==Familijarna)
        {
            out<<"family - ";
        }

        out<<dr.price()<<endl;
        return out;
    }
};
class FoldedPizza : public Pizza{
protected:
    bool belobrashno;
public:
    FoldedPizza(char *ime="", char *sostojki="", float cena=0.0f, bool belobrashno=true) :
            Pizza(ime, sostojki, cena)
    {
        this->belobrashno=belobrashno;
    }
    void setWhiteFlour(bool belobrashno)
    {
        this->belobrashno=belobrashno;
    }
    float price()const
    {
        if(belobrashno)
        {
            return cena*1.1;
        }
            return cena*1.3;
    }
    friend ostream& operator<<(ostream& out, FoldedPizza& dr)
    {
        out<<dr.ime<<": "<<dr.sostojki<<", ";
        if(dr.belobrashno)
        {
            out<<"wf - ";
        }
        else{
            out<<"nwf - ";
        }
        out<<dr.price()<<endl;
        return out;
    }
};

// Testing
void expensivePizza(Pizza *p[], int n)
{
    int min=0;
    for (int i = 0; i < n; ++i) {
        if(p[i]->price() > p[min]->price())
        {
            min=i;
        }
    }

    FoldedPizza* tmp=dynamic_cast<FoldedPizza*>(p[min]);
    if(tmp){
        cout<<*tmp;
    }
    else{
        FlatPizza *tmp2=dynamic_cast<FlatPizza*>(p[min]);
        cout<<*tmp2;
    }
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
