/*****************************************************************/
/*          Grafo direcionado | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "grafo.h"
#include "heap.h"

grafo *grafo_novo()
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->tamanho = 0;
    g->nos = NULL;

    return g;
}

no_grafo *encontra_no(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // pesquisa por cidade no vetor de nós
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, cidade) == 0)
            return g->nos[i];
    }
    return NULL;
}

no_grafo *no_insere(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // verifica se o nó já existe
    no_grafo *no = encontra_no(g, cidade);
    if (no)
        return NULL;

    // cria o novo nó para o user
    no = (no_grafo *)malloc(sizeof(no_grafo));
    if (!no)
        return NULL;

    // aloca espaço para o campo cidade
    no->cidade = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    if (!no->cidade)
    {
        free(no);
        return NULL;
    }
    // inicializa todos os campos
    strcpy(no->cidade, cidade);
    no->tamanho = 0;
    no->arestas = NULL;
    no->p_acumulado = 0;
    no->anterior = NULL;
    no->dataatualizada = NULL;

    // insere o nó criado no final do vetor de nós
    g->nos = (no_grafo **)realloc(g->nos, (g->tamanho + 1) * sizeof(no_grafo *));
    if (!g->nos)
    {
        free(no->cidade);
        free(no);
        return NULL;
    }
    // incrementa o tamanho do numero de nós e insere no vetor de apontadores de nós
    g->tamanho++;
    g->nos[g->tamanho - 1] = no;

    return no;
}

// função auxiliar que retorna 1 se existir a aresta para destino ou 0,
// se a aresta não existir, -1 se der erro
int existe_aresta(no_grafo *origem, no_grafo *destino, char *codigo)
{

    if (!origem || !destino)
        return -1;

    //pesquisa em todas as arestas se existe
    for (int i = 0; i < origem->tamanho; i++)
    {

        if ((origem->arestas[i]->destino == destino) && ((strcmp(origem->arestas[i]->codigo, codigo) == 0)))
            return 1;
    }

    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *companhia, data partida, data chegada, float preco, int lugares)
{
    if (!origem || !destino || !codigo || !companhia)
        return -1;

    if (preco < 0 || lugares < 0)
        return -1;

    // verifica se a ligação já existe
    if (existe_aresta(origem, destino, codigo) > 0)
        return -1;

    // cria a nova ligação
    aresta_grafo *ag = (aresta_grafo *)malloc(sizeof(aresta_grafo));
    if (!ag)
        return -1;

    ag->destino = destino;
    ag->preco = preco;
    ag->lugares = lugares;
    // aloca espaço para o código
    ag->codigo = (char *)malloc((strlen(codigo) + 1) * sizeof(char));
    if (!ag->codigo)
    {
        free(ag);
        return -1;
    }
    strcpy(ag->codigo, codigo);
    // aloca espaço para o companhia
    ag->companhia = (char *)malloc((strlen(companhia) + 1) * sizeof(char));
    if (!ag->companhia)
    {
        free(ag->codigo);
        free(ag);
        return -1;
    }
    strcpy(ag->companhia, companhia);

    // inicializa todos os campos
    ag->partida.tm_year = partida.tm_year;
    ag->partida.tm_mon = partida.tm_mon;
    ag->partida.tm_mday = partida.tm_mday;
    ag->partida.tm_hour = partida.tm_hour;
    ag->partida.tm_min = partida.tm_min;
    ag->partida.tm_sec = 0;
    ag->partida.tm_isdst = 0;

    // inicializa todos os campos
    ag->chegada.tm_year = chegada.tm_year;
    ag->chegada.tm_mon = chegada.tm_mon;
    ag->chegada.tm_mday = chegada.tm_mday;
    ag->chegada.tm_hour = chegada.tm_hour;
    ag->chegada.tm_min = chegada.tm_min;
    ag->chegada.tm_sec = 0;
    ag->chegada.tm_isdst = 0;

    // insere a nova ligação no vetor de ligações
    origem->arestas = (aresta_grafo **)realloc(origem->arestas, (origem->tamanho + 1) * sizeof(aresta_grafo *));
    if (!origem->arestas)
    {
        free(ag->codigo);
        free(ag->companhia);
        free(ag);
        return -1;
    }
    origem->tamanho++;
    origem->arestas[origem->tamanho - 1] = ag;

    return 0;
}

no_grafo *no_remove(grafo *g, char *cidade)
{
    //verificações
    if (g == NULL || cidade == NULL)
        return NULL;

    no_grafo *aux = NULL;
    int i, j;

    if (!encontra_no(g, cidade))
        return NULL;
    //percorre nós e arestas, efetua a remoção e ajusta o tamanho
    for (i = 0; i < g->tamanho; i++)
    {
        for (j = 0; j < g->nos[i]->tamanho; j++)
        {
            if (strcmp(g->nos[i]->arestas[j]->destino->cidade, cidade) == 0)
            {
                aresta_apaga(g->nos[i]->arestas[j]);
                g->nos[i]->arestas[j] = g->nos[i]->arestas[g->nos[i]->tamanho - 1];
                g->nos[i]->tamanho--;
                j--;
            }
        }
    }

    for (i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, cidade) == 0)
        {
            aux = g->nos[i];
            g->nos[i] = g->nos[g->tamanho - 1];
            g->tamanho -= 1;

            break;
        }
    }

    if (aux != NULL)
        return aux;

    return NULL;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if (aresta == NULL)
        return -1;
    //apaga a aresta e os seus campos
    free(aresta->codigo);
    free(aresta->companhia);
    free(aresta);

    return 0;
}

int no_apaga(no_grafo *no)
{
    if (!no)
        return -1;
    //apaga os campos da aresta
    free(no->cidade);
    free(no->dataatualizada);
    //percorre o nó para apagar cada aresta
    for (int i = 0; i < no->tamanho; i++)
    {
        aresta_apaga(no->arestas[i]);
    }
    free(no->arestas);
    free(no);
    return 0;
}

void grafo_apaga(grafo *g)
{
    if (!g)
        return;
    //percorre o grafo para apagar cada nó
    for (int i = 0; i < g->tamanho; i++)
    {
        no_apaga(g->nos[i]);
    }
    //apaga grafo e vetor nós
    free(g->nos);
    free(g);
}

no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos)
{
    if (!g || !codigo)
        return NULL;

    int i, j, flag = 1;
    no_grafo *aux;
    //percorre nós e arestas, quando encontra guarda a posição
    for (i = 0; i < g->tamanho; i++)
    {
        for (j = 0; j < g->nos[i]->tamanho; j++)
        {
            if (strcmp(g->nos[i]->arestas[j]->codigo, codigo) == 0)
            {
                flag = 0;
                *aresta_pos = j;
                aux = g->nos[i];
                break;
            }
        }
    }

    if (flag)
        return NULL;

    return aux;
}

int no_existe(no_grafo **no, int *n, char *cidade)
{
    //criada pelos estudantes
    if (!no)
        return 0;
    //percorre o nó, se econtrar a cidade retorna 1
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(no[i]->cidade, cidade) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int dia_compara(data a, data b)
{
    //criada pelos estudantes; se as datas forem iguais retorna 1
    if (a.tm_year == b.tm_year)
    {
        if (a.tm_mon == b.tm_mon)
        {
            if (a.tm_mday == b.tm_mday)
                return 1;
        }
    }

    return 0;
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n)
{
    if (!g || !destino || !n)
        return NULL;
    int i, j;
    //alocar memória
    no_grafo **aux = malloc(sizeof(no_grafo *));
    // percorre nós e arestas, se encontrar voos que cumpram os requisitos, adiciona-os ao vetor, realocando memória
    for (i = 0; i < g->tamanho; i++)
    {
        for (j = 0; j < g->nos[i]->tamanho; j++)
        {
            if (strcmp(g->nos[i]->arestas[j]->destino->cidade, destino) == 0 && g->nos[i]->arestas[j]->preco <= preco_max && dia_compara(g->nos[i]->arestas[j]->chegada, chegada) && !no_existe(aux, n, destino))
            {
                *n += 1;
                aux = realloc(aux, *n * sizeof(no_grafo *));
                aux[*n - 1] = g->nos[i];
            }
        }
    }

    return aux;
}

no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n)
{
    //verificações
    if (!g || !origem || !destino || !n)
        return NULL;

    heap *prior = heap_nova(g->tamanho), *aux = heap_nova(g->tamanho - 1);

    if(!prior||!aux)
        return NULL;
    
    int i;
    no_grafo **output = NULL;
    no_grafo *inicio, *fim, *temp, *temp1;
    aresta_grafo *ar;
    time_t k;
    //extremos
    inicio = encontra_no(g, origem);
    fim = encontra_no(g, destino);
    //prioridades
    for (i = 0; i < g->tamanho; i++)
    {
        g->nos[i]->p_acumulado = INFINITY;
        g->nos[i]->anterior = NULL;
    }

    inicio->p_acumulado = 0;
    //adiciona nós à heap
    for (i = 0; i < g->tamanho; i++)
    {
        heap_insere(prior, g->nos[i], g->nos[i]->p_acumulado);
    }
    //percorre heap e, com o auxílio de outra heap, vai somando os tempos e o número de nós
    while (prior->tamanho != 0)
    {
        temp = heap_remove(prior);
        for (i = 0; i < temp->tamanho; i++)
        {
            ar = temp->arestas[i];
            if (difftime(mktime(&ar->partida), mktime(&partida)) >= 0)
            {

                k = difftime(mktime(&ar->chegada), mktime(&ar->partida));
                if (ar->destino->p_acumulado > (k + temp->p_acumulado))
                {

                    ar->destino->p_acumulado = k + temp->p_acumulado;
                    ar->destino->anterior = temp;

                    while (prior->tamanho != 0)
                    {
                        temp1 = heap_remove(prior);

                        if (strcmp(temp1->cidade, ar->destino->cidade) == 0)
                        {

                            temp1->p_acumulado = k + temp->p_acumulado;
                            temp1->anterior = temp;
                        }

                        heap_insere(aux, temp1, temp1->p_acumulado);
                    }

                    while (aux->tamanho != 0)
                    {

                        temp1 = heap_remove(aux);
                        heap_insere(prior, temp1, temp1->p_acumulado);
                    }
                }
            }
        }
    }

    heap_apaga(aux);
    heap_apaga(prior);

    if (!fim->anterior)
        return NULL;

    temp = fim;
    int tam = 1;
    //caminho inverso
    while (temp->anterior)
    {
        tam++;
        temp = temp->anterior;
    }
    //aloca para o vetor do resultado
    output = (no_grafo **)calloc(tam, sizeof(no_grafo *));
    //insere no vetor do resultado
    for (i = tam; i > 0; i--)
    {
        output[i - 1] = fim;
        fim = fim->anterior;
    }

    *n = tam;

    return output;
}

no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n)
{
    if (!g || !destino || !n)
        return NULL;

    int i;
    heap *aux = heap_nova(g->tamanho), *prior = heap_nova(g->tamanho - 1);

    if(!prior||!aux)
        return NULL;
    
    no_grafo **output = NULL;
    no_grafo *inicio, *fim, *temp, *temp1;
    aresta_grafo *ar;
    double k;

    //extremos
    inicio = encontra_no(g, origem);
    fim = encontra_no(g, destino);
    //prioridades
    for (i = 0; i < g->tamanho; i++)
    {
        g->nos[i]->p_acumulado = INFINITY;
        g->nos[i]->anterior = NULL;
    }

    inicio->p_acumulado = 0;
    //adiciona nós à heap
    for (i = 0; i < g->tamanho; i++)
    {
        heap_insere(aux, g->nos[i], g->nos[i]->p_acumulado);
    }
    //percorre heap e, com o auxílio de outra heap, vai somando os tempos e o número de nós
    while (aux->tamanho != 0)
    {
        temp = heap_remove(aux);

        for (i = 0; i < temp->tamanho; i++)
        {
            ar = temp->arestas[i];
            k = temp->p_acumulado + 1;

            double dif = difftime(mktime(&ar->partida), mktime(&partida));

            if (dif > 0)
            {
                if (ar->destino->p_acumulado > k)
                {
                    ar->destino->p_acumulado = k;
                    ar->destino->anterior = temp;
                    while (aux->tamanho != 0)
                    {
                        temp1 = heap_remove(aux);

                        if (strcmp(temp1->cidade, ar->destino->cidade) == 0)
                        {

                            temp1->p_acumulado = k + temp->p_acumulado;
                            temp1->anterior = temp;
                        }

                        heap_insere(prior, temp1, temp1->p_acumulado);
                    }

                    while (prior->tamanho != 0)
                    {

                        temp1 = heap_remove(prior);
                        heap_insere(aux, temp1, temp1->p_acumulado);
                    }
                }
            }
        }
    }

    heap_apaga(prior);
    heap_apaga(aux);

    if (fim->anterior == NULL)
        return NULL;

    temp = fim;
    int tam = 1;
    //caminho inverso
    while (temp->anterior)
    {
        tam += 1;
        temp = temp->anterior;
    }
    //aloca para o vetor do resultado final
    output = calloc(tam, sizeof(no_grafo *));
    temp = fim;
    //insere no vetor pretendido
    for (i = tam - 1; i >= 0; i--)
    {
        output[i] = temp;
        temp = temp->anterior;
    }

    *n = tam;

    return output;
}

aresta_grafo **atualiza_lugares(char *ficheiro, grafo *g, int *n)
{   
    //verificações
    if (!ficheiro || !g || !n)
        return NULL;
    FILE *f = fopen(ficheiro, "r");

    if(!f)
        return NULL;
        
    no_grafo *voo;
    aresta_grafo **vetor = calloc(1, sizeof(aresta_grafo *));
    aresta_grafo *aresta;
    char *token;
    char aux[100];
    int m;

    *n = 0;
    //lê o ficheiro,  procura o código, quando encontra verifica os lugares, se estiver cheio retira do grafo e insere no vetor que vai retornar
    while (fgets(aux, 100, f) != NULL)
    {
        token = strtok(aux, ",");
        voo = encontra_voo(g, token, &m);
        token = strtok(NULL, ",");
        voo->arestas[m]->lugares = atoi(token);
        if (voo->arestas[m]->lugares == 0)
        {
            aresta = voo->arestas[m];
            voo->arestas[m] = voo->arestas[voo->tamanho - 1];
            voo->tamanho -= 1;
            *n += 1;
            vetor = realloc(vetor, *n * sizeof(aresta_grafo *));
            vetor[*n - 1] = aresta;
        }
    }

    fclose(f);

    return vetor;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, companhia[4] = {0};
    int lugares = 0;
    double preco = 0;
    struct tm partida, chegada;

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ",");
        if (!token)
            break;
        strcpy(codigo, token);

        token = strtok(NULL, ",");
        strcpy(origem, token);

        token = strtok(NULL, ",");
        strcpy(destino, token);

        token = strtok(NULL, ",");
        partida.tm_year = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        partida.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_min = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_year = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        chegada.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_min = atoi(token);

        token = strtok(NULL, ",");
        preco = atof(token);

        token = strtok(NULL, ",");
        lugares = atoi(token);

        token = strtok(NULL, ",");
        strcpy(companhia, token);

        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {

            no_origem = no_insere(g, origem);

            if (!no_origem)
            {
                fclose(f);
                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
            no_destino = no_insere(g, destino);

            if (!no_destino)
            {
                fclose(f);
                return NULL;
            }
        }

        if (existe_aresta(no_origem, no_destino, codigo) == 0)
        {

            ret = cria_aresta(no_origem, no_destino, codigo, companhia, partida, chegada, preco, lugares);

            if (ret == -1)
            {
                fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}
