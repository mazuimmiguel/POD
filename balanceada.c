#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RAM 5
#define NUM_CAMINHOS 3

int cparai(char c){
  return (int)(c-'a');
}

void sort(char* vet, int tam){
	int i;
	char aux;
	int troca;
	do{
		troca=0;//inicia sem troca
		for(i=1;i<tam;i++){//percorre o  vetor
			if(cparai(vet[i])<cparai(vet[i-1])){//se ter troca
				aux=vet[i];
				vet[i]=vet[i-1];
				vet[i-1]=aux;
				troca=1;//define que teve troca
			}
		}
	}while(troca);//se nenhuma troca ter ocorrido acaba

}

// Le um aquivo com numeros inteiros e mostra-os na tela.
void le_arq(char *nome){
	FILE *arq;
	char num;
	int i=0;

	arq = fopen(nome,"r");

	while( 1 == fread(&num,sizeof(num),1,arq)){
		printf("%d:%c\t",i++,num);
		if (i%RAM==0)
		printf("\n");
	}
	printf("\n");
}

void fecha_arqs(int num, FILE **arqs){
	int i;
	for (i =0; i < num; i++){
		fclose(arqs[i]);
	}
}

void gera_arqs_temp(int inicio, int fim, char *nome_arq, FILE **arqstemp, char *como){
	char nome_arq_temp[20];
	int i;
	for (i=inicio;i<fim;i++){
		// cria o nome do arquivo e gera ele 
		sprintf(nome_arq_temp,"%s.%d.txt",nome_arq,i);
		arqstemp[i-inicio]=fopen(nome_arq_temp, como);
	}
}

void intercalacao_balanceada(int num_caminhos, char *nome_arq){
	int i;
	int teste=0,pos_menor;
	char nome_arq_temp[20];
	char comp[num_caminhos];
 	char aux[100];
	FILE* temp;
	FILE **arqstemp = malloc(sizeof(FILE*)*num_caminhos);
	/*
	for(i=0;i<num_caminhos;i++){//organiza as letras dentro do arquivos temp
		sprintf(nome_arq_temp,"%s.%d.txt",nome_arq,i);
		arqstemp[i]= fopen(nome_arq_temp,"r");
		
		fgets(aux,100,arqstemp[i]);
		sort(aux,strlen(aux));

		arqstemp[i]= fopen(nome_arq_temp,"w");
		fwrite(aux, sizeof(char)*strlen(aux), 1, arqstemp[i]);
	}
	
	fecha_arqs(num_caminhos, arqstemp);
	*/
	for(i=0;i<num_caminhos;i++){//carrega as primeiras letras
		sprintf(nome_arq_temp,"%s.%d.txt",nome_arq,i);
		arqstemp[i]= fopen(nome_arq_temp,"r");
		comp[i]=fgetc(arqstemp[i]);
	}
	
	temp = fopen("organizado.txt","w");//gera o arquivo final
	do{
		pos_menor=-1;//inicializa com nenhuma letra como menor (se colocasse zero, o primeiro arquivo poderia selecionado, mesmo estando no EOF)
		for(i=0;i<num_caminhos;i++){
			if(!(feof(arqstemp[i]))){//se n estiver vazio
				if(pos_menor==-1){//se nenhuma letra ainda tiver sido achada
					pos_menor=i;
				}else{
					if(cparai(comp[i])<=cparai(comp[pos_menor])){//se a letra encontrada for menor
						pos_menor=i;	
					}
				}
			}else{//se estiver vazio
				teste++;
			}
		}
		if(teste==num_caminhos){//se todos os arquivos estiverem vazios
			break;//finaliza
		}else{
			teste=0;//reseta o contador de vazios
			fputc(comp[pos_menor], temp);//insere a menor letra
			if(!(feof(arqstemp[pos_menor]))){//se o arquivo não estiver no fim
				comp[pos_menor]=fgetc(arqstemp[pos_menor]);//seleciona a proxima letra
			}
		}
	}while(1);
	
	fclose(temp);//fecha os arquivos
	fecha_arqs(num_caminhos, arqstemp);
	
	
}

void distribui(int num_caminhos, char *nome_arq, char *arq_organizar){
	FILE *arq = fopen(arq_organizar,"r");
	FILE **arqstemp = malloc(sizeof(*arq)*num_caminhos);
	char buffer[RAM], i=0, lidos;

	gera_arqs_temp(0,num_caminhos,nome_arq,arqstemp,"w"); //Gera os arquivos temporarios

	while( RAM == (lidos = fread(&buffer, sizeof(char), RAM, arq))){ // le o arquivo de entrada para a RAM
		sort(buffer,RAM); // Reorganiza os caracteres
		fwrite(buffer, sizeof(char)*RAM, 1, arqstemp[i]); // escreve para o arquivo temporario atual
		i++;
		i %= num_caminhos; // incrementa o arquivo temporario
	}

	// trata os ultimos numeros do arquivo
	sort(buffer,lidos); // Reorganiza os caracteres
	fwrite(buffer, sizeof(char)*lidos, 1, arqstemp[i]); // escreve para o arquivo temporario atual
	fecha_arqs(num_caminhos, arqstemp);

	intercalacao_balanceada(num_caminhos,nome_arq);
}

int main( int argc, char *argv[ ]){
	char* arq_organizar = argv[1];

	char nome_temp[]="temporario";
	char *nome_arq_temp = malloc(sizeof(char)*strlen(nome_temp)+3); // suporta ate .99 arquivos
	
	le_arq(arq_organizar);
	distribui(NUM_CAMINHOS, nome_temp,arq_organizar);

	int i;
	for (i=0; i<NUM_CAMINHOS; i++){
		sprintf(nome_arq_temp, "%s.%d.txt", nome_temp, i);
		printf("------- %s:\n", nome_arq_temp);
		le_arq(nome_arq_temp);
	}
	
	printf("------- Organizado.txt:\n");
	le_arq("organizado.txt");
}

