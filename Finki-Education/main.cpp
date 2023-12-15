#include <iostream>
#include <cstring>
using namespace std;
class Book {
    char isbn[20], title[50], author[30];
    double price;
public:
    Book(const char *isbn = "", const char *title = "", const char *author = "", const double price = 0.0) : price(
            price) {
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
    }

    virtual double bookPrice() const = 0;


    bool operator>(const Book &rhs) const {
        return bookPrice() > rhs.bookPrice();
    }

    const char *getIsbn() const {
        return isbn;
    }
    void setISBN(const char* isbn){
        strcpy(this->isbn, isbn);
    }
    const char *getTitle() const {
        return title;
    }

    const char *getAuthor() const {
        return author;
    }

    const double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        Book::price = price;
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os  << book.isbn << ": " << book.title << ", " << book.author;
        os<<" "<<book.bookPrice()<<endl;
        return os;
    }
};
class OnlineBook: public Book{
    char *url;
    unsigned int size;
    void copy(const OnlineBook& dr){
        url=new char[strlen(dr.url)+1];
        strcpy(url, dr.url);
        size=dr.size;
    }
public:
    OnlineBook(const char *isbn = "", const char *title = "", const char *author = "", const double price = 0.0, const char* url="", const unsigned int size=0):
            Book(isbn, title, author, price), size(size){
        this->url=new char[strlen(url)+1];
        strcpy(this->url, url);
    }
    OnlineBook(const OnlineBook& dr): Book(dr){
        copy(dr);
    }
    OnlineBook& operator=(const OnlineBook& dr){
        if(this!=&dr){
            Book::operator=(dr);
            copy(dr);
        }
        return *this;
    }
    ~OnlineBook(){
        delete[] url;
    }
    double bookPrice()const{
        if(size>=20){
            return getPrice()*1.2;
        }
        else
            return getPrice();
    }
};
class PrintBook: public Book{
    bool available;
    double weight;
public:
    PrintBook(const char *isbn = "", const char *title = "", const char *author = "", const double price = 0.0, const bool available=false, double weight=0.0):
            Book(isbn, title, author, price), available(available), weight(weight){}
    double bookPrice()const{
        if(weight>=0.7){
            return getPrice()*1.15;
        }
        else
            return getPrice();
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool available) {
        PrintBook::available = available;
    }

    double getWeight() const {
        return weight;
    }

    void setWeight(double weight) {
        PrintBook::weight = weight;
    }
};
void mostExpensiveBook (Book** book, int n){
    int index=0;
    Book &najskapa=*book[0];
    int online=0, printed=0;
    cout<<"FINKI-Education"<<endl;
    for (int i = 0; i < n; ++i) {
        Book *tmp=dynamic_cast<OnlineBook*>(book[i]);
        if(tmp== nullptr){
            printed++;
        }
        else
            online++;
        if(book[i]->bookPrice()>book[index]->bookPrice()){
            index=i;
            najskapa=*book[i];
        }
    }
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*book[index]<<endl;
}
    int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
