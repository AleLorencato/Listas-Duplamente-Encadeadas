#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listade.h"

int main()
{
  int op, cd, peso, qt;
  ListaDE lt;
  Dado d;

  criaLista(&lt);

  do
  {
    printf("\n0. Fim                         5. Exclui do Inicio         10. Exclui Nodo\n");
    printf("1. Inclui no Inicio            6. Inclui no Fim              11. le Arquivo\n");
    printf("2. Exibe Lista                 7. Exclui do Fim            12. Grava Arquivo\n");
    printf("3. Quantidade de Nodos         8. Consulta por Codigo      \n");
    printf("4. Exibe Situacao da Lista     9. Inclui Depois      \n");
    printf("Operacao: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      printf("[cd][peso]\n");
      scanf(" %d %f", &d.cod, &d.peso);
      if (incluiNoInicio(&lt, d) == 0)
        printf("Operacao Realizada com Sucesso!\n");
      else
        printf("Operacao NAO realizada: Faltou Memoria!");
      break;
    case 2:
      break;
    case 3:
      printf("Quantidade de Nodos= %d\n", quantidadeDeNodos(&lt));
      break;
    case 4:
      break;
    case 5:
      if (excluiDoInicio(&lt, &d) == LISTA_VAZIA)
        printf("A lista está vazia!!");
      else
      {
        printf("Operacao Realizada com Sucesso!\n");
        printf("Dado excluido:%d %.2f\n", d.cod, d.peso);
      }
      break;
    case 6:
      printf("[cd][peso]\n");
      scanf(" %d %f", &d.cod, &d.peso);
      if (incluiNoFim(&lt, d) == 0)
        printf("Operacao Realizada com Sucesso!\n");
      else
        printf("Operacao NAO realizada: Faltou Memoria!");
      break;
    case 7:
      if (excluiDoFim(&lt, &d) == LISTA_VAZIA)
        printf("A lista está vazia!!");
      else
      {
        printf("Operacao Realizada com Sucesso!\n");
        printf("Dado excluido:%d %.2f\n", d.cod, d.peso);
      }
      break;
    case 8:
      printf("Digite o código do nodo que voce quer consultar: ");
      scanf("%d", &cd);
      if (consultaPorCodigo(&lt, cd, &d) == CODIGO_INEXISTENTE)
      {
        printf("Operacao NAO realizada: CODIGO INEXISTENTE!");
      }
      else
      {
        printf("Operacao Realizada com Sucesso!\n");
        printf("Dado consultado:%d %.2f\n", d.cod, d.peso);
      }
      cd = 8;
      break;
    case 9:
      printf("Digite o código do nodo que voce vai inserir depois: ");
      scanf("%d", &cd);
      printf("[cd][peso]\n");
      scanf(" %d %f", &d.cod, &d.peso);
      if (incluiDepois(&lt, d, cd) == SUCESSO)
        printf("Operacao Realizada com Sucesso!\n");
      else
        printf("Operacao NAO realizada: CODIGO INEXISTENTE!");
      break;
    case 10:
      printf("Digite o código do nodo que deseja excluir: ");
      scanf("%d", &cd);
      qt = excluiNodo(&lt, cd, &d);
      if (qt == LISTA_VAZIA)
        printf("A lista está vazia!!");
      else if (qt == CODIGO_INEXISTENTE)
      {
        printf("Operacao NAO realizada: CODIGO INEXISTENTE!");
      }
      else
      {
        printf("Operacao Realizada com Sucesso!\n");
        printf("Dado de cod %d excluido!", cd);
      }
      break;
    case 11:
      leArquivo(&lt);
      break;
    case 12:
      gravaArquivo(&lt);
      break;
    }
    exibe(lt);
  } while (op != 0);

  return (0);
}
