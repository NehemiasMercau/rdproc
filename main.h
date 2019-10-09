#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#define BUFFSIZE 256  //lo defino como una longitud arbitraria de longitudes de lineas de texto extraidas de archivos

void printParteA();
void printParteB();
void printParteC(int, int);
void printParteD1(int);
void printParteD2(int);
void printParteD3(int);
void Encabezado(char str[]);
void piePagina();
void getMatch(char*, char*, char*);

