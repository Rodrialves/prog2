/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PATH "db_small.txt"
#define MAX_LINE 500
#define TOKENS ","

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	int i;
	planta *nova = (planta *)malloc(sizeof(planta));

	//verificacoes
	if (nova == NULL)
		return NULL;

	if (strlen(ID) > 10 || strlen(nome_cientifico) > MAX_NAME)
		return NULL;

	//guarda informacoes da planta
	strcpy(nova->ID, ID);
	strcpy(nova->nome_cientifico, nome_cientifico);
	nova->n_alcunhas = n_alcunhas;
	nova->n_sementes = n_sementes;

	//aloca
	nova->alcunhas = (char **)calloc(n_alcunhas, sizeof(char *));
	for (i = 0; i < n_alcunhas; i++)
	{
		nova->alcunhas[i] = (char *)malloc((strlen(alcunhas[i]) + 1) * sizeof(char));
		strcpy(nova->alcunhas[i], alcunhas[i]);
	}

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{

	int i;
	colecao *nova = (colecao *)calloc(1, sizeof(colecao));

	//verificacoes
	if (nova == NULL)
		return NULL;
	if (strcmp("nome", tipo_ordem) != 0)
	{
		if (strcmp("id", tipo_ordem) != 0)
			return NULL;
	}

	strcpy(nova->tipo_ordem, tipo_ordem);

	return nova;
}

int planta_insere(colecao *c, planta *p)
{
	int i, flag = 0, k = 0, j = 0, count = 0;
	planta *aux;

	//verificacoes
	if (p == NULL || c == NULL)
		return -1;

	//caso lista vazia
	if (c->tamanho == 0)
	{
		c->tamanho++;
		c->plantas = (planta **)realloc(c->plantas, c->tamanho * sizeof(planta *));
		c->plantas[c->tamanho - 1] = p;

		return 0;
	}

	//verifica id existe//
	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(c->plantas[i]->ID, p->ID) == 0)
		{
			flag++;
			k = i;
		}
	}

	//caso já exista//
	if (flag)
	{
		//atualiza seeds
		c->plantas[k]->n_sementes += p->n_sementes;

		for (i = 0; i < p->n_alcunhas; i++)
		{
			//conta quantas alcunhas de c->plantas[k] são diferentes de p->alcunhas[i]
			for (j = 0; j < c->plantas[k]->n_alcunhas; j++)
			{
				if (strcmp(c->plantas[k]->alcunhas[j], p->alcunhas[i]) != 0)
					count++;
			}

			//verifica se alcunha de p já existe em c->plantas[k]->alcunhas
			if (count == c->plantas[k]->n_alcunhas)
			{
				//atualiza alcunhas
				c->plantas[k]->n_alcunhas++;
				c->plantas[k]->alcunhas = (char **)realloc(c->plantas[k]->alcunhas, sizeof(char *) * c->plantas[k]->n_alcunhas);
				if (c->plantas[k]->alcunhas == NULL)
					return -1;
				c->plantas[k]->alcunhas[c->plantas[k]->n_alcunhas - 1] = (char *)realloc(c->plantas[k]->alcunhas[c->plantas[k]->n_alcunhas - 1], sizeof(char) * (strlen(p->alcunhas[i]) + 1));
				if (c->plantas[k]->alcunhas[c->plantas[k]->n_alcunhas - 1] == NULL)
					return -1;
				strcpy(c->plantas[k]->alcunhas[c->plantas[k]->n_alcunhas - 1], p->alcunhas[i]);
			}
		}

		return 1;
	}

	//caso não exista

	c->plantas = (planta **)realloc(c->plantas, sizeof(planta *) * (c->tamanho + 1));
	c->plantas[c->tamanho] = p;
	c->tamanho++;

	//ID

	if (strcmp(c->tipo_ordem, "id") == 0)
	{
		for (i = 0; i < c->tamanho; i++)
		{
			if (strcmp(c->plantas[c->tamanho - 1]->ID, c->plantas[i]->ID) < 0)
			{
				break;
			}
		}

		aux = c->plantas[c->tamanho - 1];

		for (j = c->tamanho - 1; j > i; j--)
		{
			c->plantas[j] = c->plantas[j - 1];
		}

		c->plantas[i] = aux;
		return 0;
	}

	//NOME

	if (strcmp(c->tipo_ordem, "nome") == 0)
	{
		for (i = 0; i < c->tamanho; i++)
		{
			if (strcmp(c->plantas[c->tamanho - 1]->nome_cientifico, c->plantas[i]->nome_cientifico) < 0)
			{
				break;
			}
		}

		aux = c->plantas[c->tamanho - 1];

		for (j = c->tamanho - 1; j > i; j--)
		{
			c->plantas[j] = c->plantas[j - 1];
		}

		c->plantas[i] = aux;
		return 0;
	}

	return -1;
}

int colecao_tamanho(colecao *c)
{
	if (c == NULL)
		return -1;

	return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	// int i, n_sementes = 0, n_alcunhas = 0;
	// char aux[MAX_LINE], nome_cientifico[MAX_NAME] , ID[10], num;
	// char *token;
	// char **alcunhas= calloc(1, sizeof(char *));
	// planta *p;
	// colecao *c_nova = colecao_nova(tipo_ordem);
	// FILE *f = fopen(nome_ficheiro, "r");

	// //verificacoes
	// if (nome_ficheiro == NULL || tipo_ordem == NULL || f == NULL)
	// 	return NULL;

	// //le e copia
	// while (fgets(aux, MAX_LINE, f) != NULL)
	// {
	// 	if (aux[strlen(aux) - 1] == '\n')
	// 		aux[strlen(aux) - 1] = '\0';

	// 	printf("%s\n", aux);

	// 	token = strtok(aux, TOKENS);
	// 	strcpy(ID, token);
	// 	// printf("\n%s",ID);
	// 	token = strtok(NULL, TOKENS);
	// 	strcpy(nome_cientifico, token);
	// 	// printf(" %s",nome_cientifico);
	// 	token = strtok(NULL, TOKENS);
	// 	n_sementes=atoi(token);
	// 	// printf(" %i",n_sementes);
	// 	token = strtok(NULL, TOKENS);
	// 	//caso tenha alcunhas
	// 	while (token != NULL)
	// 	{
	// 		printf("%i",n_alcunhas);
	// 		alcunhas = realloc(alcunhas, sizeof(char*)*(n_alcunhas + 1));
	// 		alcunhas[n_alcunhas] = (char *)calloc(1,sizeof(char) * (strlen(token)+1));
	// 		strcpy(alcunhas[n_alcunhas], token);
	// 		token = strtok(NULL, TOKENS);

	// 		n_alcunhas++;
	// 		printf(" %s",alcunhas[n_alcunhas-1]);
	// 		printf("   %s",token);
	// 	}
	// 	printf("\n");
	// 	printf("%i",n_alcunhas);
	// 	//prepara proxima iteracao
	// 	p = planta_nova(ID, nome_cientifico, alcunhas, n_alcunhas, n_sementes);
	// 	planta_insere(c_nova, p);
	// 	planta_apaga(p);
		
	// 	for(i=0;i<n_alcunhas;i++)
	// 	{
	// 		free(alcunhas[i]);
	// 	}
	// 	//coloca a zero
	// 	n_alcunhas = 0;
	// 	n_sementes = 0;
	// }
	// free(alcunhas);
	// fclose(f);

	return NULL;
}

planta *planta_remove(colecao *c, const char *nomep)
{
	int i, k = 0;

	//verificacoes
	if (c == NULL || nomep == NULL)
		return NULL;
	//procura planta a remover
	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(nomep, c->plantas[i]->nome_cientifico) == 0)
		{
			k = i;
		}
	}
	//ajusta posicoes
	for (i = k; i < c->tamanho; i++)
	{
		c->plantas[i] = c->plantas[i + 1];
	}

	c->tamanho--;

	return c->plantas[k];
}

int planta_apaga(planta *p)
{
	int i;

	if (p == NULL)
		return -1;
	//liberta
	for (i = 0; i < p->n_alcunhas; i++)
	{
		free(p->alcunhas[i]);
	}
	free(p->alcunhas);
	free(p);

	return 0;
}

int colecao_apaga(colecao *c)
{
	int i;

	if (c == NULL)
		return -1;
	//liberta
	for (i = 0; i < c->tamanho; i++)
	{
		planta_apaga(c->plantas[i]);
	}
	free(c);
	return 0;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	int i, n = 0, j = 0;
	int *indice = (int *)calloc(1, sizeof(int));

	if (c == NULL)
		return NULL;
	//procura nome
	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(nomep, c->plantas[i]->nome_cientifico) == 0)
		{
			indice = (int *)realloc(indice, (n + 1) * sizeof(int));
			indice[n] = i;
			n++;
		}
		//procura alcunhas
		for (j = 0; j < c->plantas[i]->n_alcunhas; j++)
		{
			if (strcmp(nomep, c->plantas[i]->alcunhas[j]) == 0)
			{
				indice = (int *)realloc(indice, (n + 1) * sizeof(int));
				indice[n] = i;
				n++;
			}
		}
	}

	*tam = n;

	return indice;
}

int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	int i,j,min=0;
	planta *p=(planta*)calloc(1,sizeof(planta));
	//verificacoes
	if (c == NULL)
		return -1;
	if (strcmp("nome", tipo_ordem) != 0)
		{
			if (strcmp("id", tipo_ordem) != 0)
				return -1;
			}
	if(strcmp(tipo_ordem,c->tipo_ordem)==0)
		return 0;

	p=c->plantas[0];
	
	if(strcmp(tipo_ordem,"id")==0)
	{
		for(j=0;j<c->tamanho-1;j++)
		{
			for(i=j;i<c->tamanho;i++)
			{
				if(strcmp(p->ID,c->plantas[i]->ID)>0)
				{
					min=i;
					p=c->plantas[min];	
				}
			}
			p=c->plantas[min];
			c->plantas[min]=c->plantas[j];
			c->plantas[j]=p;
			min=j;
			p=c->plantas[min];
		}
	}

	if(strcmp(tipo_ordem,"nome")==0)
	{
		for(j=0;j<c->tamanho-1;j++)
		{
			for(i=j;i<c->tamanho;i++)
			{
				if(strcmp(p->nome_cientifico,c->plantas[i]->nome_cientifico)>0)
				{
					min=i;
					p=c->plantas[min];	
				}
			}
			p=c->plantas[min];
			c->plantas[min]=c->plantas[j];
			c->plantas[j]=p;
			min=j;
			p=c->plantas[min];
		}
	}
 
	return 1;
}
