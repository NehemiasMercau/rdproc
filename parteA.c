#include "main.h"
#include "parteA.h"

void printKernelInfo() {
	puts("\n La version del kernel es: ");
	system("uname -rms");
}

void printCpuInfo() {

	FILE *cpuinfoFile;
	char buffer[50];
	cpuinfoFile = fopen ("/proc/cpuinfo", "r");

	if (cpuinfoFile==NULL) {
		printf("No cpuinfo file found!");
		fclose(cpuinfoFile);
		return;
	}

	puts("\n Informacion del CPU: ");

	while(!feof(cpuinfoFile)) {
		char *tipoCpu;
		char *modelCpu;
		char *lineRead = fgets(buffer, 50, cpuinfoFile);

		if(lineRead==NULL) { break; }

		if((tipoCpu = strstr(lineRead, "vendor_id"))!= NULL)
			printf("\n %s",tipoCpu);

		if((modelCpu = strstr(lineRead, "model name"))!= NULL)
		{
			printf("%s \n\n",modelCpu);
			break;
		}


	}

	fclose (cpuinfoFile);
	return;
}

/**
 * Imprime el tiempo transcurrido desde que se inición el SO, con formato DD HH:MM:SS
 */
void printUpTime(){
	FILE *fd;
	float time;
	char hms[20];
	fd = fopen("/proc/uptime","r");
	fscanf(fd, "%f", &time);
	secToDayHourMinSec(time, hms);
	printf("Tiempo transcurrido desde que se inicio el SO: %s \n", hms);
	fclose(fd);
	return;
}

/**
 * Convierte un numero de segundos a formato DD HH:MM:SS
 * @param secs Segundos a convertir
 * @param buf Tiempo en formato DD HH:MM:SS
 */
void secToDayHourMinSec (float secs, char* buf){
	unsigned int d, h, m;
	float s;

	d = (int) (secs / 86400);
	secs = secs - (long) (d * 86400);
	h = (int) (secs / 3600);
	secs = secs - (long) (h * 3600);
	m = (int) (secs / 60);
	secs = secs - (long) (m * 60);
	s = secs;
	if (d > 0)
		sprintf (buf, "%2ud %2u:%02u:%02.2f", d, h, m, secs);
	else
		sprintf (buf, "%2u:%02u:%02.2f", h, m, s);
	return;
}

/**
 * Imprime el numero de sistemas de archivos soportados por el kernell.
 */
void printNumFilesystemsSuport(){
	int n = 0;
	//int dato = 0;
	FILE *fd;
	fd = fopen("/proc/filesystems","r");

	while(feof(fd) == 0){
		int dato = fgetc(fd); //lectura de cada caracter en ascii
		if(dato == 10) n++; // en ascii el 10 es salto de linea... como en el archivo los filesystems soportados estan tabulados, cada salto de linea es uno mas
	}

	fclose(fd);
	printf("Cantidad de sistemas de archivos soportados por el kernel: %d \n", n+1);
	return;
}

void impHostname()
{
	char const* const fileName = "/proc/sys/kernel/hostname";
	FILE* file = fopen(fileName, "r");
	char * line[256];
	fgets(*line, sizeof(line), file);
	printf("Hostname: %s", *line);
	fclose(file);
}

void impFecha()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Fecha y hora actual: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

}
