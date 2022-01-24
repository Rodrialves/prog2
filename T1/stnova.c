/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "stnova.h"

estrutura *st_nova()
{
    estrutura *novo = calloc(1, sizeof(estrutura));

    if (!novo)
        return NULL;

    novo->tamanho = 0;
    novo->vec = NULL;

    return novo;
}

int st_insere(estrutura*st, no_grafo* no)
{
    int n;

	if (!no||!st)
		return -1;

    n=st->tamanho;

	if (st->tamanho==0)
	{
        st->vec=calloc(1,sizeof(no_grafo*));

        if(!st->vec)
            return -1;
	}

    else
    {
        st->vec=realloc(st->vec,(n+1)*sizeof(no_grafo*));

        if(!st->vec)
            return -1;
    }

    st->vec[st->tamanho]=no;

    st->tamanho +=1;

    return st->tamanho-1;
}

int st_importa_grafo(estrutura *st, grafo *g)
{
    if (!g || !st)
        return -1;

    for(int i=0;i<g->tamanho;i++)
    {
        if(st_insere(st,g->nos[i])==-1)
            return -1;
    }
    
    return 0;
}

char *st_pesquisa(estrutura *st, char *origem, char *destino)
{
    if(!st||origem==NULL||destino==NULL)
        return NULL;
    int i,k, pos=0,j;
    double min=INFINITY;
    char * codigo;
    no_grafo* aux=NULL;

    k=st->tamanho/2+st->tamanho%2;

    for(i=0;i<k;i++)
    {
        if(strcmp(st->vec[i]->cidade,origem)==0)
            aux = st->vec[i];

        if(strcmp(st->vec[st->tamanho-i-1]->cidade,origem)==0)
            aux = st->vec[st->tamanho-i-1];

   
        if(aux)
        {
            int n=aux->tamanho/2+aux->tamanho%2;

            for(j=0;j<n;j++)
            {
                if(strcmp(destino,aux->arestas[j]->destino->cidade)==0 && aux->arestas[j]->preco<min)
                {
                    min=aux->arestas[j]->preco;
                    pos=j;
                }

                if(strcmp(destino,aux->arestas[aux->tamanho-j-1]->destino->cidade)==0 && aux->arestas[aux->tamanho-j-1]->preco<min)
                {
                    min=aux->arestas[aux->tamanho-j-1]->preco;
                    pos=aux->tamanho-j-1;
                }
            }

            break;
        }
    }

    codigo=aux->arestas[pos]->codigo;
    return codigo;
}

// int st_remove(estrutura *st)
// {
// 	if (!st || st->tamanho==0)
// 		return 0;

//     st->tamanho-=1;

//     free(st->vec[st->tamanho]);

//     st->vec=realloc(st->vec,sizeof(no_grafo*)*(st->tamanho));
//     if(!st->vec)
//          return -1;
// 	return 1;
// }

int st_apaga(estrutura *st)
{
    if(!st)
        return -1;

    free(st->vec);
    free(st);
    return 0;
    
}
