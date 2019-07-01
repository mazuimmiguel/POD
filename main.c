#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void comprimir(char* arquivo){
	int i=0; 
	int cont = 0;
	char[200] temp;
	char comparar;
	
	FILE* arq = fopen(arquivo,"r");
	fgets(temp,200,arq);
	FILE* comprimido = fopen("comprimido.txt","w");
	
	do{
		comparar = temp[i];
		do{
			break;
		}while(1);
		break;
	}while(1);

	
}

int main( int argc, char *argv[ ]){
	if(argc != 2){
		printf("Argumentos invalidos!");
		exit(1);
	}
	
	comprimir(argv[1]);
	
}

