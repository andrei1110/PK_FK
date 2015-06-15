#include "interp.h"

int main(int argc, char const *argv[]){
	
	char str[MAX_QUERY_SIZE];

	while(1){
		fflush(stdin);
		printf("#UsrDB > ");
		fgets(str,MAX_QUERY_SIZE, stdin);

		//get out
		if(strcmp(str,"quit\n") == 0)
			break;

		if(inter(str))
			printf("INSERT DONE\n");
		else
			printf("ERROR!\nVERIFY SYNTAX ON SYNTAX.TXT!\n");
	}


	return 0;
}
