#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct par_ordenado
{
    int x;
    int y;
};

void imprime_par(struct par_ordenado pares) {
    
    printf("(%d, %d)", pares.x, pares.y);
}

int compara(const void *a, const void *b) {
    struct par_ordenado *parA = (struct par_ordenado *)a;
    struct par_ordenado *parB = (struct par_ordenado *)b;

    // Se o componente x for diferente, ordene pelos componentes x
    if (parA->x != parB->x) {
        return parA->x - parB->x;
    }
    // Se o componente y for diferente, ordene pelos componentes y
    return parA->y - parB->y;
}

// Função para ordenar um array de pares ordenados
void ordena(struct par_ordenado pares[], int tamanho) {
    qsort(pares, tamanho, sizeof(struct par_ordenado), compara);
}

void remove_inversos(struct par_ordenado pares[], int *tamanho) {

    for (int i = 0; i < *tamanho; i++)
    {
        for (int j = i + 1; j < *tamanho; j++)
        {
            if (pares[i].x == pares[j].y && pares[i].y == pares[j].x)
            {
                for (int k = j; k < *tamanho - 1; k++)
                {
                    pares[k] = pares[k + 1];
                }
                (*tamanho)--;
                j--;
            }
        }
    }
}

void is_reflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //saida corrigida 
    
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

void is_irreflexiva(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //saida corrigida

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

void is_simetrica(struct par_ordenado pares[], int tamanho) { // saida corrigida
    
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

void is_anti_simetrica(struct par_ordenado pares[], int tamanho) { //saida corrigida

    bool anti_simetrica = true;

    struct par_ordenado excecoes[50];
    int n_excecoes = 0;

    for (int i = 0; i < tamanho; i++)
    {
        bool found = false;
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
    remove_inversos(excecoes, &n_excecoes);

    if (anti_simetrica)
    {
        printf("4. Anti-simetrica: V\n");
    } else 
    {
        printf("4. Anti-simetrica: F\n");

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

void is_assimetrica(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //checada

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

    if (reflexiva && anti_simetrica)
    {
        printf("5. Assimetrica: V\n");
    } else {
        printf("5. Assimetrica: F\n");
    }
}

void is_transitiva(struct par_ordenado pares[], int tamanho) { // saida corrigida

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

void relacao_equivalencia(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //verdadeira quando R é reflexiva, simétrica e transitiva

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

    if (reflexiva && simetrica && transitiva)
    {
        printf("Relacao de equivalencia: V\n");
    } else
    {
        printf("Relacao de equivalencia: F\n");
    }
}

void relacao_ordem_parcial(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //verdadeira quando R é reflexiva, anti-simétrica e transitiva

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

    if (reflexiva && anti_simetrica && transitiva)
    {
        printf("Relacao de ordem parcial+: V\n");
    } else
    {
        printf("Relacao de ordem parcial: F\n");
    }

}

void fecho_reflexivo(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) { //saida corrigida

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

    printf("Fecho reflexivo da relacao: ");
    
    if (reflexiva)
    {
        printf("R\n");
    } else
    {
        struct par_ordenado fecho[50];
        int tamanho_fecho = tamanho_pares + n_excecoes;

        for (int i = 0; i < tamanho_fecho; i++)
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

void fecho_simetrico(struct par_ordenado pares[], int tamanho) { // saida corrigida

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

    printf("Fecho simetrico da relacao: ");
    
    if (simetrica)
    {
        printf("R\n");
    } else
    {
        struct par_ordenado fecho[50];
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

void fecho_transitivo(struct par_ordenado pares[], int tamanho) { // saida corrigida

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

    printf("Fecho transitivo da relacao: ");
    
    if (transitiva)
    {
        printf("R\n");
    } else
    {
        struct par_ordenado fecho[50];
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

void imprime_relacoes(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    relacao_equivalencia(a, tamanho_a, pares, tamanho_pares);

    relacao_ordem_parcial(a, tamanho_a, pares, tamanho_pares);

    printf("\n");
}

void imprime_fechos(int a[], int tamanho_a, struct par_ordenado pares[], int tamanho_pares) {

    fecho_reflexivo(a, tamanho_a, pares, tamanho_pares);

    fecho_simetrico(pares, tamanho_pares);

    fecho_transitivo(pares, tamanho_pares);
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

    imprime_propriedades(conjuntoA, tamanhoA, conjuntoB, tamanhoB);
    imprime_relacoes(conjuntoA, tamanhoA, conjuntoB, tamanhoB);
    imprime_fechos(conjuntoA, tamanhoA, conjuntoB, tamanhoB);

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