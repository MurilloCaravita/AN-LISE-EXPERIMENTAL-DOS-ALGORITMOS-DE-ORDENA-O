#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copiar_vetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void imprimir_vetor(int vet[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void gerar_aleatorios(int vet[], int n, int limite) {
    for (int i = 0; i < n; i++) {
        vet[i] = rand() % limite;
    }
}

void bubble_sort(int vet[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (vet[j] > vet[j + 1]) {
                int aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

void merge(int vet[], int ini, int meio, int fim) {
    int tam_esq = meio - ini + 1;
    int tam_dir = fim - meio;

    int *esq = (int *)malloc(tam_esq * sizeof(int));
    int *dir = (int *)malloc(tam_dir * sizeof(int));

    for (int i = 0; i < tam_esq; i++) {
        esq[i] = vet[ini + i];
    }

    for (int i = 0; i < tam_dir; i++) {
        dir[i] = vet[meio + 1 + i];
    }

    int i = 0, j = 0, k = ini;

    while (i < tam_esq && j < tam_dir) {
        if (esq[i] <= dir[j]) {
            vet[k] = esq[i];
            i++;
        } else {
            vet[k] = dir[j];
            j++;
        }
        k++;
    }

    while (i < tam_esq) {
        vet[k] = esq[i];
        i++;
        k++;
    }

    while (j < tam_dir) {
        vet[k] = dir[j];
        j++;
        k++;
    }

    free(esq);
    free(dir);
}

void merge_sort(int vet[], int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        merge_sort(vet, ini, meio);
        merge_sort(vet, meio + 1, fim);
        merge(vet, ini, meio, fim);
    }
}

int particionar(int vet[], int ini, int fim) {
    int pivo = vet[fim];
    int i = ini - 1;

    for (int j = ini; j < fim; j++) {
        if (vet[j] < pivo) {
            i++;
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        }
    }

    int aux = vet[i + 1];
    vet[i + 1] = vet[fim];
    vet[fim] = aux;

    return i + 1;
}

void quick_sort(int vet[], int ini, int fim) {
    if (ini < fim) {
        int pos_pivo = particionar(vet, ini, fim);
        quick_sort(vet, ini, pos_pivo - 1);
        quick_sort(vet, pos_pivo + 1, fim);
    }
}

void executar_bubble(int vet[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    bubble_sort(vet, n);
    fim = clock();

    printf("\nBubble Sort:\n");
    imprimir_vetor(vet, n);
    printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

void executar_merge(int vet[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    merge_sort(vet, 0, n - 1);
    fim = clock();

    printf("\nMerge Sort:\n");
    imprimir_vetor(vet, n);
    printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

void executar_quick(int vet[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    quick_sort(vet, 0, n - 1);
    fim = clock();

    printf("\nQuick Sort:\n");
    imprimir_vetor(vet, n);
    printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

int main() {
    int n;
    int opcao;
    int *vet_base;
    int *vet_aux;

    srand(time(NULL));

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Tamanho invalido\n");
        return 1;
    }

    vet_base = (int *)malloc(n * sizeof(int));
    vet_aux = (int *)malloc(n * sizeof(int));

    gerar_aleatorios(vet_base, n, 1000);

    printf("\nVetor gerado:\n");
    imprimir_vetor(vet_base, n);

    printf("\nEscolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Merge Sort\n");
    printf("3 - Quick Sort\n");
    printf("4 - Executar todos\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        copiar_vetor(vet_base, vet_aux, n);
        executar_bubble(vet_aux, n);
    } else if (opcao == 2) {
        copiar_vetor(vet_base, vet_aux, n);
        executar_merge(vet_aux, n);
    } else if (opcao == 3) {
        copiar_vetor(vet_base, vet_aux, n);
        executar_quick(vet_aux, n);
    } else if (opcao == 4) {
        copiar_vetor(vet_base, vet_aux, n);
        executar_bubble(vet_aux, n);

        copiar_vetor(vet_base, vet_aux, n);
        executar_merge(vet_aux, n);

        copiar_vetor(vet_base, vet_aux, n);
        executar_quick(vet_aux, n);
    } else {
        printf("Opcao invalida\n");
    }

    free(vet_base);
    free(vet_aux);

    return 0;
}
