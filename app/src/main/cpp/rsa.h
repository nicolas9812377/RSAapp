//
// Created by Lenovo 330S on 3/7/2021.
//

#ifndef RSA_APP_RSA_H
#define RSA_APP_RSA_H

void insertarP(int);
void insertarQ(int);
int primoAleatorio();
void generarPrimos();
void generarClaves();
long long int cifrarCaracter(long long int);
char *cifrarTexto(char *);
long long int descifrarCaracter(long long int);
char *descifrarTexto(char *);
//void mostrar();

//metodos utilitarios
int mcd(int, int);
bool verificar1(char []);
bool verificar2(char *);
void concatenar(char *, char *);
jstring convertInt(long long int);


#endif //RSA_APP_RSA_H
