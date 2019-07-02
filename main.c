#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void comprimir(char* arquivo){
    int i=0; 
    int cont = 0;
    char temp[200];
    char salvar[5];
    char comparar;


    FILE* arq = fopen(arquivo,"r");
    FILE* comprimido = fopen("comprimido.txt","w");
    fgets(temp,200,arq);//pega o texto

    do{
        if(temp[i] == '\0'){//verifica se acabou o arquivos
            break;
        }

        comparar = temp[i];//Pega o caractere para comparar
        cont=1;//o primeiro

        do{
            if(temp[i+1] == comparar && temp[i+1] != '\0'){//se o proximo for igual e não for o final
                cont++;//aumenta a quantidade
            }else{
                break;
            }
            i++;
        }while(1);

        sprintf(salvar,"%i%c",cont,comparar);//comprime e salva
        fwrite(salvar, sizeof(char)*strlen(salvar), 1, comprimido);
        i++;
    }while(1);


}
void descomprimir(char *arquivo){
    char temp[200];
    long cont;
    int i = 0, j = 0;
    int lidos;
    char *endptr;
    char salvar;

    FILE *arq = fopen(arquivo,"r");
    FILE *descomprimido = fopen("descomprimido.txt","w");
    fgets(temp,200,arq);

    do{
    	cont = strtol(temp+i,&endptr,10);
        lidos = cont;

        while(lidos != 0){
            lidos /= 10;
            i++;
        }

        for(j = 0; j<cont; j++){
            fputc(temp[i], descomprimido);
        }

    i++;

    }while(temp[i] != '\0');
}

int main( int argc, char *argv[ ]){
	int	modo = 0;
	if(argc != 3){
		printf("Argumentos invalidos!");
		exit(1);
	}
	char* endptr;
	strtoimax(" -123junk",&endptr,10);
	 printf("%ld\n", strtoimax("junk",&endptr,10));
	if(strcmp(argv[2],"c") == 0){
		printf("Comprimindo Arquivo: %s\n",argv[1]);
		comprimir(argv[1]);
	}else if(strcmp(argv[2],"d") == 0){
		printf("Descomprimindo Arquivo: %s\n",argv[1]);
		descomprimir(argv[1]);
	} else {
		printf("Segundo argumento deve ser [c] ou [d]");
		exit(1);
	}	
}

