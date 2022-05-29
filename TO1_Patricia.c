#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N; // a quantidade de casos de teste que vem a seguir
int V; // a quantidade de vertices do grafo
int E; // a quantidade de arestas do grafo
int **adj; // nosso grafo
int *lbl; // lista de quando o vertice foi visitado
int contador = 0; // contador de quando o vertice foi visitado

void preencherGrafo() {
    int i;
    int j;
    for(i = 0; i < V; i++) {
        for(j = 0; j < V; j++) {
            adj[i][j] = -1;
        }
    }
}

void criarGrafo() {
    adj = (int**)malloc(V * sizeof(int*));
    int i;
    for(i = 0; i < V; i++) {
        adj[i] = (int*)malloc(V * sizeof(int));
    } 

    preencherGrafo();
}

void preencherListaVisitados() {
    int i;
    for(i = 0; i < V; i++) {
        lbl[i] = -1;
    }
}

void criarListaVisitados() {
    lbl = (int*)malloc(V * sizeof(int));
    preencherListaVisitados();
}

void pathR(int v, int tabs) {
    int w;
    int i;
    contador++;
    lbl[v] = contador;
    for(w = 0; w < V; w++) {
        if(adj[v][w] == 1) {
            for(i = 0; i < tabs; i++) {
                printf("  ");
            }
            printf("  %d-%d ", v, w);
            if(lbl[w] == -1) {
                printf("pathR(G,%d)\n", w);
                tabs++;
                pathR(w, tabs);
                tabs--;
            } else {
                printf("\n");
            }
        }
    }
}

int possuiVizinhos(int v) {
    int i;
    for(i = 0; i < V; i++) {
        if(adj[v][i] == 1) {
            return 1;
        }
    }
    return 0;
}

void leEntrada() {
    scanf("%d", &N);

    if(N <= 0) {
        return;
    }

    int casos = 0;
    while(casos < N) {
        casos++;
        scanf("%d %d", &V, &E);
        
        if(V < 1 || V > 20) {
            return;
        }

        if(E < 1 || E > 20) {
            return;
        }

        criarGrafo();
        criarListaVisitados();

        int vEntrada;
        int vSaida;
        int i;
        for(i = 0; i < E; i++) {
            scanf("%d %d", &vEntrada, &vSaida);
            adj[vEntrada][vSaida] = 1;
        }

        printf("Caso %d:\n", casos);

        for(i = 0; i < V; i++) {
            if(lbl[i] == -1) {
                pathR(i, 0);
                if(possuiVizinhos(i) == 1) {
                    printf("\n");
                }
            }
        }
        free(adj);
        free(lbl);
        contador = 0;
    }
}

void leArquivoEntrada(FILE* arquivo) {
    fscanf(arquivo, "%d", &N);

    if(N <= 0) {
        return;
    }

    int casos = 0;
    while(casos < N && fscanf(arquivo, "%d %d", &V, &E) != EOF) {
        casos++;
        fscanf(arquivo, "%d %d", &V, &E);
        
        if(V < 1 || V > 20) {
            return;
        }

        if(E < 1 || E > 20) {
            return;
        }

        criarGrafo();
        criarListaVisitados();

        printf("Caso %d:\n", casos);
        int vEntrada;
        int vSaida;
        int i;
        for(i = 0; i < E; i++) {
            fscanf(arquivo, "%d %d", &vEntrada, &vSaida);
            adj[vEntrada][vSaida] = 1;
        }

        for(i = 0; i < V; i++) {
            if(lbl[i] == -1) {
                pathR(i, 0);
                if(possuiVizinhos(i) == 1) {
                    printf("\n");
                }
            }
        }
        free(adj);
        free(lbl);
        contador = 0;
    }
}

void abreArquivoEntrada(char *nomeArquivo[]) {
    FILE *arquivo;
    arquivo = fopen(*++nomeArquivo, "r");

    if(arquivo == NULL) {
        return;
    }

    leArquivoEntrada(arquivo);
    
    fclose(arquivo);
}

int main (int argc, char *argv[]) {
    // abreArquivoEntrada(argv);
    leEntrada();
    return 0;
}