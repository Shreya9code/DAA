#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

void printLCS(char X[], int m, int n, int **b) {
    int i = m, j = n;
    char lcs[MAX]; 
    int index = 0;
    
    while (i > 0 && j > 0) {
        if (b[i][j] == 1) { // Diagonal ↖
            lcs[index++] = X[i - 1];
            i--; j--;
        } else if (b[i][j] == 2) { // Up ↑
            i--;
        } else { // Left ←
            j--;
        }
    }
    
    lcs[index] = '\0';
    
    // Reverse the LCS string
    for (int k = 0; k < index / 2; k++) {
        char temp = lcs[k];
        lcs[k] = lcs[index - k - 1];
        lcs[index - k - 1] = temp;
    }
    
    printf("Longest Common Subsequence: %s\n", lcs);
}

void LCS(char X[], char Y[], int m, int n) {
    int **c = (int **)malloc((m + 1) * sizeof(int *));
    int **b = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        c[i] = (int *)malloc((n + 1) * sizeof(int));
        b[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            c[i][j] = 0;
            b[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1; // Diagonal ↖
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2; // Up ↑
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3; // Left ←
            }
        }
    }

    printf("Length of LCS: %d\n", c[m][n]);
    printLCS(X, m, n, b);

    // Free allocated memory
    for (int i = 0; i <= m; i++) {
        free(c[i]);
        free(b[i]);
    }
    free(c);
    free(b);
}

int main() {
    char X[MAX], Y[MAX];

    printf("Enter first sequence: ");
    fgets(X, MAX, stdin);
    printf("Enter second sequence: ");
    fgets(Y, MAX, stdin);

    // Remove newline character
    X[strcspn(X, "\n")] = 0;
    Y[strcspn(Y, "\n")] = 0;

    int m = strlen(X);
    int n = strlen(Y);

    LCS(X, Y, m, n);

    return 0;
}
