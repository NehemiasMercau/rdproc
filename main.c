#include "main.h"
#include "parteA.h"
#include "parteB.h"
#include "parteC.h"
#include "parteD.h"


int main(int argc, char *argv[]) {

	int nextArg;

	const char* argumentos = "slpft";
	unsigned int *a=&(unsigned int){0}, *b=&(unsigned int){0}, *pid=&(unsigned int){0};
	//int *pdi=&(int){0};
	printParteA();


	do {
		nextArg = getopt(argc,argv,argumentos);
		switch(nextArg)
		{
		case 's':
			//parteB
			printParteB();
			break;
		case 'l':
			//
			sscanf(argv[2], "%u", a);
			sscanf(argv[3], "%u", b);
			printParteB();
			printParteC(*a, *b);
			break;
		case 'p':
			sscanf(argv[2], "%u", pid);
			printParteD1(*pid);
			break;
		case 'f':
			sscanf(argv[2], "%u", pid);
			printParteD2(*pid);
			break;
		case 't':
			sscanf(argv[2], "%u", pid);
			printParteD3(*pid);
			break;
		case -1:
			break;
		default:
			break;
		}
	}
	while (nextArg != -1);
}

void printParteA(){
	Encabezado("A");
	printCpuInfo();
	printKernelInfo();
	printUpTime();
	printNumFilesystemsSuport();
	impHostname();
	impFecha();
	piePagina();
	return;
}

void printParteB(){
	Encabezado("B");
	cpuTimes();
	contextChanges();
	processes();
	piePagina();
	return;
}

void printParteC(int a, int b){
	Encabezado("C");

	int i;
	i=b/a;
	printf("-------------------------------------\n");
	while(i>0){
		pedidosHDD();
		memInfo();
		loadAvg();
		i--;
		sleep(a);
		printf("-------------------------------------\n");
	}
	piePagina();
	return;
}

void printParteD1(int pid){
	Encabezado("D1");
	fileDescriptors(pid);
	piePagina();
	return;
}

void printParteD2(int pid){
	Encabezado("D2");
	fileLimits(pid);
	piePagina();
	return;
}

void printParteD3(int pid){
	Encabezado("D3");
	stackTrace(pid);
	piePagina();
	return;
}

void Encabezado(char str[]){
	printf("\n ***************** Parte: %s *************\n", str);
	return;
}

void piePagina(){
	puts("\n *******************FIN********************\n");
	return;
}

/**
 * Coloca en matched una linea que comienza con la cadena matchStr, recortada de una linea extraida de un archivo de texto.
 * @param filename El archivo en el que se va a buscar.
 * @param matched Almacena la linea que comienza con la cadena matchStr.
 * @param matchStr Cadena a buscar.
 */
void getMatch(char* filename, char* matched, char* matchStr){
	char buffer[BUFFSIZE]; //defino de forma arbitraria que la linea no va a tener mas caracteres que BUFFSIZE, total la funcion fgets que utilizo para leer la linea deja de leer una vez que encuentra LF o EOF
	char* match = NULL;
	FILE* fd;
	fd = fopen(filename,"r");
	while(feof(fd) == 0){
		fgets(buffer, BUFFSIZE, fd);           //esta funcion es la que extrae una linea del archivo
		match = strstr(buffer, matchStr);      //esta funcion busca en la linea extraida la cadena matchStr, y devuelve el recorte de la linea desde el comienzo de matchStr
		if(match!=NULL) break;
	}

	fclose(fd);
	strcpy(matched,match);
	return;
}




