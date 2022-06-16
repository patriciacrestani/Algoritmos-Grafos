#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
    int x, y, v; 
}Grafo;

int total;
int* fat;
Grafo* grafo;

int cmp(const void *a, const void *b) {
    return (*(Grafo *)a).v - (*(Grafo *)b).v;
}

void makeset(int n) {
    for (int i = 0; i < n; i++){
        fat[i] = i;
    }
}

int find(int n) {
    if(fat[n] != n){
        fat[n] = find(fat[n]);
    }
    return fat[n];
}

int unionp(int x, int y, int p) {
    int i = find(x), j = find(y);

    if(i != j) {
        total -= grafo[p].v;
        if(i > j){ 
            fat[i] = j;
        } else {
            fat[j] = i;
        }
        return 1;
    }

    return 0;
}

void leEntrada() {
    int m, n, i, x, y, v;
    int controle = 1;
    
    while(controle == 1) {
        scanf("%d %d", &m, &n);

        if((1 > m) || (m > 200000) || (1 > n) || (n > 200000)){
            controle = 0;
            continue;
        }

        total = 0;
        grafo = (Grafo*)malloc(n * sizeof(Grafo));

        for (i = 0; i < n; i++) {
            scanf("%d %d %d", &x, &y, &v);

            if((0 > x) || (y > m) || (x == y)){
                controle = 0;
                break;
            }

            grafo[i].x = x;
            grafo[i].y = y;
            grafo[i].v = v;
            total += v;
        }
        fat = (int*)malloc(n * sizeof(int));
        makeset(m);
        qsort(grafo, n, sizeof(grafo[0]), cmp);
        for (i = 0; i < n; ++i){
            unionp(grafo[i].x, grafo[i].y, i);
        }
        printf("%d\n", total);
    }
}

int main(int argc, char const *argv[]) {
    leEntrada();
    return 0;
}