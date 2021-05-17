#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

bool oyunSonu;
const int genislik=25;
const int yukseklik=25;
int x, y, yemisX, yemisY, puan;
enum yonler{DUR=0, SOL, SAG, YUKARI, ASAGI};

int kuyrukX[100];
int kuyrukY[100];
int kuyrukSayisi;

yonler dir;

void kur(){
    oyunSonu=false;
    dir=DUR;

    x=genislik/2;
    y=yukseklik/2;

    yemisX=rand()%genislik;
    yemisY=rand()%yukseklik;
    puan=0;
}

void ciz(){
    system("CLS");

    for(int i=0;i<genislik+2;i++){
        cout<<"#";
    }

    cout<<endl;

    for(int i=0;i<yukseklik;i++){
        for(int j=0;j<genislik;j++){
            if(j==0){
                cout<<"#";
            }
            if(i==y && j==x){
                cout<<"0";
            }
            else if(i==yemisY && j==yemisX){
                cout<<"*";
            }
            else{
                bool yazdir=false;

                for(int k=0;k<kuyrukSayisi;k++){
                    if(kuyrukX[k]==j && kuyrukY[k]==i){
                        cout<<"o";
                        yazdir=true;
                    }
                }

                if(!yazdir){
                    cout<<" ";
                }
            }

            if(j==genislik-1){
                cout<<'#';
            }
        }

        cout<<endl;
    }

    for(int i=0;i<genislik+2;i++){
        cout<<"#";
    }

    cout<<endl<<"Puan: "<<puan<<endl;
}

void giris(){
    if(_kbhit()){

        switch(_getch()){
        case 'a':
            dir=SOL;
            break;
        case 'd':
            dir=SAG;
            break;
        case 'w':
            dir=YUKARI;
            break;
        case 's':
            dir=ASAGI;
            break;
        case 'x':
            oyunSonu=true;
            break;
        }
    }
}

void mantik(){
    int oncekiX=kuyrukX[0];
    int oncekiY=kuyrukY[0];
    int onceki2X, onceki2Y;

    kuyrukX[0]=x;
    kuyrukY[0]=y;

    for(int i=1;i<kuyrukSayisi;i++){
        onceki2X=kuyrukX[i];
        onceki2Y=kuyrukY[i];
        kuyrukX[i]=oncekiX;
        kuyrukY[i]=oncekiY;
        oncekiX=onceki2X;
        oncekiY=onceki2Y;
    }

    switch(dir){
    case SOL:
        x--;
        break;
    case SAG:
        x++;
        break;
    case YUKARI:
        y--;
        break;
    case ASAGI:
        y++;
        break;
    }

    if(x>genislik || x<0 || y>yukseklik || y<0){
        oyunSonu=true;
    }

    for(int i=0;i<kuyrukSayisi;i++){
        if(kuyrukX[i]==x && kuyrukY[i]==y){
            oyunSonu=true;
        }
    }

    if(x==yemisX && y==yemisY){
        puan=puan+10;
        yemisX=rand()%genislik;
        yemisY=rand()%yukseklik;
        kuyrukSayisi++;
    }
}

void anaMenu(){
    int seviye;

    cout<<"Bir Seviye Seciniz (1-10): ";
    cin>>seviye;
    kur();

    while(!oyunSonu){
        ciz();
        giris();
        mantik();
        Sleep(100/seviye);
    }

    char tercih;

    cout<<"Puan= "<<puan<<endl;
    cout<<"Devam Etmek Istiyor Musunuz (E/e)? ";
    cin>>tercih;

    if(tercih=='e' || tercih=='E'){
        system("CLS");
        kuyrukSayisi=0;
        anaMenu();
    }
}

int main(){
    anaMenu();
    system("CLS");
    cout<<"Oyun Sonu!";
    Sleep(2000);

    return 0;
}

