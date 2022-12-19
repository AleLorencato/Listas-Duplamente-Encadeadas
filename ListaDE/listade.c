#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listade.h"

void criaLista(ListaDE *lt)
{
   lt->inicio = NULL;
   lt->fim = NULL;
   lt->n = 0;
}

void exibe(ListaDE lt)
{
   Nodo *pAux;
   pAux = lt.inicio;
   printf("\nExibindo a Lista\n");
   printf("Inicio: %p \n", lt.inicio);
   printf("[End Ant] [cd] [End Nodo] [peso] [End Prox]\n");
   while (pAux != NULL)
   {
      printf("%p - %3d %p %.2f - %p\n", pAux->ant, pAux->info.cod, pAux, pAux->info.peso, pAux->prox);
      pAux = pAux->prox;
   }
   printf("Fim: %p - N= %d\n", lt.fim, lt.n);
}

int quantidadeDeNodos(ListaDE *lt)
{
   return lt->n;
}

int incluiNoInicio(ListaDE *lt, Dado d)
{
   Nodo *pNodo;
   pNodo = (Nodo *)malloc(sizeof(Nodo));
   if (pNodo == NULL)
      return (FALTOU_MEMORIA);
   else
   {
      pNodo->info = d;
      pNodo->prox = lt->inicio;
      pNodo->ant = NULL;

      if (lt->n == 0)
         lt->fim = pNodo;
      else
         lt->inicio->ant = pNodo;

      lt->inicio = pNodo;
      lt->n++;
      return (SUCESSO);
   }
}

int incluiNoFim(ListaDE *lt, Dado d)
{
   Nodo *pNodo;
   pNodo = (Nodo *)malloc(sizeof(Nodo));
   if (pNodo == NULL)
      return (FALTOU_MEMORIA);
   else
   {
      pNodo->info = d;
      pNodo->ant = lt->fim;
      pNodo->prox = NULL;

      if (lt->n == 0)
         lt->inicio = pNodo;
      else
         lt->fim->prox = pNodo;

      lt->fim = pNodo;
      lt->n++;
      return SUCESSO;
   }
}

int estaVazia(ListaDE lt)
{
   if (lt.n == 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int excluiDoInicio(ListaDE *lt, Dado *d)
{
   Nodo *pNodo;
   if (lt->n == 0)
      return LISTA_VAZIA;
   else
   {
      *d = lt->inicio->info;
      pNodo = lt->inicio;
      lt->inicio = lt->inicio->prox;
      if (lt->n == 1)
         lt->fim = NULL;
      else
         lt->inicio->ant = NULL;
      lt->n--;
      free(pNodo);
      return SUCESSO;
   }
}
int excluiDoFim(ListaDE *lt, Dado *d)
{
   Nodo *pNodo;
   if (lt->n == 0)
      return LISTA_VAZIA;
   else
   {
      *d = lt->fim->info;
      pNodo = lt->fim;
      lt->fim = lt->fim->ant;
      if (lt->n == 1)
         lt->inicio = NULL;
      else
         lt->fim->prox = NULL;
      lt->n--;
      free(pNodo);
      return SUCESSO;
   }
}

int excluiNodo(ListaDE *lt, int cod, Dado *d)
{
   Nodo *pNodo;
   pNodo = lt->inicio;
   int achouNodo, i;
   achouNodo = 0;
   if (lt->n == 0)
      return LISTA_VAZIA;
   for (i = 0; i < lt->n; i++)
   {
      if (cod == pNodo->info.cod)
      {
         achouNodo++;
         break;
      }
      pNodo = pNodo->prox;
   }
   if (achouNodo == 1)
   {
      if (lt->n == 1)
      {
         lt->inicio = NULL;
      }
      if (pNodo->prox == NULL)
      {
         excluiDoFim(lt, d);
         return SUCESSO;
      }
      else
      {
         *d = pNodo->info;
         pNodo->ant->prox = pNodo->prox;
         pNodo->prox->ant = pNodo->ant;
         lt->n--;
         free(pNodo);
         return SUCESSO;
      }
   }
   return CODIGO_INEXISTENTE;
}

int consultaPorCodigo(ListaDE *lt, int cod, Dado *d)
{
   Nodo *pNodo;
   pNodo = lt->inicio;
   int i;
   for (i = 0; i < lt->n; i++)
   {
      if (cod == pNodo->info.cod)
      {
         *d = pNodo->info;
         return SUCESSO;
      }
      pNodo = pNodo->prox;
   }
   return CODIGO_INEXISTENTE;
}

int incluiDepois(ListaDE *lt, Dado d, int cod)
{
   Nodo *pNodo, *pAux;
   pNodo = (Nodo *)malloc(sizeof(Nodo));
   if (pNodo == NULL)
      return (FALTOU_MEMORIA);
   pAux = lt->inicio;
   int i, achouNodo;
   achouNodo = 0;
   for (i = 0; i < lt->n; i++)
   {
      if (cod == pAux->info.cod)
      {
         achouNodo++;
         break;
      }
      pAux = pAux->prox;
   }
   if (achouNodo == 1)
   {
      if (pAux->prox == NULL)
      {
         incluiNoFim(lt, d);
      }
      else
      {
         pNodo->prox = pAux->prox;
         pNodo->ant = pAux;
         pAux->prox = pNodo;
         pNodo->info = d;
         pNodo->prox->ant = pNodo;
         lt->n++;
         return SUCESSO;
      }
   }
}

void leArquivo(ListaDE *lt)
{
   FILE *stream;
   char nomeArq[10];
   Dado dado;

   strcpy(nomeArq, "dados.txt");

   if ((stream = fopen(nomeArq, "r")) == NULL)
   {
      printf("Nao foi possivel abrir %s\n", nomeArq);
   }
   else
   {
      criaLista(lt);
      while (fscanf(stream, "%d %f\n", &dado.cod, &dado.peso) != EOF)
      {
         incluiNoFim(lt, dado);
      }
      fclose(stream);
      printf("Importacao Realizada com Sucesso!\n");
   }
}
void gravaArquivo(ListaDE *lt)
{
   FILE *stream;
   char nomeArq[10];
   int i;
   Nodo *pNodo;
   pNodo = lt->inicio;
   strcpy(nomeArq, "dados.txt");

   if ((stream = fopen(nomeArq, "w")) == NULL)
   {
      printf("Nao foi possivel abrir %s\n", nomeArq);
   }
   else
   {
      for (i = 0; i < lt->n; i++)
      {
         fprintf(stream, "%d %.2f\n", pNodo->info.cod, pNodo->info.peso);
         pNodo = pNodo->prox;
      }
      fclose(stream);
      printf("Gravacao Realizada com Sucesso!\n");
   }
}