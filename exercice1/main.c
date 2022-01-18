#include "main.h"

int main(){
	char *welcome = "$ ./enseash\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'. \n";
	char *nline = "enseash % ";
	write(STDOUT_FILENO, welcome ,strlen(welcome));
	write(STDOUT_FILENO, nline ,strlen(nline));
	
	return 0;
}
