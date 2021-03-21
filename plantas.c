/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PATH "db_small.txt"

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	int i;
	planta *nova = (planta *)malloc(sizeof(planta));

	if (nova == NULL)
		return NULL;

	if (strlen(ID) > 10 || strlen(nome_cientifico) > MAX_NAME)
		return NULL;

	for(i=0;i<strlen(ID);i++)
	{
		nova->ID[i]=ID[i];
	}

	for(i=0;i<strlen(nome_cientifico);i++)
	{
		nova->nome_cientifico[i] = nome_cientifico[i];
	}
	
	nova->n_alcunhas = n_alcunhas;
	nova->n_sementes = n_sementes;
	nova->alcunhas = alcunhas;

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{

	int i;
	colecao *nova = (colecao *)malloc(sizeof(colecao));

	if (nova == NULL)
		return NULL;
	
	if(strcmp("nome",tipo_ordem)!=0)
	{
		if(strcmp("id",tipo_ordem)!=0)
			return NULL;
	}

	nova->plantas = NULL;
	nova->tamanho = 0;

	for(i=0; i<strlen(tipo_ordem);i++)
		nova->tipo_ordem[i]= tipo_ordem[i];

	return nova;
}

int planta_insere(colecao *c, planta *p)
{
	int i,flag=0,k=0,j,count=0;
	if (p == NULL)
		return -1;

	for(i=0;i<c->tamanho;i++)
	{
		if(strcmp(c->plantas[i]->ID,p->ID)!=0)
		{
			flag++;
			k=i;
			break;
		}
	}

	if(flag)
	{
		c->plantas[k]->n_sementes += p->n_sementes;
		for(i=0;i<c->plantas[k]->n_alcunhas;i++)
		{
			for(j=0;j<p->n_alcunhas;j++)
			{
				if(strcmp(c->plantas[k]->alcunhas[j],p->alcunhas[i])!=0)
					count++;
			}

			if(count==c->plantas[k]->n_alcunhas)
			{
				c->plantas[k]->n_alcunhas++;
				c->plantas[k]->alcunhas=(char **)realloc(c->plantas[k]->alcunhas,sizeof(char*)*c->plantas[k]->n_alcunhas);
			}
		}
	}	
	


}
int colecao_tamanho(colecao * c)
{
	return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}
planta *planta_remove(colecao * c, const char *nomep)
{
	return NULL;
}

int planta_apaga(planta * p)
{
	return -1;
}
int colecao_apaga(colecao * c)
{
	return -1;
}
int *colecao_pesquisa_nome(colecao * c, const char *nomep, int *tam)
{
	return NULL;
}
int colecao_reordena(colecao * c, const char *tipo_ordem)
{
	return -1;
}
