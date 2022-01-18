#include "main.h"


int main(){
	const char *welcome = "$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'. \n";
	char newline[50];
	sprintf(newline, "enseash %% ");
	char buff[BUFFER_SIZE];
	int pid;
	ssize_t read_len;
	int returnStatus;
	struct timespec start;
	struct timespec end;
	long delay;
	
	
	write(STDOUT_FILENO, welcome ,strlen(welcome));
	write(STDOUT_FILENO, newline ,strlen(newline));
	

	while(1){
		read_len = read(STDIN_FILENO,buff,BUFFER_SIZE);
		
		//test pour Ctrl+D et exit
		if(strncmp(buff,"exit",strlen("exit")) == 0  || read_len == 0){
			write(STDOUT_FILENO, "\nKTHXBYE\n", strlen("\nKTHXBYE\n"));
			return 0;
		}
		
		//ajout du caractère de fin de chaine de caractère
		buff[read_len-1] = '\0';
		
		clock_gettime(CLOCK_MONOTONIC, &start);
		
		pid = fork();
		if(pid == 0){
			execlp(buff, buff,  NULL);
			exit(EXIT_FAILURE);
		}
		
		//attente de la fin du processus fils et recuperation du status de sortie du processus fils
		wait(&returnStatus);
		
		//recuperation du temps et calcul de temps d'éxecution de la commande
		clock_gettime(CLOCK_MONOTONIC, &end);
		delay = (end.tv_nsec - start.tv_nsec)/1000000 + ((long)((end.tv_sec-start.tv_sec)*1000));
		
		//affichage du status de sortie du processus fils
		if(WIFEXITED(returnStatus)){
			sprintf(newline, "enseash [exit:%d|%ldms] %% ",WEXITSTATUS(returnStatus),delay);
		}else if(WIFSIGNALED(returnStatus)){
			sprintf(newline, "enseash [sign:%d|%ldms] %% ",WTERMSIG(returnStatus),delay);
		}
		
		
		write(STDOUT_FILENO, newline ,strlen(newline));
	}
	pid = 1;
	return 0;
}



