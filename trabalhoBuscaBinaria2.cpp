#include<stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{	
	FILE *f;
	Endereco e;
	long tamanhoArquivo;	
	f = fopen("cep_ordenado.dat.part","r");
    fseek(f,0,SEEK_END);
	tamanhoArquivo = ftell(f);
	    int inicio=0;
	    int achei=0;
	    int i = 0;
	   	int len;
	    int meio;	    
		int fim=(tamanhoArquivo/sizeof(Endereco))-1;
		
		while(inicio<=fim){
		i++;		
		meio=(fim+inicio)/2;
		fseek(f, meio*sizeof(Endereco), SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);				
				
		if(strncmp(argv[1],e.cep,8)==0){
			achei=1;
		    printf("\nO valor %s foi encontrado",argv[1]);
			printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);		
			break;			
		}
		if(strncmp(argv[1],e.cep,8)<0){
			fim=fim-1;
			}
		
		if(strncmp(argv[1],e.cep,8)>0){
			inicio=inicio+1;
			}		
	}
	
	if(achei==0){
			printf("\n valor %s nao foi encontrado",argv[1]);
		}
	printf("\n",i);
	
return 0;	
}
