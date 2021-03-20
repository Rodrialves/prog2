/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	FILE *f = fopen("db_small.txt", "r");
	int i = 0;
	nova
	char *token = strtok(ID, ",");
	planta *nova = (planta *)malloc(sizeof(planta));

	while (fscanf("%s,%s,%d", &planta->ID[i], &planta->nome_cientifico[i], &planta->n_sementes) == 3)
	//  while( token != NULL ) 
	//  	token = strtok(NULL, ","");

	{
		if (sizeof(planta->ID) > 10 || sizeof(planta->nome_cientifico) > MAX_NAME)
			return NULL;

		
		i++;
	}
	return nova;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	return NULL;
}
int planta_insere(colecao *c, planta *p)
{
	return -1;
}
int colecao_tamanho(colecao *c)
{
	return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	return NULL;
}

int planta_apaga(planta *p)
{
	return -1;
}
int colecao_apaga(colecao *c)
{
	return -1;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	return NULL;
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}
