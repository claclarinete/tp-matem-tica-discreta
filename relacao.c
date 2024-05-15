#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct par_ordenado
{
    int x;
    int y;
};

void imprime_par(struct par_ordenado pares) {
    
    printf("(%d, %d) ", pares.x, pares.y);
}

int compara(const void *a, const void *b) {
    struct par_ordenado *parA = (struct par_ordenado *)a;
    struct par_ordenado *parB = (struct par_ordenado *)b;

    // Se o índice do primeiro par for par, faça o segundo par ser o inverso do primeiro
    if ((parA->x % 2 == 0) && (parB->x % 2 == 0)) {
        return parA->y - parB->x;
    }

    // Caso contrário, compare normalmente
    if (parA->x != parB->x) {
        return parA->x - parB->x;
    } else {
        return parA->y - parB->y;
    }
}

// Função para ordenar um array de pares ordenados
void ordena(struct par_ordenado pares[], int tamanho) {
    qsort(pares, tamanho, sizeof(struct par_ordenado), compara);
}

bool is_reflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //checada 
    
    bool reflexiva = true;
    
    struct par_ordenado excecoes[50];
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

    if (reflexiva)
    {
        printf("1. Reflexiva: V\n");
        return true;
    } else 
    {
        printf("1. Reflexiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);
        }
        
        printf("\n");
        return false;
    }
}

bool is_irreflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    bool irreflexiva = true;

    struct par_ordenado excecoes[50];
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
        if (found)
        {
            excecoes[n_excecoes].x = a[i];
            excecoes[n_excecoes].y = a[i];
            n_excecoes ++;
            irreflexiva = false;
        }
    }
    
    if (irreflexiva)
    {
        printf("2. Irreflexiva: V\n");
        return true;
    } else 
    {
        printf("2. Irreflexiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);
        }
        
        printf("\n");
        return false;
    }
}

bool is_simetrica(struct par_ordenado pares[], int tamanho) { // checada
    
    bool simetrica = true;

    struct par_ordenado excecoes[50];
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
    
    if (simetrica)
    {
        printf("3. Simetrica: V\n");
        return true;
    } else 
    {
        printf("3. Simetrica: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);
        }
        
        printf("\n");
        return false;
    }
}

bool is_anti_simetrica(struct par_ordenado pares[], int tamanho) { //falta ajustar a saida das exceções

    bool anti_simetrica = true;

    struct par_ordenado excecoes[50];
    int n_excecoes = 0;

    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
        /*for (int j = 0; j < tamanho; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x && pares[i].x == pares[i].y)
            {
                found = true;
                break;
            }
        }*/
        for (int j = 0; j < tamanho; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                for (int k = 0; k < tamanho; k++)
                {
                    if (pares[i].x == pares[i].y)
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
                    anti_simetrica = false;
                }
            }
        }
    }
    
    ordena(excecoes, n_excecoes);

    if (anti_simetrica)
    {
        printf("4. Anti-simetrica: V\n");
        return true;
    } else 
    {
        printf("4. Anti-simetrica: F\n");

        for (int i = 0; i < n_excecoes; i += 2)
        {
            printf("((%d, %d), (%d, %d)) ", excecoes[i].x, excecoes[i].y, excecoes[i + 1].y, excecoes[i + 1].x);
        }
        
        printf("\n");
        return false;
    }
}

bool is_assimetrica(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //checada

    if (is_reflexiva(a, tamanho_a, pares, tamanho_pares) && is_anti_simetrica(pares, tamanho_pares))
    {
        printf("5. Assimetrica: V\n");
        return true;
    } else {
        printf("5. Assimetrica: F\n");
        return false;
    }
}

bool is_transitiva(struct par_ordenado pares[], int tamanho) { // alterar a saida das exceções

    bool transitiva = true;

    struct par_ordenado excecoes[50];
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
    
    for (int i = 0; i < n_excecoes; i++)
    {
        /* code */
    }
    

    if (transitiva)
    {
        printf("6. Transitiva: V\n");
        return true;
    } else 
    {
        printf("6. Transitiva: F\n");

        for (int i = 0; i < n_excecoes; i++)
        {
            imprime_par(excecoes[i]);
        }
        
        printf("\n");
        return false;
    }
}


int main() {
    // Exemplo de conjunto A
    int conjuntoA[] = {3, 4, 5, 6, 7, 8};//{1, 2, 3, 4};

    // Exemplo de conjunto de pares ordenados B
    struct par_ordenado conjuntoB[] = {
        /*{1, 2},
        {2, 3},
        {3, 4},
        {1, 1}*/
        {3, 5},
        {5, 7},
        {7, 3},
        {5, 3},
        {7, 5},
        {3, 7},
        {4, 6},
        {6, 8},
        {8, 4},
        {6, 4},
        {8, 6},
        {4, 8},
        {3, 3},
        {4, 4},
        {5, 5},
        {6, 6},
        {7, 7},
        {8, 8}
    };

    int tamanhoA = sizeof(conjuntoA) / sizeof(conjuntoA[0]);
    int tamanhoB = sizeof(conjuntoB) / sizeof(conjuntoB[0]);

    is_reflexiva(conjuntoA, tamanhoA, conjuntoB, tamanhoB);

    is_irreflexiva(conjuntoA, tamanhoA, conjuntoB, tamanhoB);

    is_simetrica(conjuntoB, tamanhoB);

    is_anti_simetrica(conjuntoB, tamanhoB);

    is_assimetrica(conjuntoA, tamanhoA, conjuntoB, tamanhoB);

    is_transitiva(conjuntoB, tamanhoB);
    
    

    return 0;
    
    
    
    /*int tamanho;
    struct par_ordenado pares[50];

    scanf("%d ", &tamanho);
    int *a = (int *)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d ", &a[i]);
    }
    for (int i = 0; i < 50; i++)
    {
        scanf("%d\n", &pares[i]);
    }
    
    for (int i = 0; i < tamanho; i++)
    {
        is_reflexiva(a[tamanho], tamanho, pares);
        if (is_reflexiva)
        {
            printf("verdadeiro\n");
        } else
        {
            printf("falso\n");
        }
        
        
    }
    

    return 0;*/
}