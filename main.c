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

int main(int argc, char **argv) {

  int carro = 0, carrosatendidos = 0, opcao = 7;
  char opc = 'a', calibrar = 'X', txt;
  float litrosabas = 0, lucro = 0, litrosvendidos = 0;
  struct Scarro *filadecarros, *listaatendidos;
  FILE *arquivo;

  printf("\n%sPOSTO DE GASOLINA%s\n\n", PURPLE, NONE);

  float valor = 0;
  printf("Informe o valor do combusível (use o ponto, não a virgula. ex.: "
         "3.5):  ");
  while (valor <= 0) {
    scanf("%f", &valor);
    if (valor <= 0) {
      printf("Valor inválido, tente novamente.");
    }
  }

  int capacidade = 0;
  printf("\nInforme a capacidade da fila suportada pelo estabelecimento: ");
  while (capacidade <= 0) {
    scanf("%d", &capacidade);
    if (capacidade <= 0) {
      printf("Capacidade inválida, tente novamente.");
    }
  }

  filadecarros = (struct Scarro *)malloc(capacidade * sizeof(struct Scarro));
  if (filadecarros == NULL) {
    printf("Erro de alocacao");
    exit(0);
  }
  listaatendidos = (struct Scarro *)malloc(1 * sizeof(struct Scarro));
  if (listaatendidos == NULL) {
    printf("Erro de alocacao");
    exit(0);
  }

  float litros = 0;
  printf("\n\nInforme a quantidade de litros presente no tanque: ");
  while (litros <= 0) {
    scanf("%f", &litros);
    if (litros <= 0) {
      printf("Litros inválidos, tente novamente.");
    }
  }

  printf("\n%sO valor do combustível é de R$%.2f, a capacidade de fila nesse "
         "estabelecimento é de %d automóveis e a quantidade de litros "
         "presentes no tanque é de %.2f.%s\n\n",
         YELLOW, valor, capacidade, litros, NONE);

  timer();

  while (opcao != 6) {
    system("clear");
    printf("--- carros na fila: %d\n", carro);
    printf("--- capacidade de carros na fila: %d\n", capacidade);
    printf("--- vagas restantes: %d\n", (capacidade - carro));
    printf("--- litros no tanque: %.2f\n", litros);
    menuprinc();
    scanf("%d", &opcao);
    if (opcao > 6 && opcao <= 0)
      printf("%sOpção inválida. Tente novamente!%s", RED, NONE);
    else {
      switch (opcao) {
      case 1:
        if (carro >= capacidade) {
          printf("%sDesculpe, estamos com a capacidade máxima atingida.%s", RED,
                 NONE);
        } else {
          flush_in();
          printf("Qual a marca do seu carro: ");
          fgets(filadecarros[carro].marca, 15, stdin);
          filadecarros[carro].marca[strcspn(filadecarros[carro].marca, "\n")] =
              0;
          printf("Qual a placa do seu carro: ");

          fgets(filadecarros[carro].placa, 10, stdin);
          filadecarros[carro].placa[strcspn(filadecarros[carro].placa, "\n")] =
              0;
          printf("Qual a cor do seu carro: ");

          fgets(filadecarros[carro].cor, 15, stdin);
          filadecarros[carro].cor[strcspn(filadecarros[carro].cor, "\n")] = 0;

          printf("\nO carro foi adicionado!\n");
          carro = carro + 1;
          printf("O número atual de carros na fila é: %d", carro);
        }
        break;
      case 2:
        if (carro == 0) {
          printf(
              "\n%sNão foi possível abastecer! (Dica: você precisa adicionar "
              "um carro na fila primeiro.)%s",
              RED, NONE);
        } else {
          printf("\nQuantos litros deseja abastecer? ");
          scanf("%f", &litrosabas);
          if (litrosabas > litros) {
            printf("\n%sDesculpe, a gasolina disponível no posto é de %.2f.%s",
                   RED, litros, NONE);
            if (litros > 0) {
              printf("\nTente novamente. Quantos litros deseja abastecer?");
              scanf("%f", &litrosabas);
            } else {
              printf("%sSinto muito, estamos sem gasolina! TODOS OS CARROS "
                     "SERÃO REMOVIDOS.%s",
                     RED, NONE);
              carro = 0;
            }
          } else {
            if (litrosabas <= litros) {
              printf("O carro foi abastecido!\n");
              carro = carro - 1;
              litros = litros - litrosabas;
              litrosvendidos = litrosvendidos + litrosabas;
              lucro = litrosvendidos * valor;
              listaatendidos = (struct Scarro *)realloc(
                  listaatendidos,
                  (carrosatendidos + 1) * sizeof(struct Scarro));
              listaatendidos[carrosatendidos] = filadecarros[0];
              carrosatendidos = carrosatendidos + 1;
              for (int cont = 0; cont < carro; cont++) {
                filadecarros[cont] = filadecarros[cont + 1];
              }
              printf("\nO número de carros na fila é: %d", carro);
              printf("\nQuantidade de litros restantes no tanque: %.2f",
                     litros);
            }
          }
        }
        break;
      case 3:
        printf("%d carros na fila.", carro);
        imprimir(filadecarros, carro);
        break;
      case 4:
        flush_in();
        opc = 'h';
        while (opc != 'f') {
          system("clear");
          menurelat();
          scanf("%c", &opc);
          switch (opc) {
          case 'A':
          case 'a':
            printf("%.2f litros vendidos", litrosvendidos);
            break;
          case 'B':
          case 'b':
            printf("%.2f é o valor arrecadado com as vendas.", lucro);
            break;
          case 'C':
          case 'c':
            printf("%d carros atendidos.", carrosatendidos);
            break;
          case 'D':
          case 'd':
            printf("%.2f litros no tanque.", litros);
            break;
          case 'E':
          case 'e':
            arquivo = fopen("relatorio.txt", "w");
            if (arquivo == NULL)
              printf("Erro ao tentar abrir o arquivo.\nPressione enter para "
                     "continuar.\n");
            else {

              fprintf(
                  arquivo,
                  "%d carros na fila.\n%.2f litros vendidos.\n%.2f é o valor "
                  "arrecadado com as vendas.\n%.2f litros disponíveis no "
                  "posto.\n%d "
                  "carros atendidos.\n",
                  carro, litrosvendidos, lucro, litros, carrosatendidos);
              if (carrosatendidos > 0) {
                fprintf(arquivo, "\nCarros atendidos: ");
                for (int cont = 0; cont < carrosatendidos; cont++) {
                  fprintf(arquivo, "\n--- Carro %d ---", cont+1);
                  fprintf(arquivo, "\nmarca: %s", listaatendidos[cont].marca);
                  fprintf(arquivo, "\nplaca: %s", listaatendidos[cont].placa);
                  fprintf(arquivo, "\ncor: %s", listaatendidos[cont].cor);
                }
              }
              if (carro > 0) {
                fprintf(arquivo, "\n\nCarros na fila: ");
                for (int cont = 0; cont < carro; cont++) {
                  fprintf(arquivo, "\n--- Carro %d ---", cont+1);
                  fprintf(arquivo, "\nmarca: %s", filadecarros[cont].marca);
                  fprintf(arquivo, "\nplaca: %s", filadecarros[cont].placa);
                  fprintf(arquivo, "\ncor: %s", filadecarros[cont].cor);
                }
              }
              fclose(arquivo);
              printf("%sArquivo criado com sucesso!%s\nPressione enter para "
                     "continuar.\n",
                     GREEN, NONE);
            }

            break;
          case 'F':
          case 'f':
            printf("Pressione enter para voltar ao menu.");
            break;
          default:
            printf("Opção inválida\n");
          }
          if (opc != 'f' && opc != 'F') {
            limpatela();
          }
        }
        break;
      case 5:
        if (carro == 0) {
          printf("%sPrecisa adicionar um carro na fila primeiro!%s", RED, NONE);
        } else {
          printf("\nDeseja calibrar seus pneus?: (S ou N)\n");
          while (calibrar != 'S' && calibrar != 's' && calibrar != 'N' &&
                 calibrar != 'n') {
            scanf("%c", &calibrar);
          }
          switch (calibrar) {
          case 'S':
          case 's':
            printf("pneu calibrado!");
            carro = carro - 1;
            listaatendidos = (struct Scarro *)realloc(
                listaatendidos, (carrosatendidos + 1) * sizeof(struct Scarro));
            listaatendidos[carrosatendidos] = filadecarros[0];
            carrosatendidos = carrosatendidos + 1;
            for (int cont = 0; cont < carro; cont++) {
              filadecarros[cont] = filadecarros[cont + 1];
            }
            printf("\nO número de carros na fila é: %d", carro);
          }
          break;
        case 'N':
        case 'n':
          printf("Ok.");
          system("clear");
          break;
        }
        system("clear");
        break;
      case 6:
        printf("%sPrograma encerrado. Obrigada!%s\n", PURPLE, NONE);
        break;
      }
    }
    getchar();
    getchar();
  }
  return (EXIT_SUCCESS);
}
