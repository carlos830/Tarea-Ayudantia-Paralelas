#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>


using namespace std;

class Angulo{
private:
    int Numero;
    int x;
    int y;
};


class Triangulo{
private:
    char frase2[50];
public:
    int cuenta;
    int N;
    double AB;//angulo AB
    double BC;//angulo BC
    double CA;//angulo CA
    double Ax;//cordenada x del nodo A
    double Ay;//cordenada y del nodo A
    double Bx;//cordenada x del nodo B
    double By;//cordenada y del nodo B
    double Cx;//cordenada x del nodo C
    double Cy;//cordenada y del nodo C
    int A;
    int B;
    int C;
    char frase[50];
    Triangulo();
    void Muestra();
    void BuscaVertbice();
    void Split();
    void Split2();
    void Cordenadas();
    void Busca();
    void Angulos();
};
Triangulo::Triangulo(){
    cuenta=0;
}
void Triangulo::Angulos(){
    double Aa;//distancia
    double Bb;//distancia
    double Cc;//distancia
    Aa=sqrt(pow((Bx-Ax),2)+pow((By-Ay),2));
    Bb=sqrt(pow((Cx-Bx),2)+pow((Cy-By),2));
    Cc=sqrt(pow((Ax-Cx),2)+pow((Ay-Cy),2));
    AB = acos((Bb*Bb+Cc*Cc-Aa*Aa)/(2*Bb*Cc))*180/3.14159265;
    BC = acos((Aa*Aa+Cc*Cc-Bb*Bb)/(2*Aa*Cc))*180/3.14159265;
    CA = acos((Aa*Aa+Bb*Bb-Cc*Cc)/(2*Aa*Bb))*180/3.14159265;
}

void Triangulo::Split(){//separa frase espiral.mesh y lo guarda en variables
    char auxN[50],auxX[20],auxY[20];
    int posicion=0,y=0;
    for(int i=0;i<=strlen(frase);i++){
        if((frase[i]>47 and frase[i]<58) || (frase[i]>43 and frase[i]<47)){
            if(posicion==0){
                auxN[y]=frase[i];
                y++;
            }else if(posicion==1){
                auxX[y]=frase[i];
                y++;
            }else if(posicion==2){
                auxY[y]=frase[i];

                y++;
            }
        }else{
            if(posicion==2){
                C=atoi(auxY);
                posicion++;
                y=0;
            }else if(posicion==1){
                B=atof(auxX);
                posicion++;
                y=0;
            }else if(posicion==0){
                A=atof(auxN);
                posicion++;
                y=0;
            }
        }
    }
}
void Triangulo::Split2(){//separa frase espiral.node y lo guarda en variables
    char auxN[50],auxX[10],auxY[10];
    int posicion=0,y=0;
    for(int i=0;i<=strlen(frase);i++){
        if((frase[i]>47 and frase[i]<58) or (frase[i]>43 and frase[i]<47)){
            if(posicion==0){
                auxN[y]=frase[i];
                y++;
            }else if(posicion==1){
                auxX[y]=frase[i];
                y++;
            }else if(posicion==2){
                auxY[y]=frase[i];
                y++;
            }
        }else{
            if(posicion==2){
                if(A==N){
                    Ay=atof(auxY);
                    posicion++;
                    y=0;
                }else if(B==N){
                    By=atof(auxY);
                    posicion++;
                    y=0;
                }else if(C==N){
                    Cy=atof(auxY);
                    posicion++;
                    y=0;
                }
            }else if(posicion==1){
                if(A==N){
                    Ax=atof(auxX);
                    posicion++;
                    y=0;
                }else if(B==N){
                    Bx=atof(auxX);
                    posicion++;
                    y=0;
                }else if(C==N){
                    Cx=atof(auxX);
                    posicion++;
                    y=0;
                }
            }else if(posicion==0){
                N=atoi(auxN);
                if(A==N){
                    posicion++;
                    y=0;
                }else if(B==N){
                    posicion++;
                    y=0;
                }else if(C==N){
                    posicion++;
                    y=0;
                }
            }
        }
    }
}
void Triangulo::Cordenadas(){
    fstream Coordenadas;
    string nombre2= "Cordenadas.txt";
    Coordenadas.open (nombre2.c_str(),ios::in);
    if(Coordenadas.is_open()){
        while(!Coordenadas.eof()){
            Coordenadas.getline(frase, 50);
            Split2();
            cuenta++;
        }
    }
}
double Distancia(double Ax,double Bx,double Ay,double By){
    return sqrt(pow((Bx-Ax),2)+pow((By-Ay),2));
}
int main()
{
    char digito[20];
    cout << "Ingrese Angulo: ";
    cin >> digito;
    cout<<endl;
    char digito2[20];
    int k=0;
    for(int y=0;digito[y]!='\0';y++){
        if((digito[y]>47 and digito[y]<58) or (digito[y]>43 and digito[y]<47)){
            digito2[k]=digito[y];
            k++;
        }else{
            cout<<"Angulo ingresado no es valido"<<endl;
            system("pause");
            return 0;
        }
    }
    double Grad=atof(digito2);
    Triangulo triangulos[10000];
    int cuenta=0;//lineas de txt vertices
    fstream ficheroEntrada;
    string nombre= "espiral.mesh";
    ficheroEntrada.open (nombre.c_str(),ios::in);
    if(ficheroEntrada.is_open()){
            cout << "Refinando con respecto al angulo ingresado...." << endl;
        while(!ficheroEntrada.eof()){
            if(cuenta==0){
                    Triangulo *tri = new Triangulo();
                    ficheroEntrada.getline(tri->frase, 50);
            }else{
                Triangulo *tri = new Triangulo();
            ficheroEntrada.getline(tri->frase, 50);
            tri->Split();
            tri->Cordenadas();
            tri->Angulos();
            triangulos[cuenta-1] = *tri;
            }
            cuenta++;
        }
        ficheroEntrada.close();
    }
    ofstream nuevoNodos;
    ofstream N;
    double nAx,nAy,nBx,nBy,nCx,nCy,Aa,Bb,Cc;
    int cuento=0,cuenta2=1;
    for(int i=0;i<cuenta-1;i++){
        Aa=Distancia(triangulos[i].Ax,triangulos[i].Bx,triangulos[i].Ay,triangulos[i].By);
        Bb=Distancia(triangulos[i].Bx,triangulos[i].Cx,triangulos[i].By,triangulos[i].Cy);
        Cc=Distancia(triangulos[i].Cx,triangulos[i].Ax,triangulos[i].Cy,triangulos[i].Ay);
        if(Grad>=triangulos[i].AB or Grad>=triangulos[i].BC or Grad>=triangulos[i].CA){
            if(Aa>=Bb and Aa>=Cc){
                int posicion=(triangulos[i].cuenta)+cuenta2;
                nAx=(triangulos[i].Ax+triangulos[i].Bx)/2;//Coordenada media
                nAy=(triangulos[i].Ay+triangulos[i].By)/2;
                nuevoNodos.open("nuevascordenadas.txt",ios::app);
                nuevoNodos<<posicion<<" "<<nAx<<" "<<nAy<<endl;
                nuevoNodos.close();
                N.open("nuevosnodos.txt",ios::app);
                N<< triangulos[cuento].A<<" "<<posicion<<" "<<triangulos[cuento].C<<endl;
                N<< posicion<<" "<<triangulos[i].B<<" "<<triangulos[cuento].C<<endl;
                N.close();
                cuenta2++;
                cuento++;
            }
            if(Bb>=Aa and Bb>=Cc){
                int posicion=(triangulos[i].cuenta)+cuenta2;
                nBx=(triangulos[i].Bx+triangulos[i].Cx)/2;//Coordenada media
                nBy=(triangulos[i].By+triangulos[i].Cy)/2;
                nuevoNodos.open("nuevascordenadas.txt",ios::app);
                nuevoNodos<<posicion<<" "<<nBx<<" "<<nBy<<endl;
                nuevoNodos.close();
                N.open("nuevosnodos.txt",ios::app);
                N<< triangulos[cuento].A<<" "<<posicion<<" "<<triangulos[cuento].C<<endl;
                N<< triangulos[i].A<<" "<<triangulos[i].B<<" "<<posicion<<endl;
                N.close();
                cuenta2++;
                cuento++;
            }
            if(Cc>=Bb and Cc>=Aa){
                int posicion=(triangulos[i].cuenta)+cuenta2;
                nCx=(triangulos[i].Cx+triangulos[i].Ax)/2;//Coordenada media
                nCy=(triangulos[i].Cy+triangulos[i].Ay)/2;
                nuevoNodos.open("nuevascordenadas.txt",ios::app);
                nuevoNodos<<posicion<<" "<<nCx<<" "<<nCy<<endl;
                nuevoNodos.close();
                N.open("nuevosnodos.txt",ios::app);
                N<< posicion<<" "<<triangulos[i].B<<" "<<triangulos[cuento].C<<endl;
                N<< triangulos[i].A<<" "<<triangulos[i].B<<" "<<posicion<<endl;
                N.close();
                cuenta2++;
                cuento++;
            }
        }else{
            N.open("nuevosnodos.txt",ios::app);
            N<< triangulos[cuento].A<<" "<<triangulos[cuento].B<<" "<<triangulos[cuento].C<<endl;
            N.close();
            cuento++;
        }
    }
    cout << "Proceso finalizado revisar archivos nuevascoredenas.txt y nuevosnodos.txt "<<endl;


}
