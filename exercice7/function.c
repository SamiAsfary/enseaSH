#include "main.h"

int cinstr(char * str, char separator){
	int loop = 0, total = 0;	
	while(str[loop] != '\0'){
		if(str[loop] == separator){total++;}
		loop++;
	}
	return total;
}
