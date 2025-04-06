#include<stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

int c = 0;

void gen_seq(int m,int n) {

    int i,j,k;
    FILE *file = fopen("random.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int **A = (int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)
    {
        A[i] = (int*)malloc(n*sizeof(int));
    }
    srand(time(0));
    for(i=0;i<m;i++)
    {

        for(j=0;j<n;j++)
        {
            A[i][j] = rand() % (MAX + 1); 
        }
        
        for (j = 0; j < n; j++) {
            fprintf(file, "%d\t", A[i][j]);
        }
        fprintf(file, "\n");

    }
    

    fclose(file);
    for(i=0;i<m;i++)
    {
        free(A[i]);
    }
    free(A);
    printf("Random sequence generated and saved to random.txt\n");

}


void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    // int L[n1 + 1], R[n2 + 1];
    int *L = (int*)malloc((n1+1)*sizeof(int));
    int *R = (int*)malloc((n2+1)*sizeof(int));
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        c++; 
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void mergesort(int *A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergesort(A, p, q);
        mergesort(A, q + 1, r);
        merge(A, p, q, r);
    }
}


int main() {
    int m,n,i,j,step=0;
    printf("Enter the number of arrays(m): ");
    scanf("%d",&m);

    printf("Enter array size(n): ");
    scanf("%d",&n);

    gen_seq(m,n);

    FILE *ip = fopen("random.txt", "r"); 
    FILE *op = fopen("sorted.txt", "w");

    if (!ip || !op) {
        printf("Error opening file,,!\n");
        return 1;
    }

   

    for(i=0;i<m;i++)
    {
        c=0;
        
        int* arr = (int*)malloc(n*sizeof(int));
        
        for (j = 0; j < n; j++)
        {
            fscanf(ip, "%d", &arr[j]);
        }
            

        mergesort(arr, 0, n - 1);

        // printf("\nTotal Comparison: %d\n", c);
        step += c;

        for (j = 0; j < n; j++)
        {
            fprintf(op, "%d\t", arr[j]);
        }
        fprintf(op, "\n");

    }
    
   
    fclose(ip);
    fclose(op);

    printf("Avg comparison: %.2f\n",(float)step/(float)m);

    printf("Sorting complete. Check output.txt for results.\n");


}
