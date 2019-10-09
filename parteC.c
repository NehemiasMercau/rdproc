#include "main.h"


/**
 * Imprime la cantidad de pedidos a disco realizados
 */
void pedidosHDD(){
	char matched[BUFFSIZE];
	unsigned int lecturas, escrituras, pedidos;

	getMatch("/proc/diskstats", matched, "sda");
	sscanf(matched, "sda %u", &lecturas);
	sscanf(matched, "sda %*u %*u %*u %*u %u", &escrituras);
	pedidos = escrituras + lecturas;
	printf("Cantidad de pedidos al disco: %u\n", pedidos);
	return;
}

/**
 * Imprime la informacion de la memoria
 */
void memInfo(){
	char matched[BUFFSIZE];
	unsigned int memTotal, memFree;

	getMatch("/proc/meminfo", matched, "MemTotal");
	sscanf(matched, "MemTotal: %u", &memTotal);
	getMatch("/proc/meminfo", matched, "MemFree");
	sscanf(matched, "MemFree: %u", &memFree);
	printf("Memoria total: %u MB\n", memTotal/1024);
	printf("Memoria disponible: %u MB\n", memFree/1024);
	return;
}

/**
 * Imprime lista de promedios de carga de un minuto
 */
void loadAvg(){
	FILE *fd;
	float load;
	fd = fopen("/proc/loadavg","r");
	fscanf(fd,"%f", &load);
	printf("Promedio de carga de un minuto: %f\n", load);
	fclose(fd);
	return;
}
