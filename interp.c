#include "interp.h"

int countElements(char *str){

  int count=0;
  int i;
  size_t len = strlen(str);
  for (i = 0; i < len; i++) {
    if(str[i] == ',')
    	count++;
  }
    return count;
 }
void removeFandLchar(char *string){
	int i;
	size_t len = strlen(string);

	 for (i = 0; i < len; ++i){
	 	string[i] = string[i+1];
	 }
	 string[len-2] = '\0';
	
}

void insertInto(char *tableName,char *references, char *values){
	int nRef, nVal,i;

	nRef = countElements(references)+1;
	nVal = countElements(values) +1;
	char *aux1, *aux2;
	elements element[nRef];
	table  *tab = (table *)malloc(sizeof(table));
	column *col = NULL;

	strcpy(tab->nome,tableName);
	tab->esquema = leSchema(leObjeto(tab->nome));


	if(nRef!=nVal)// if the number of references isn't the same as the number of values
		return;

	for (i = 0; i < nRef; ++i){
		aux1 = strsep(&references, ",");
		aux2 = strsep(&values, ",");
		//puts(aux);

		if(strchr(aux2,'"')){
			removeFandLchar(aux2);
		}

		strcpy(element[i].fieldName,aux1);
		strcpy(element[i].fieldValue,aux2);
		col = insereValor(tab,col, element[i].fieldName, element[i].fieldValue);

	}

	finalizaInsert(tab->nome, col);
	imprime(tab->nome);

}

bool inter(char *string){
	int nCase;

	char *ptr,*aux, *tb, *ref, *values;
		
		aux = malloc(sizeof(char*) *(strlen(string)));
		aux = strcpy(aux,string);


		aux = strsep(&aux," ");
		
		if(string[0]== ' ')
			return 0;

		if(!strcmp(aux,"INSERT"))
			nCase = 1;		
		if(!strcmp(aux,"CREATE"))
			nCase = 2;


		if(nCase == 1){
			string  = strstr(string,"INSERT INTO");
			values = malloc(sizeof(char*) *(strlen(string)));
			values = strcpy(values,string);
			
			if(!string) 
				return 0;


			ptr = strtok(string," ");
			while(ptr != NULL){
				ptr = strtok(NULL," ");
				if(!strstr(ptr,"INTO"))
					break;
			}

			

			//table
			tb = strsep(&ptr, "(");
			if(!tb) return 0;

			//references
			ref = strsep(&ptr,")");
			if(!ref) {
				ptr = strtok(NULL,"(");
				ptr = strsep(&ptr,")");
				ref = ptr;

			}


			//values
			values = strstr(values,"VALUES");
			values = strtok(values,"(");
			values = strtok(NULL,"(");
			values = strsep(&values,")");


			insertInto(tb,ref,values);
		}
		else if(nCase == 2){

			string  = strstr(string,"TABLE");
			
			if(!string) 
				return 0;

			if(strsep(&string," ")){//table name
				tb = strsep(&string, "(");
				if(!tb) return 0;
			}
			else return 0;
			

		}
		else return 0;

		return 1;
}
