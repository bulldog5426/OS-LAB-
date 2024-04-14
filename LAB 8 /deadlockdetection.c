#include <stdio.h>

#define N 5
#define M 3

int alloc[N][M];
int max[N][M];
int need[N][M];
int avail[M];
int work[M];
int finish[N];

void printGraph() {
    printf("Allocation Graph:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < M; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("Maximum Claim Graph:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < M; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Need Graph:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < M; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void calculateNeed() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int isSafe() {
    int count = 0;
    for (int i = 0; i < N; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        work[i] = avail[i];
    }

    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < M; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == M) {
                    for (j = 0; j < M; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            return 0;
        }
    }

    return 1;
}

void testDeadlock() {
    calculateNeed();
    if (isSafe() == 0) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }
}

int main() {
    printf("Enter the resource allocation graph:\n");
    printf("Enter the current allocation matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the maximum claim matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < M; i++) {
        scanf("%d", &avail[i]);
    }

    printGraph();
    testDeadlock();

    return 0;
}
