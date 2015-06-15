#include <stdbool.h>
#include "buffend.h"
#define MAX_QUERY_SIZE 1000

typedef struct elements{
	char fieldName[TAMANHO_NOME_CAMPO];	//Nome do Campo.
	char fieldValue[TAMANHO_NOME_CAMPO];// Valor do Campo.
}elements;

int countElements(char *str);

void removeFandLchar(char *string);

void insertInto(char *tableName,char *references, char *values);

bool inter(char *string);
