#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define NONE "\033[0m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"

struct Scarro {
  char marca[15];
  char placa[10];
  char cor[15];
};

void flush_in() {
  int ch;
  do {
    ch = fgetc(stdin);
  } while (ch != EOF && ch != '\n');
}

void menuprinc() {
  printf("%s\n--- Menu principal, escolha uma opção: ---%s\n\n", BLUE, NONE);
  printf("1- adicionar um carro na fila.\n");
  printf("2- abastecer.\n");
  printf("3- exibir carros na fila de espera.\n");
  printf("4- relatórios.\n");
  printf("5- calibrar.\n");
  printf("6- encerrar.\n");
}

void menurelat() {
  printf("%s\n--- Menu de opções do relatório---%s\n\n", BLUE, NONE);
  printf("a- quantidade de litros vendida.\n");
  printf("b- valor total arrecadado com vendas.\n");
  printf("c- quantidade de carros atendida.\n");
  printf("d- quantidade de combustível restante no tanque. \n");
  printf("e- gerar arquivo para impressão. \n");
  printf("f- voltar ao menu anterior. \n");
  printf("Selecione uma opção: (apenas de 'a' a 'f'!!!) \n");
}

void limpatela() {
  getchar();
  getchar();
  system("clear");
}

void imprimir(struct Scarro cadastro[], int t) {
  for (int cont = 0; cont < t; cont++) {
    printf("\n%s--- Carro %d ---%s", PURPLE, cont+1, NONE);
    printf("\nmarca: %s", cadastro[cont].marca);
    printf("\nplaca: %s", cadastro[cont].placa);
    printf("\ncor: %s", cadastro[cont].cor);
  }
}

void timer() {
  sleep(3);
  system("clear");
}
