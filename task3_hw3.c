#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;

    scanf("%d %d", &N, &M);

    int **matrix = (int **)malloc(N * sizeof(int *));
    int **transposed = (int **)malloc(M * sizeof(int *));

    if (matrix == NULL || transposed == NULL) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            return 1;
        }
    }

    for (int i = 0; i < M; i++) {
        transposed[i] = (int *)malloc(N * sizeof(int));
        if (transposed[i] == NULL) {
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    for (int i = 0; i < M; i++) {
        free(transposed[i]);
    }
    free(transposed);

    return 0;
}
