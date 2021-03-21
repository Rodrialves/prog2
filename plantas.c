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
	int i = 0;
	planta *nova = (planta *)malloc(sizeof(planta));

	if (nova == NULL)
		return NULL;

	if (strlen(ID) > 10 || strlen(nome_cientifico) > MAX_NAME)
		return NULL;

	*nova->ID = ID;
	*nova->nome_cientifico = nome_cientifico;
	nova->n_alcunhas = n_alcunhas;
	nova->n_sementes = n_sementes;
	nova->alcunhas = alcunhas;

	return nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	colecao *c_nova = (colecao *)malloc(sizeof(colecao));
	if (colecao == NULL)
		return NULL;
	return c_nova;
}
int planta_insere(colecao *c, planta *p)
{
	if (p != NULL && planta_nova(ID, nome_cientifico, alcunhas, n_alcunhas, n_sementes) != NULL)
		return 0;
	tipo_ordem if (strcmp(p, colecao->plantas->ID) == 0) do
	{
		planta_nova(ID, nome_cientifico, alcunhas, n_alcunhas, n_sementes);
		while (coelcao->plantas !=)
			return 1;
		if (p = NULL)
			return -1;
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
