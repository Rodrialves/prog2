/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include "grafo.h"

tabela_dispersao *tabela_nova(int capacidade, hash_func *hfunc, sond_func *sfunc)
{
    if (!sfunc || !hfunc)
        return NULL;

    tabela_dispersao *t = malloc(sizeof(tabela_dispersao));
    if (!t)
        return NULL;

    t->capacidade = capacidade;
    t->tamanho = 0;

    t->nos = calloc(t->capacidade, sizeof(no_grafo *));
    if (!t->nos)
        return NULL;

    t->estado_celulas = calloc(t->capacidade, sizeof(int));
    if (!t->estado_celulas)
        return NULL;

    t->hfunc = hfunc;
    t->sfunc = sfunc;

    return t;
}

int tabela_adiciona(tabela_dispersao *td, no_grafo *entrada)
{
    if (td == NULL || entrada == NULL || td->capacidade == td->tamanho)
        return -1;

    int pos, atual, t = 1;

    pos = td->hfunc(entrada->cidade, td->capacidade);

    atual = pos;

    if (td->estado_celulas[pos] == 1)
    {
        do
        {
            atual = td->sfunc(pos, t, td->capacidade);
            t += 1;
        } while (td->estado_celulas[atual] == 1);
    }

    td->nos[atual] = entrada;
    td->estado_celulas[atual] = 1;
    td->tamanho += 1;

    return atual;
}

int tabela_remove(tabela_dispersao *td, no_grafo *saida)
{
    if (td == NULL || saida == NULL || td->tamanho == 0)
        return -1;

    int pos;

    pos = tabela_existe(td, saida->cidade);

    if (pos == -1)
        return -1;

    td->nos[pos] = NULL;
    td->estado_celulas[pos] = -1;
    td->tamanho -= 1;

    return 0;
}

void tabela_apaga(tabela_dispersao *td)
{
    if (!td || !td->nos || !td->estado_celulas)
        return;

    free(td->estado_celulas);
    free(td->nos);
    free(td);
}

int tabela_existe(tabela_dispersao *td, const char *cidade)
{
    if (!td || !cidade)
        return -1;

    int pos, i = 1, atual;

    pos = td->hfunc(cidade, td->capacidade);
    atual = pos;

    while (td->estado_celulas[atual] != 0)
    {
        if (td->nos[atual])
        {
            if (strcmp(cidade, td->nos[atual]->cidade) == 0)
            {
                return atual;
            }
        }

        atual = td->sfunc(pos, i, td->capacidade);

        if (i == td->capacidade)
            return -1;

        i++;
    }

    return -1;
}

tabela_dispersao *tabela_carrega(grafo *g, int tamanho)
{
    tabela_dispersao *td = tabela_nova(tamanho, hash_krm, sond_rh);
    if (!g || !td || g->tamanho > tamanho)
        return NULL;
    for (int i = 0; i < g->tamanho; i++)
    {
        tabela_adiciona(td, g->nos[i]);
    }

    return td;
}

/*================================================================================*/
unsigned long sond_rh(int pos, int tentativas, int tamanho)
{

    return (pos + tentativas * tentativas) % tamanho;
}

unsigned long hash_krm(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;
}
