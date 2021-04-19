#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)

typedef struct Endereco Endereco;

struct Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
int comparando(const void *e1, const void *e2);
void intercalando(char *arquivo1, char *arquivo2, char *arquivoSaida)
{
   
    FILE *x, *y, *saida;
    Endereco ex, ey;

    x = fopen(arquivo1, "r");
    y = fopen(arquivo2, "r");
    saida = fopen(arquivoSaida, "w");

    fread(&ex, sizeof(Endereco), 1, x);
    fread(&ey, sizeof(Endereco), 1, y);

    while (!feof(x) && !feof(y))
    {
        if ( comparando(&ex, &ey) < 0)
        {
            fwrite(&ex, sizeof(Endereco), 1, saida);
            fread(&ex, sizeof(Endereco), 1, x);
        }
        else
        {
            fwrite(&ey, sizeof(Endereco), 1, saida);
            fread(&ey, sizeof(Endereco), 1, y);
        }
    }

    while (!feof(x))
    {
        fwrite(&ex, sizeof(Endereco), 1, saida);
        fread(&ex, sizeof(Endereco), 1, x);
    }
    while (!feof(y))
    {
        fwrite(&ey, sizeof(Endereco), 1, saida);
        fread(&ey, sizeof(Endereco), 1, y);
    }

    fclose(x);
    fclose(y);
    fclose(saida);
}

int  comparando(const void *x1, const void *y2)
{
    return strncmp(((Endereco *)x1)->cep, ((Endereco *)y2)->cep, 8);
}
int main()
{
	printf("     ------------------------------------------trabalho de arquivo--------------------------------------------\n\n\n");
    FILE *f, *saida;
    char *file = "cep.dat.part";  // variavel que armazena o nome do arquivo com a extensao do arquivo
    long qtdMaxRegPorBloco = 50000; 
    int indice = 0;
    int inicio = 0;
    char dados[100];
	int auxiliar,contador;
    Endereco *endereco;
    int ultArq = 0;
   

    f = fopen(file , "r"); 
    if (f == NULL)
    {
        printf("Nao foi possivel abrir esse arquivo.");
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    long quantidadeRegistros = tamanho / sizeof(Endereco);
    printf("A quantidade de Registros no %s: %d registros\n", file, quantidadeRegistros);
    long quantidadeBloco = pow(2, ceil(log2(quantidadeRegistros/ qtdMaxRegPorBloco)));
    printf("A quantidade de Blocos: %d\n", quantidadeBloco);
    long RegistroPorBloco = (int)ceil((float)quantidadeRegistros / quantidadeBloco);
    printf("Quantidade de Registro por Bloco: %d registros\n\n", (RegistroPorBloco));
    rewind(f);
    endereco = (Endereco *)malloc(RegistroPorBloco * sizeof(Endereco));
    
    int fase = log2(quantidadeBloco);
   while(inicio < quantidadeBloco)
    {
        if (inicio == quantidadeBloco - 1){         
            RegistroPorBloco =  quantidadeRegistros; 
       }
        //ordenando os blocos de arquivos
        qsort(endereco,  RegistroPorBloco, sizeof(Endereco),  comparando);
        
        sprintf(dados, "cep_bloco_%d.dat", inicio);
        saida = fopen(dados, "w");
        fwrite(endereco, sizeof(Endereco), RegistroPorBloco, saida);
        fclose(saida);       
        quantidadeRegistros -= RegistroPorBloco;   
        ultArq++;
        inicio++;
    }
    free(endereco);
    fclose(f); 
   
   

    while (fase > 0)
    { 
        printf("\n");
        char arq1[50], arq2[50], arqSaida[50];
        auxiliar = ultArq;
        quantidadeBloco =quantidadeBloco / 2;
        contador = 0;
        printf("fase  %d:\n", fase);
        while (contador < quantidadeBloco)
        {         
            sprintf(arq1, "cep_bloco_%d.dat", indice++);
            sprintf(arq2, "cep_bloco_%d.dat", indice++);     
            sprintf(arqSaida, "cep_bloco_%d.dat", ultArq++);
            printf("ja esta ordenado. Agora estou intercalar o '%s' com '%s' entao temos: '%s'\n", arq1, arq2, arqSaida);
		    intercalando(arq1, arq2, arqSaida);
           
			remove(arq2);
            remove(arq1);
            

            if (contador == quantidadeBloco - 1){
                indice = auxiliar;
        }
            ++contador;
                 
        }
        --fase;
    
    }
   
    system("pause");
    return 0;
    
}


    
