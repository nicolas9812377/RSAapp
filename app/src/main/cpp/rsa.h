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
int cifrarCaracter(int);
int cifrarTexto(char *,char *);
long long int descifrarCaracter(long long int);
int descifrarTexto(char *, char *);
//int leres(char, char);
//void mostrar();

//metodos utilitarios
int mcd(int, int);
int verificar1(char []);
int verificar2(char *);
void concatenar(char *, char *);
char* convertInt(long long int);


#endif //RSA_APP_RSA_H
