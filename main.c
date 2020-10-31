#include <stdio.h>
#include <stdlib.h>
#include "ordenacoes.h"
#include <string.h>
#include <windows.h>
void cls(void)
{
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '),
                   dwConSize, coordScreen, &cCharsWritten);

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                               dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}


void geraArqAleatorio(char* nome_arquivo, int num_registros){
  //Gera Arquivos aleatorios para o meu caso de testes
  int r;
  FILE* arq = fopen(nome_arquivo, "w");
  if(arq != NULL){
     for(int i = 0; i < num_registros; i++){
        r = rand()%1000;
        fprintf(arq, "%d\n", r);
    }
  }
  fclose(arq);
}
void ordenaArquivo(char* arquivo, int num_registros){
    //Ordena os arquivos que estiverem no formato especificado "ArquivoN.txt"
    FILE* arq = fopen(arquivo, "r");
    int dados[num_registros];

    //Copia os registros do arquivo para memoria principal atraves de um vetor
    for(int c = 0;c<num_registros;c++){
      fscanf(arq, "%d", &dados[c]);
    }

    int indMax = sizeof(dados)/sizeof(dados[0]);
    quicksort(dados, 0, indMax-1);
    fclose(arq);
    //Apos o vetor estar ordenado, escreve de volta no arquivo.
    arq = fopen(arquivo, "w");
    for(int k = 0;k<num_registros;k++){
      fprintf(arq, "%d\n", dados[k]);
    }
    fclose(arq);

}

void geraArqAleatorioOrdenado(char* nome_arquivo, int num_registros){
  geraArqAleatorio(nome_arquivo, num_registros);
  ordenaArquivo(nome_arquivo, num_registros);
}

void merge(int num_arquivos, int num_registros){
  char nome_arq[20];
  FILE* arq[num_arquivos];
  //Abre os arquivos
  for(int i =0; i<num_arquivos;i++){
    sprintf(nome_arq,"Arquivo%d.txt", i);
    arq[i] = fopen(nome_arq, "r");
    if(arq[i] == NULL){
      printf("\nERRO!\n");
    }
  }

  int arquivosFechados = 0;
  //Faz o merge
  int buffer[num_arquivos];

  int menor = 32767;
  int indMenor = -1;

  int ultimoNumero = -32767;
  FILE* arqSaida = fopen("saida.txt", "w");
  //Coloca 1 valor de cada arquivo no buffer cujo tamanho é a quantidade de partiçoes
  for(int k = 0;k<num_arquivos;k++){
          fscanf(arq[k],"%d", &buffer[k]);

      }
  printf("[ ]");
  char loading[20] = "";
  float load = 0;
  float percent = num_arquivos/10;
  float dezena = 0;
  printf("percent = %.2f", percent);
  do{
    //Procura menor
    for(int z = 0;z<num_arquivos;z++){
      if(buffer[z] < menor){
        menor = buffer[z];
        indMenor = z;
      }
    }
    //Verifica se o menor já nao foi escrito por ultimo no arquivo de saída, caso nao, escreve no arq
    if(ultimoNumero != menor){
      fprintf(arqSaida, "%d\n", menor);
      ultimoNumero = menor;
      menor = 32765;
    }else{
      fscanf(arq[indMenor], "%d", &buffer[indMenor]);
      menor = 32765;
    }
    if(!feof(arq[indMenor])){
      fscanf(arq[indMenor], "%d", &buffer[indMenor]); // coloca um elemento na posiçao do vetor que teve o elemento "retirado
    }else{
      buffer[indMenor] = 32765;
      fclose(arq[indMenor]);
      indMenor = 0;
      arquivosFechados++;

    }

    if(arquivosFechados == (percent * dezena)){
        cls();
        strcat(loading, "- ");
        printf("[%s]\n", loading);
        Sleep(250); //Sleep com S maiusculo é fornecido pela API do windows, está em milisegundos.
        dezena++;
      }

  }while(arquivosFechados < num_arquivos);
  fflush(arqSaida);
  fclose(arqSaida);
}

int main()
{   srand(time(NULL));
    char nome_arq[20];

    int num_reg = 50; //num de registros por arquivo "tamanho da particao"
    int num_arquivos = 10; //Quantidade de arquvios gerados "quantidade de particoes"

    for(int k = 0; k<num_arquivos; k++){
      sprintf(nome_arq, "Arquivo%d.txt", k); //formata nome dos arquivos a serem criados
      geraArqAleatorioOrdenado(nome_arq, num_reg);//Gera arquivos aleatorios
    }
    merge(num_arquivos, num_reg);
    printf("Carregado!");
    return 0;
}
