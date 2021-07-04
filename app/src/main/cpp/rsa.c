//
// Created by Lenovo 330S on 3/7/2021.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <jni.h>

int q = 0, p = 0;
long long int n = 0, fi = 0;
long long int e = 0, d = 0;
char Abc[50];
char resultado[1024];

//strcpy(Abc, "0123456789abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ");

//Funcion que retorna un numero primo generado aleatoriamente, el rango en que se genera el numero primo esta definido internamente
int primoAleatorio()
{
    int num, p;
    int RAND_MAX = 10;
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
        return  "0";
    char * temp="";
    char * returnvalue="";
    while (number>0)
    {
        temp = malloc(temp+1);
        strcat(temp, number%10+48):
        //temp+=number%10+48;
        number/=10;
    }
    for(int i=0; i<temp.length(); i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

//cifrar x, convertirlo a char y luego copiar caracter a caracter y sumarle un espacio en blanco,
//todo a un arreglo de caracteres, ejemplo: "19203 12843 2837"
char * cifrarTexto(char *T)
{
    char *cadena, *pt;
    jstring temp;
    strcpy(resultado, "\0");
    pt=T;
    for(int i=0; i<strlen(T); i++)
    {
        for(int x=0; x<strlen(Abc); x++)
        {
            if(*pt == Abc[x])
            {
                temp= convertInt(cifrarCaracter(x));
                cadena= strdup(temp.c_str());
                concatenar(resultado, cadena);
                pt++;
            }
        }
    }
    return resultado;
}

//clave publica (e, n)
long long int cifrarCaracter(long long int men)
{
    long long int C = 1;
    for(int i=0; i<e ; i++)
        C=C*men%n;
    C = C%n;
    return C;
}

//funcion para saber si, dentro del arreglo de caracteres, hay solo numeros, retorna true si se cumple, false de lo contrario
bool verificar2(char *T)
{
    bool band;
    while(*T != '\0')
    {
        if(*T=='1' || *T=='2' || *T=='3' || *T=='4' || *T=='5' || *T=='6' || *T=='7' || *T=='8' || *T=='9' || *T=='0' || *T==' ' )
            band= true;
        else
            return false;
        T++;
    }
    return band;
}

//funcion para saber si, dentro del arreglo de caracteres, hay un espacio despues de cada grupo de numeros alfanumericos,
//retorna true si se cumple, false de lo contrario
bool verificar1(char texto[])
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
        return false;
    if(texto[i-1]==' ')
        c--;
    return true;
}

//se recibe un arreglo de caracteres (numeros separados x espacios), se sacan de uno cada caracter hasta encontrar un espacio,
//y se convierte a un numero compacto, se descifra y como resultado dara una letra, esa letra se mete en resultado hasta descifrar todo
//y obtener el texto plano
char * descifrarTexto(char *T)
{
    char *pt, cadena[15];
    pt=T;
    int c= 0, j= 0;
    long long int num;
    strcpy(resultado, "\0");

    if( verificar1(T) && verificar2(T) )
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
                resultado[j]= Abc[descifrarCaracter(num)];
                c= 0;
                j++;
                pt++;
            }
        }
        cadena[c]= '\0';
        num= atoll(cadena);
        resultado[j]= Abc[descifrarCaracter(num)];
        c= 0;
        j++;
        resultado[j]= '\0';
    }
    else
        return (char*)"Error.";
    return resultado;
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
