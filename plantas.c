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

	strcpy(nova->ID, ID);
	strcpy(nova->nome_cientifico, nome_cientifico);
	nova->n_alcunhas = n_alcunhas;
	nova->n_sementes = n_sementes;

	nova->alcunhas = (char **)calloc(n_alcunhas, sizeof(char *));
	for (i = 0; i < n_alcunhas; i++)
	{
		nova->alcunhas[i] = (char *)malloc((strlen(alcunhas[i]) +1)*sizeof(char));
		strcpy(nova->alcunhas[i], alcunhas[i]);
	}

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{

	int i;
	colecao *nova = (colecao *)calloc(1, sizeof(colecao));

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
	//verificacoes
	if (p == NULL)
		return -1;

	//coleçao vazia
	if (c->tamanho == 0)
	{
		c->tamanho++;
		c->plantas = (planta **)calloc(1,sizeof(planta *));
		c->plantas[0] = p;

		return -1;
	}

	//verifica id existe//
	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(c->plantas[i]->ID, p->ID) == 0)
		{
			flag++;
			k = i;
			break;
		}
	}

	//caso já exista//
	if (flag)
	{
		//atualiza seeds
		c->plantas[k]->n_sementes += p->n_sementes;
		for (i = 0; i < c->plantas[k]->n_alcunhas; i++)
		{
			for (j = 0; j < p->n_alcunhas; j++)
			{
				if (strcmp(c->plantas[k]->alcunhas[j], p->alcunhas[i]) != 0)
					count++;
			}

			if (count == c->plantas[k]->n_alcunhas)
			{
				//atualiza alcunhas
				c->plantas[k]->n_alcunhas++;
				c->plantas[k]->alcunhas = (char **)realloc(c->plantas[k]->alcunhas, sizeof(char *) * c->plantas[k]->n_alcunhas);

			}
		}

		return 1;
	}

	//caso não exista--------------------------id-------------------------

	c->plantas = (planta **)realloc(c->plantas, sizeof(planta *) * (c->tamanho + 1));

	if (strcmp(c->tipo_ordem, "id") == 0)
	{
		for (i = 0; i < c->tamanho; i++)
		{
			if (strcmp(p->ID, c->plantas[i]->ID) < 0)
			{
				break;
			}
		}

		if (i == 0)
		{
			for (k = c->tamanho; k > 0; k--)
			{
				c->plantas[k] = c->plantas[k - 1];
			}
			c->plantas[0] = p;
			return 0;
		}

		if (i == c->tamanho)
		{
			c->plantas[c->tamanho] = p;
			return 0;
		}

		for (k = c->tamanho; k > i; k--)
		{
			c->plantas[k] = c->plantas[k - 1];
		}

		c->plantas[i] = p;
		c->tamanho++;

		return 0;
	}
	//-------------------------------nome----------------------------
	if (strcmp(c->tipo_ordem, "nome") == 0)
	{
		for (i = 0; i < c->tamanho; i++)
		{
			if (strcmp(p->nome_cientifico, c->plantas[i]->nome_cientifico) < 0)
			{
				break;
			}
		}

		if (i == 0)
		{
			for (k = c->tamanho; k > 0; k--)
			{
				c->plantas[k] = c->plantas[k - 1];
			}
			c->plantas[0] = p;
			return 0;
		}

		if (i == c->tamanho)
		{
			c->plantas[c->tamanho] = p;
			return 0;
		}

		for (k = c->tamanho; k > i; k--)
		{
			c->plantas[k] = c->plantas[k - 1];
		}

		c->plantas[i] = p;
		c->tamanho++;

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
	// col->tipo_ordem;
	// FILE *f=fopen(PATH,"r");
	// fclose(f);
	// return c_nova;
	return NULL;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	int i, k = 0;

	if (c == NULL || nomep == NULL)
		return NULL;

	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(nomep, c->plantas[i]->nome_cientifico) == 0)
		{
			k = i;
		}
	}

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

	for (i = 0; i < c->tamanho; i++)
	{
		if (strcmp(nomep, c->plantas[i]->nome_cientifico) == 0)
		{
			indice = (int *)realloc(indice, (n + 1) * sizeof(int));
			indice[n] = i;
			n++;
		}

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

	return 0;
}

int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}
