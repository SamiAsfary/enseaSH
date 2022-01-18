#include "main.h"


int main(){
	const char *welcome = "$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'. \n";
	const char *newline = "enseash % ";
	char buff[BUFFER_SIZE];
	int pid;
	ssize_t read_len;
	
	write(STDOUT_FILENO, welcome ,strlen(welcome));
	write(STDOUT_FILENO, newline ,strlen(newline));

	while(1){
		read_len = read(STDIN_FILENO,buff,BUFFER_SIZE);
			
		//test pour Ctrl+D et exit
		if(strncmp(buff,"exit",strlen("exit")) == 0  || read_len == 0){
			return 0;
		}else if(buff[read_len-1] != '\n'){
			return 0;
		}
		
		//ajout du caractère de fin de chaine de caractère
		buff[read_len-1] = '\0';
		
		pid = fork();
		if(pid == 0){
			execlp(buff, buff,  NULL);
			
			return 0;
		}
		//attente de la fin du processus fils
		wait(NULL);
		write(STDOUT_FILENO, newline ,strlen(newline));
	}
	
	return 0;
}



