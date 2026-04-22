#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int **a = (int **)malloc(N * sizeof(int *));
    int **b = (int **)malloc(M * sizeof(int *));
    if (a == NULL || b == NULL) return 1;

    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(M * sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        b[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            b[j][i] = a[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) free(a[i]);
    free(a);

    for (int i = 0; i < M; i++) free(b[i]);
    free(b);

    return 0;
}
