#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //bibliotecas utilizadas ao longo do programa

//struct para armazenar pares ordenados (x, y), sendo dois ints

struct par_ordenado {
    int x;
    int y;
};

//função usada para imprimir os pares ordenados na formatação correta
void imprime_par(struct par_ordenado pares) { 
    
    printf("(%d, %d)", pares.x, pares.y);
}

//função que compara dois pares ordenados, utilizada posteriormente para ordenar um array de pares
int compara(const void *a, const void *b) { 

    //acessa os pares ordenados específicos usando os ponteiros a e b
    struct par_ordenado *parA = (struct par_ordenado *)a;
    struct par_ordenado *parB = (struct par_ordenado *)b;

    // Se o elemento x for diferente, ordena por x de forma crescente
    if (parA->x != parB->x) {
        return parA->x - parB->x;
    }
    // quando x é igual, ordena por y de forma crescente
    return parA->y - parB->y;
}

// função para ordenar um array de pares ordenados usando qsort
void ordena(struct par_ordenado pares[], int tamanho) {

    qsort(pares, tamanho, sizeof(struct par_ordenado), compara);
}

//função para remover inversos de um array de pares ordenados, importante para listar as exceções na ordem certa da propriedade anti-simétrica
//exemplo: se a função contém (x, y) e (y, x), sobra apenas (x, y)
void remove_inversos(struct par_ordenado pares[], int *tamanho) {

    for (int i = 0; i < *tamanho; i++)
    {
        for (int j = i + 1; j < *tamanho; j++) //dois for para percorrer o array duas vezes e comparar dois pares de acordo com os índices i e j
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x) //checa se os dois pares são inversos
            {
                for (int k = j; k < *tamanho - 1; k++) //loop para excluir o inverso, realoca o índice dos pares que vem depois desse inverso
                {
                    pares[k] = pares[k + 1];
                }
                (*tamanho)--;
                j--;
            }
        }
    }
}

//função para checar a reflexividade (para todo a, existe (a, a)) de um conjunto de pares e imprimir o resultado
void is_reflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { 
    
    bool reflexiva = true;
    
    struct par_ordenado excecoes[2450]; //declara um array para armazenar as exceções à regra
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++) //dois loops que percorrem o array buscando dois pares reflexivos
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y) //checa de os dois pares são reflexivos
            {
                found = true;
                break;
            }
        }
        if (!found) //se não encontrado, adiciona o elemento não existente ao array excecoes e muda o valor da bool reflexiva para false
        {
            excecoes[n_excecoes].x = a[i];
            excecoes[n_excecoes].y = a[i];
            n_excecoes ++;
            reflexiva = false;
        }  
    }

    //imprime os resultados na formatação adequada:
    if (reflexiva)
    {
        printf("1. Reflexiva: V\n");
    } else 
    {
        printf("1. Reflexiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);

            if (i< n_excecoes - 1)
            {
                printf(", ");
            }
        }
        
        printf("\n");
    }
}

//função para checar se o conjunto é irreflexivo (para nenhum a existe (a, a)) e imprimir os resultados
void is_irreflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    bool irreflexiva = true;

    struct par_ordenado excecoes[2450]; //array de exceções
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++) //loops para encontrar dois pares a serem comparados
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y) //checa se os dois são irreflexivos 
            {
                found = true;
                break;
            }
        }
        if (found) //se encontrado, adiciona o par ao array de excecoes e muda o valor da bool irreflexiva
        {
            excecoes[n_excecoes].x = a[i];
            excecoes[n_excecoes].y = a[i];
            n_excecoes ++;
            irreflexiva = false;
        }
    }
    
    //imprime os resultados adequadamente
    if (irreflexiva)
    {
        printf("2. Irreflexiva: V\n");
    } else 
    {
        printf("2. Irreflexiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);

            if (i< n_excecoes - 1)
            {
                printf(", ");
            }
        }
        
        printf("\n");
    }
}

//função que checa a simetria de um conjunto (para todo (x, y), existe (y, x)) e imprime os resultados
void is_simetrica(struct par_ordenado pares[], int tamanho) { 
    
    bool simetrica = true;

    struct par_ordenado excecoes[2450]; //array de exceções
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho; j++) //dois loops para buscar dois pares a serem comparados
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                found = true;
                break;
            }
        }
        if (!found) //se não encontrado, adiciona o par que falta às exceções e muda o valor da bool simetrica
        {
            excecoes[n_excecoes].x = pares[i].y;
            excecoes[n_excecoes].y = pares[i].x;
            n_excecoes ++;
            simetrica = false;
        }
    }
    
    //imprime os resultados na formatação correta
    if (simetrica)
    {
        printf("3. Simetrica: V\n");
    } else 
    {
        printf("3. Simetrica: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);

            if (i< n_excecoes - 1)
            {
                printf(", ");
            }
        }
        
        printf("\n");
    }
}

//funçaõ que checa se o conjunto é anti-simétrico(se existe (x, y) e (y, x), então x = y) e imprime os resultados
void is_anti_simetrica(struct par_ordenado pares[], int tamanho) {

    bool anti_simetrica = true;

    struct par_ordenado excecoes[2450]; //array para exceções
    int n_excecoes = 0;

    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho; j++) //dois loops que percorrem o conjunto em busca de dois pares 
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x) //checa se os dois pares atendem a condição de serem inversos
            {
                if (pares[i].x == pares[i].y) // caso a primeira condição seja atendida, checa se x = y
                {
                    found = true;
                    break;
                }
                if (!found) //se não encontrado, adiciona o par i a lista de exceções e muda o valor da bool anti-simetrica
                {
                    excecoes[n_excecoes].x = pares[i].y;
                    excecoes[n_excecoes].y = pares[i].x;
                    n_excecoes ++;
                    anti_simetrica = false;
                }
            }
        }
    }

    ordena(excecoes, n_excecoes); //ordena o array exceções de forma crescente
    remove_inversos(excecoes, &n_excecoes); //remove os inversos do array, deixando apenas o menor de cada dupla

    //imprime os resultados corretamente
    if (anti_simetrica)
    {
        printf("4. Anti-simetrica: V\n");
    } else 
    {
        printf("4. Anti-simetrica: F\n");

        //percorre o array "exceções" e imprime, na formatação correta, o par atual e seu inverso
        for (int i = 0; i < n_excecoes; i++)
        {
            printf("((%d, %d), (%d, %d))", excecoes[i].x, excecoes[i].y, excecoes[i].y, excecoes[i].x);

            if (i< n_excecoes - 1)
            {
                printf(", ");
            }
        }
        
        printf("\n");
    }
}

//função que checa se um conjunto é assimétrico (irreflexivo e anti-simétrico) e imprime os resultados
void is_assimetrica(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { 

    //essa parte checa se a relação é reflexiva:
    bool reflexiva = true;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            reflexiva = false;
        }  
    }

    //checa se a relação é anti-simétrica:
    bool anti_simetrica = true;

    for (int i = 0; i < tamanho_pares; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                for (int k = 0; k < tamanho_pares; k++)
                {
                    if (pares[i].x == pares[i].y)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    anti_simetrica = false;
                }
            }
        }
    }

    //imprime os resultados
    if (reflexiva && anti_simetrica) //checa se o conjunto é reflexivo e anti-simétrico
    {
        printf("5. Assimetrica: V\n");
    } else {
        printf("5. Assimetrica: F\n");
    }
}

//função que checa a transitividade  do conjunto (se existe (x, y) e (y, z), então existe (x, z)) e imprime os resultados 
void is_transitiva(struct par_ordenado pares[], int tamanho) {

    bool transitiva = true;

    struct par_ordenado excecoes[2450];
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho; j++) //loops para encontrar dois pares ordenados para comparar
        {
            if (pares[i].y == pares[j].x) //checa se y do par 1 é igual a x do par 2
            {
                for (int k = 0; k < tamanho; k++) //se verdadeiro, percorre o array de novo para comparar um terceiro par
                {
                    if (pares[k].x == pares[i].x && pares[k].y == pares[j].y) //checa se os tres pares atendem às condições
                    {
                        found = true;
                        break;
                    }
                }
                if (!found) //se não encontrado, adiciona o par faltante a lista de exceções e muda a bool transitiva
                {
                    excecoes[n_excecoes].x = pares[i].x;
                    excecoes[n_excecoes].y = pares[j].y;
                    n_excecoes ++;
                    transitiva = false;
                }
            }
        }
    }
    
    //imprime os resultados
    if (transitiva)
    {
        printf("6. Transitiva: V\n");
    } else 
    {
        printf("6. Transitiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);

            if (i< n_excecoes - 1)
            {
                printf(", ");
            }
        }
        
        printf("\n");
    }
}

//função para checar se a o conjunto é de relação equivalência (quando R é reflexiva, simétrica e transitiva) e imprimir os resultados
void relacao_equivalencia(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { 

    //checagem da reflexividade
    bool reflexiva = true;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            reflexiva = false;
        }  
    }

    //checagem da simetria
    bool simetrica = true;
    
    for (int i = 0; i < tamanho_pares; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            simetrica = false;
        }
    }

    //checagem da transitividade
    bool transitiva = true;
    
    for (int i = 0; i < tamanho_pares; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[i].y == pares[j].x)
            {
                for (int k = 0; k < tamanho_pares; k++)
                {
                    if (pares[k].x == pares[i].x && pares[k].y == pares[j].y)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    transitiva = false;
                }
            }
        }
    }

    //impressão dos resultados
    if (reflexiva && simetrica && transitiva)
    {
        printf("Relacao de equivalencia: V\n");
    } else
    {
        printf("Relacao de equivalencia: F\n");
    }
}

//função para checar se a relação é de ordem parcial (ocorre quando R é reflexiva, anti-simétrica e transitiva) e imprime os resultados
void relacao_ordem_parcial(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { 

    //checagem da reflexividade
    bool reflexiva = true;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            reflexiva = false;
        }  
    }

    //checagem da anti-simetria
    bool anti_simetrica = true;

    for (int i = 0; i < tamanho_pares; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                if (pares[i].x == pares[i].y)
                {
                    found = true;
                    break;
                }
                if (!found)
                {
                    anti_simetrica = false;
                }
            }
        }
    }

    //checagem da transitividade
    bool transitiva = true;
    
    for (int i = 0; i < tamanho_pares; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[i].y == pares[j].x)
            {
                for (int k = 0; k < tamanho_pares; k++)
                {
                    if (pares[k].x == pares[i].x && pares[k].y == pares[j].y)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    transitiva = false;
                }
            }
        }
    }

    //impressão dos resultados
    if (reflexiva && anti_simetrica && transitiva)
    {
        printf("Relacao de ordem parcial+: V\n");
    } else
    {
        printf("Relacao de ordem parcial: F\n");
    }
}

//função que imprime o fecho reflexivo do conjunto (conjunto + pares necessários para torná-lo reflexivo)
void fecho_reflexivo(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    //checa a reflexividade e, caso não, preenche o array de exceções
    bool reflexiva = true;
    
    struct par_ordenado excecoes[2450];
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho_a; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho_pares; j++)
        {
            if (pares[j].x == a[i] && pares[j].x == pares[j].y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            excecoes[n_excecoes].x = a[i];
            excecoes[n_excecoes].y = a[i];
            n_excecoes ++;
            reflexiva = false;
        }  
    }

    //impressão do resultado
    printf("Fecho reflexivo da relacao:");
    
    //se o conjunto for reflexivo, basta imprimir "R"
    if (reflexiva)
    {
        printf(" R\n");
    } else //caso contrário, imprime o conjunto acrescido dos pares que faltam
    {
        struct par_ordenado fecho[2450]; //cria um array para o fecho
        int tamanho_fecho = tamanho_pares + n_excecoes; 

        for (int i = 0; i < tamanho_fecho; i++) //preenche o array, primeiro com o próprio conjunto, e depois com as exceções
        {
            if (i < tamanho_pares)
            {
                fecho[i].x = pares[i].x;
                fecho[i].y = pares[i].y;
            } else
            {
                fecho[i].x = excecoes[i - tamanho_pares].x;
                fecho[i].y = excecoes[i - tamanho_pares].y;
            }
        }
        
        ordena(fecho, tamanho_fecho); //ordena o array

        printf("\n");
        
        //imprime o fecho
        for (int i = 0; i < tamanho_fecho; i++)
        {
            imprime_par(fecho[i]);

            if (i< tamanho_fecho - 1)
            {
                printf(", ");
            }
        }

        printf("\n");
    }
}

//função que imprime o fecho simétrico (conjunto + pares necessários para torná-lo simétrico)
void fecho_simetrico(struct par_ordenado pares[], int tamanho) {

    //checa a simetria e preenche o array de exceções
    bool simetrica = true;

    struct par_ordenado excecoes[2450];
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            excecoes[n_excecoes].x = pares[i].y;
            excecoes[n_excecoes].y = pares[i].x;
            n_excecoes ++;
            simetrica = false;
        }
    }

    //imprime os resultados de maneira análoga à função anterior
    printf("Fecho simetrico da relacao:");
    
    if (simetrica)
    {
        printf(" R\n");
    } else
    {
        struct par_ordenado fecho[2450];
        int tamanho_fecho = tamanho + n_excecoes;

        for (int i = 0; i < tamanho_fecho; i++)
        {
            if (i < tamanho)
            {
                fecho[i].x = pares[i].x;
                fecho[i].y = pares[i].y;
            } else
            {
                fecho[i].x = excecoes[i - tamanho].x;
                fecho[i].y = excecoes[i - tamanho].y;
            }
        }
        
        ordena(fecho, tamanho_fecho);

        printf("\n");
        
        for (int i = 0; i < tamanho_fecho; i++)
        {
            imprime_par(fecho[i]);

            if (i< tamanho_fecho - 1)
            {
                printf(", ");
            }
        }

        printf("\n");
    }
}

//função para imprimir o facho transitivo (conjunto + pares necessários para torná-lo transitivo)
void fecho_transitivo(struct par_ordenado pares[], int tamanho) {

    //checa a transitividade e preenche o array de exceções
    bool transitiva = true;

    struct par_ordenado excecoes[2450];
    int n_excecoes = 0;
    
    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        for (int j = 0; j < tamanho; j++)
        {
            if (pares[i].y == pares[j].x)
            {
                for (int k = 0; k < tamanho; k++)
                {
                    if (pares[k].x == pares[i].x && pares[k].y == pares[j].y)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    excecoes[n_excecoes].x = pares[i].x;
                    excecoes[n_excecoes].y = pares[j].y;
                    n_excecoes ++;
                    transitiva = false;
                }
            }
        }
    }

    //imprime os resultados de forma análoga às funções anteriores
    printf("Fecho transitivo da relacao:");
    
    if (transitiva)
    {
        printf(" R\n");
    } else
    {
        struct par_ordenado fecho[2450];
        int tamanho_fecho = tamanho + n_excecoes;

        for (int i = 0; i < tamanho_fecho; i++)
        {
            if (i < tamanho)
            {
                fecho[i].x = pares[i].x;
                fecho[i].y = pares[i].y;
            } else
            {
                fecho[i].x = excecoes[i - tamanho].x;
                fecho[i].y = excecoes[i - tamanho].y;
            }
        }
        
        ordena(fecho, tamanho_fecho);

        printf("\n");
        
        for (int i = 0; i < tamanho_fecho; i++)
        {
            imprime_par(fecho[i]);

            if (i< tamanho_fecho - 1)
            {
                printf(", ");
            }
        }

        printf("\n");
    }

}

//função que imprime todas as propriedades dado um determinado conjunto na formatação adequada
void imprime_propriedades(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    printf("Propriedades\n");

    is_reflexiva(a, tamanho_a, pares, tamanho_pares);

    is_irreflexiva(a, tamanho_a, pares, tamanho_pares);

    is_simetrica(pares, tamanho_pares);

    is_anti_simetrica(pares, tamanho_pares);

    is_assimetrica(a, tamanho_a, pares, tamanho_pares);

    is_transitiva(pares, tamanho_pares);

    printf("\n");
}

//função que imprime todas as relações dado um determinado conjunto na formatação adequada
void imprime_relacoes(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    relacao_equivalencia(a, tamanho_a, pares, tamanho_pares);

    relacao_ordem_parcial(a, tamanho_a, pares, tamanho_pares);

    printf("\n");
}

//função que imprime todos os fechos dado um determinado conjunto na formatação adequada
void imprime_fechos(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    fecho_reflexivo(a, tamanho_a, pares, tamanho_pares);

    fecho_simetrico(pares, tamanho_pares);

    fecho_transitivo(pares, tamanho_pares);
}

int main() {
    
    //leitura da entrada:
    int tamanho; //int que armazena o tamanho do conjunto de números
    int conjunto[50]; //vetor do conjunto de números de tamanho máximo 50, como especificado nas instruções

    //lê o tamanho do conjunto de números
    scanf("%d ", &tamanho);

    //for para ler os elementos do conjunto de números
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d ", &conjunto[i]);
    }
    
    struct par_ordenado pares[2450]; //declaração do array de structs de pares ordenados
    //obs: tamanho máximo foi declarado como 2450 pois é o número máximo de permutações em um conjunto com 50 elementos
    int tamanho_pares = 0; //tamanho inicial do array, que será acrescido de acordo com a leitura

    //while utilizado para ler pares ordenados enquanto não encontrar o fim do arquivo
    while (scanf("%d %d", &pares[tamanho_pares].x, &pares[tamanho_pares].y) != EOF) //checa se a leitura retorna um valor válido
    {
        tamanho_pares++; //acresce o tamanho do array
    }
    
    //imprime toda a saída do código na formatação correta
    imprime_propriedades(conjunto, tamanho, pares, tamanho_pares);
    imprime_relacoes(conjunto, tamanho, pares, tamanho_pares);
    imprime_fechos(conjunto, tamanho, pares, tamanho_pares);
    
    return 0; //finaliza o código
}