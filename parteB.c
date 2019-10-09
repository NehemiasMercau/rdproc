#include "main.h"
#include "parteB.h"
#include "parteA.h"



/**
 * Imprime el tiempo de cpu de usuario, sistema, e idle.
 */
void cpuTimes(){
	float user, sys, idle;
	char tUser[15], tSys[15], tIdle[15];
	FILE *fd;
	fd = fopen("/proc/stat","r");
	fscanf(fd,"cpu %f %*f %f %f", &user, &sys, &idle);
	secToDayHourMinSec(user/100, tUser);
	printf("Tiempo de cpu para el usuario: %s \n",tUser);
	secToDayHourMinSec(sys/100, tSys);
	printf("Tiempo de cpu para el sistema: %s \n",tSys);
	secToDayHourMinSec(idle/100, tIdle);
	printf("Tiempo de cpu idle: %s \n",tIdle);
	fclose(fd);
	return;
}

/**
 * Imprime la cantidad de cambios de contexto
 */
void contextChanges(){
	char matched[256];
	unsigned int cambios;

	getMatch("/proc/stat", matched, "ctxt");
	sscanf(matched, "ctxt %u", &cambios);

	printf("Cambios de contexto: %u \n", cambios);
	return;
}

/**
 * Imprime la cantidad de procesos creados desde el inicio del sistema
 */
void processes(){
	char matched[BUFFSIZE];
	unsigned int* procesos=&(unsigned int){0};


	getMatch("/proc/stat", matched, "processes");
	sscanf(matched, "processes %u", procesos);

	printf("Cantidad de procesos creados: %u\n", *procesos);
	return;
}
