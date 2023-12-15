#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
    char *ime;
    char *user;
    int width, height;
protected:
    void copy(const Image& dr){
        ime=new char[strlen(dr.ime)+1];
        user=new char[strlen(dr.user)+1];
        strcpy(ime, dr.ime);
        strcpy(user, dr.user);
        width=dr.width;
        height=dr.height;
    }
public:
    Image(const char* ime="untitled\0", const char* user="unknown\0", const int width=800, const int height=800):width(width), height(height){
        this->ime=new char[strlen(ime)+1];
        this->user=new char[strlen(user)+1];
        strcpy(this->ime, ime);
        strcpy(this->user, user);
    }
    Image(const Image& dr){
        copy(dr);
    }
    Image& operator=(const Image& dr){
        if(this!=&dr){
            copy(dr);
        }
        return *this;
    }
    ~Image(){
        delete[] ime;
        delete[] user;
    }
    virtual int filesize()const{
        return width*height*3;
    }
    char *getIme() const {
        return ime;
    }

    char *getUser() const {
        return user;
    }

    int getWidth() const {
        return width;
    }
    void setWidth(int width) {
        Image::width = width;
    }
    int getHeight() const {
        return height;
    }
    void setHeight(int height) {
        Image::height = height;
    }

    friend ostream &operator<<(ostream &os, const Image &image) {
        os  << image.ime << " " << image.user <<" "<<image.filesize()<<endl;
        return os;
    }
    bool operator>(const Image& dr){
        return filesize()>dr.filesize();
    }
};
class TransparentImage: public Image{
    bool transparency;
public:
    TransparentImage(const char* ime="untitled\0", const char* user="unknown\0", const int width=800, const int height=800, const bool transparency= true):
            Image(ime, user, width, height), transparency(transparency){}
    TransparentImage(const TransparentImage& dr): Image(dr), transparency(dr.transparency){}
    int filesize()const{
        if(transparency){
            return getWidth()*getHeight()*4;
        }
        else{
            return getWidth()*getHeight()+getWidth()*getHeight()/8;
        }
    }
};
class Folder{
    char ime[256];
    char user[51];
    Image *image[100];
    int brImages;
public:
    Folder(const char *ime="untitled\0", const char* user="unknown\0"){
        strcpy(this->ime, ime);
        strcpy(this->user, user);
        brImages=0;
    }
    int foldersize()const{
        int zb=0;
        for (int i = 0; i < brImages && image[i]!= nullptr; ++i) {
            zb+=image[i]->filesize();
        }
        return zb;
    }
    Image* getMaxFile()const{
        int index=0;
        for (int i = 0; i < brImages; ++i) {
            if(image[index]->filesize()<image[i]->filesize()){
                index=i;
            }
        }
        return image[index];
    }
    Folder& operator+=(Image& dr){
        image[brImages++]=&dr;
        return *this;
    }

    Image& operator[](int i){
        if(image[i])
        { return *image[i]; }
    }

    friend ostream &operator<<(ostream &os, const Folder &folder) {
        os<<folder.ime<<" "<<folder.user<<endl<<"--"<<endl;
        for (int i = 0; i < folder.brImages; ++i) {
            os<<*folder.image[i];
        }
        os<<"--"<<endl;
        os<<"Folder size: "<<folder.foldersize()<<endl;
        return os;
    }
};
Folder& max_folder_size(Folder* folder, int n){
    int index=0;
    for (int i = 0; i < n; ++i) {
        if(folder[index].foldersize()<folder[i].foldersize()){
            index=i;
        }
    }
    return folder[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
