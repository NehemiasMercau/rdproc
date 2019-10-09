#include "main.h"
#include "parteD.h"
#include <limits.h> /* PATH_MAX */
char *x;

void fileDescriptors(int pid){

	char str[12];
	sprintf(str, "%d ", pid);
	char cmd[100] = "lsof -a -p ";
	char tag[10] = " > ";
	char fin[500]= " 2>&1";
	strcat(cmd, str);
	strcat(cmd, tag);
	strcat(cmd, getURL());
	strcat(cmd, fin);

	system(cmd);


	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	char filename[100];
	strcpy(filename, getURL());

	fp = fopen(filename, "r");
	if (fp == NULL){
		puts("Fallo al abrir el archivo");
		exit(EXIT_FAILURE);
	}


	while ((read = getline(&line, &len, fp)) != -1) {
		char comando[50];
		char FD[50];
		char Type[50];
		char Path[50];
		sscanf(line, "%s", comando);
		sscanf(line, "%*s %*s %*s %s", FD);
		sscanf(line, "%*s %*s %*s %*s %s", Type);
		sscanf(line, "%*s %*s %*s %*s %*s %*s %*s %*s %s", Path);

		printf("<%s>  <%s>  <%s>  <%s> \n", comando, FD, Type, Path);

	}

	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);

}


void fileLimits(int pid){
	char strpid[12];
	sprintf(strpid, "%d", pid);
	char cmd[15] = "/proc/";
	strcat(cmd, strpid); //concatena el cmd con el pid
	char cmdlimits[15] = "/limits";
	strcat(cmd, cmdlimits); //concatena el cmd con el cmdlimits

	char matched[BUFFSIZE];
	long int softLimit;
	long int hardLimits;
	getMatch(cmd, matched, "Max open files");
	sscanf(matched, "Max open files %ld" , &softLimit);
	sscanf(matched, "Max open files %*d %ld" , &hardLimits);
	printf("Soft Limit: %ld \n", softLimit);
	printf("Hard Limit: %ld \n", hardLimits);
	return;
}


void stackTrace(int pid){
	char strpid[12];
	sprintf(strpid, "%d", pid);
	char cmd[100] = "sudo cat /proc/";
	strcat(cmd, strpid); //concatena el cmd con el pid
	char cmdlimits[15] = "/stack";
	strcat(cmd, cmdlimits); //concatena el cmd con el cmdlimits

	char tag[10] = " > ";
	char fin[500]= " 2>&1";
	strcat(cmd, tag);
	strcat(cmd, getURL());
	strcat(cmd, fin);


	system(cmd);

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	char filename[100];
	strcpy(filename, getURL());

	fp = fopen(filename, "r");
	if (fp == NULL){
		exit(EXIT_FAILURE);
	}

	printf("Stack Trace del ProcessId: %s \n\n", strpid);
	while ((read = getline(&line, &len, fp)) != -1) {
		char simbolo[50] = "";
		size_t i = 0;
		size_t j = strlen(line);
		int k = 0;
		for (; i < j; i++){
			if (line[i]==']'){
				k = i;
				if (line[i+1]=='+'){
					break;
				}

			}
			if (line[i+1]=='+'){
				k = 0;
			}
			if (k!=0){
				char li = line[i+1];
				strcat(simbolo, &li);
			}

		}
		printf("%s\n", simbolo);

	}


	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);


}

const char * getURL(){
	char user[50];
	char str1[50]= "/home/";
	char str2[100]= "/Documentos/output";
	char str[200];

	getlogin_r(user, 50);

	strcat(str1, user);
	strcat(str1, str2);

	sprintf(str, "%s", str1);
	x = str;
	return x;
}


