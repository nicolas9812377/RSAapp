//
// Created by Lenovo 330S on 3/7/2021.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <jni.h>
#include "rsa.h"


static int q = 0, p = 0;
static long long int n = 0, fi = 0;
static long long int e = 0, d = 0;
static char Abc[68] = "0123456789abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
//static char resultado[1024];

//strcpy(Abc, "0123456789abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ");

//Funcion que retorna un numero primo generado aleatoriamente, el rango en que se genera el numero primo esta definido internamente
int primoAleatorio()
{
    int num, p;
    srand(time(NULL));
    while(1)
    {
        num= (int) (1000.0*rand()/(RAND_MAX+1.0));
        for(p = 2; num % p != 0; p++);
        if(p == num)
        {
            return num;
        }
    }
}

void generarPrimos()
{
    p= primoAleatorio();

    do
    {
        q= primoAleatorio();
    }while( q == p);
}

int mcd(int a, int b)
{
    int x, z;
    if(a<b)
    {
        x=a; z=b;
    }
    else
    {
        x=b; z=a;
    }
    if(b==0)
        return a;
    else
        return (mcd(b, a%b));
}

void generarClaves()
{
    int s;
    n= p*q;
    fi= (p-1)*(q-1);
    srand(time(NULL));
    do
    {
        e = rand()%fi;
    }while( mcd(e, fi) != 1 );

    d=1;
    do
    {
        s = (d*e)%fi;
        d++;
    }while(s!=1);
    d = d-1;
}



//Concatenacion especial de 2 arreglos de cararteres, se recibe T y S, se agrega un espacio al final de T y se une con S
//ejemplo: T= "hola", S= "griffin", ahora T sera: resultado: T= "hola griffin"
void concatenar(char *T, char *S)
{
    bool band= false;
    char *pt, *ps;
    pt=T;
    ps=S;

    while(*pt != '\0')
    {
        pt++;
        band= true;
    }

    if(band)
    {
        *pt=' ';
        *pt++;
    }

    while(*ps != '\0')
    {
        *pt=*ps;
        ps++;
        pt++;
    }
    *pt='\0';
}

char * convertInt(long long int number)
{

    if(number == 0)
        return  0;
    char temp [8] = "";
    int cont = 0;
    while (number>0)
    {
        //strcat(temp, (char *)t);
        //temp+=(number%10+48)+0x30;
        char tt = (number%10)+48;
        temp[cont] = tt;
        number/=10;
        cont++;
    }
    //return temp;
    //char valuet = "";
    //memset(returnvalue, 0, cont);
    //memcpy(returnvalue,temp,cont);
    //strcpy(returnvalue,temp);

    for(int i=0; i<cont/2; i++){
        //strcat(returnvalue,temp[strlen(temp)-i-1]);
        char* valuet = (char*)temp[i];
        temp[i] = temp[cont-i-1];
        temp[cont-i-1] = valuet;
    }

    return temp;
}

//clave publica (e, n)
int cifrarCaracter(int men)
{
    int C = 1;
    for(int i=0; i<e ; i++)
        C=C*men%n;
    C = C%n;
    return C;
}

//cifrar x, convertirlo a char y luego copiar caracter a caracter y sumarle un espacio en blanco, ejemplo: 19203 12843 2837
int cifrarTexto(char *T, char* buff)
{
    generarPrimos();
    generarClaves();
    char *cadena, *pt;
    char * temp;
    //strcpy(resultado, "\0");
    pt=T;
    int cont = 0;
    for(int i=0; i<strlen(T); i++)
    {
        for(int x=0; x<strlen(Abc); x++)
        {
            if(*pt == Abc[x])
            {

                //memcpy(buff,tt,strlen(T));
                temp= convertInt(cifrarCaracter(x));
                //strcat(buff, temp);
                //cadena= strdup(temp);
                concatenar(buff, temp);
                pt++;
                cont++;
                break;
            }
        }
    }

    return 0;
}


//funcion para saber si, dentro del arreglo de caracteres, hay solo numeros, retorna true si se cumple, false de lo contrario
int verificar2(char *T)
{
    int band;
    while(*T != '\0')
    {
        if(*T=='1' || *T=='2' || *T=='3' || *T=='4' || *T=='5' || *T=='6' || *T=='7' || *T=='8' || *T=='9' || *T=='0' || *T==' ' )
            band= 1;
        else
            return 0;
        T++;
    }
    return band;
}

//funcion para saber si, dentro del arreglo de caracteres, hay un espacio despues de cada grupo de numeros alfanumericos,
//retorna true si se cumple, false de lo contrario
int verificar1(char texto[])
{
    int i=0, c=0;
    if(texto[i]==' ')
        while(texto[i]==' ')
            i++;
    while(texto[i] != '\0')
    {
        if(texto[i] == ' ')
        {
            c++;
            while(texto[i]==' ')
                i++;
        }
        if(texto[i] != '\0')
            i++;
    }
    if(i==0)
        return 0;
    if(texto[i-1]==' ')
        c--;
    return 1;
}

//clave privada (d, n)
long long int descifrarCaracter(long long int men)
{
    long long int M= 1;
    for(int i=0; i<d; i++)
        M=M*men%n;
    M = M%n;
    return M;
}


//se recibe un arreglo de caracteres (numeros separados x espacios), se sacan de uno cada caracter hasta encontrar un espacio,
//y se convierte a un numero compacto, se descifra y como resultado dara una letra, esa letra se mete en resultado hasta descifrar todo
//y obtener el texto plano
int descifrarTexto(char *T,char* buff)
{
    char *pt, cadena[15];
    pt=T;
    int c= 0, j= 0;
    long long int num;
    //strcpy(resultado, "\0");

    if( verificar1(T) == 1 && verificar2(T) == 1)
    {
        for(int i= 0; i< strlen(T); i++)
        {
            if( *pt != ' ' )
            {
                cadena[c]= *pt;
                pt++;
                c++;
            }
            else
            {
                cadena[c]= '\0';
                num= atoll(cadena);
                buff[j]= Abc[descifrarCaracter(num)];
                c= 0;
                j++;
                pt++;
            }
        }
        cadena[c]= '\0';
        num= atoll(cadena);
        buff[j]= Abc[descifrarCaracter(num)];
        c= 0;
        j++;
        buff[j]= '\0';
    }
    else
        return 0;
    return 0;
}

void insertarP(int x)
{
    p=x;
}

void insertarQ(int x)
{
    q=x;
}

/*
void mostrar()
{
    cout << endl << Abc << endl << endl;
    cout << "p= " << p << endl;
    cout << "q= " << q << endl;
    cout << "n=p*q " << n << endl;
    cout << "fi= (p-1)*(q-1) " << fi << endl;
    cout << "clave publica (e, n)= " << "{" << e << ", " << n << "}" << endl;
    cout << "clave privada (d, n)= " << "{" << d << ", " << n << "}" << endl;
}*/
