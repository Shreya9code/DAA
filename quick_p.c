#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
int comparisons_det = 0, comparisons_rand = 0;  // Counters for comparisons

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Deterministic Quick Sort (Last Element as Pivot)
int partitionDeterministic(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;  

    for (int j = low; j < high; j++) {
        comparisons_det++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortDeterministic(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionDeterministic(arr, low, high);
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, pi + 1, high);
    }
}

// Randomized Partitioning with Consecutively Different Pivots
int partitionRandomized(int arr[], int low, int high) {
    int randomPivot = low + rand() % (high - low + 1);
    swap(&arr[randomPivot], &arr[high]);  
    return partitionDeterministic(arr, low, high);
}

void quickSortRandomized(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionRandomized(arr, low, high);
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

// Generate permutations using backtracking
void permute(int arr[], int l, int r, FILE *fp) {
    if (l == r) {
        for (int i = 0; i <= r; i++) {
            fprintf(fp, "%d ", arr[i]);
        }
        fprintf(fp, "\n");
        return;
    }

    for (int i = l; i <= r; i++) {
        swap(&arr[l], &arr[i]);
        permute(arr, l + 1, r, fp);
        swap(&arr[l], &arr[i]);  // Backtrack
    }
}

// Generate permutations and store in file
void generatePermutations(int size) {
    FILE *fp;
    char filename[20];
    sprintf(filename, "perm_%d.txt", size);
    fp = fopen(filename, "w");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    int arr[MAX_SIZE];
    for (int i = 0; i < size; i++) arr[i] = i;  // 0 to N-1

    permute(arr, 0, size - 1, fp);
    fclose(fp);
}

// Read permutations from file and sort each using both methods
void processPermutations(int size) {
    FILE *fp;
    char filename[20];
    sprintf(filename, "perm_%d.txt", size);
    fp = fopen(filename, "r");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    FILE *out_fp = fopen("out.txt", "w");
    if (!out_fp) {
        printf("Error opening output file!\n");
        return;
    }

    int arr[MAX_SIZE], perm_count = 0;
    double time_det = 0, time_rand = 0;
    clock_t start, end;

    while (!feof(fp)) {
        for (int i = 0; i < size; i++) {
            if (fscanf(fp, "%d", &arr[i]) == EOF) break;
        }

        comparisons_det = comparisons_rand = 0;

        // Deterministic Quick Sort
        int arr_copy[MAX_SIZE];
        for (int i = 0; i < size; i++) arr_copy[i] = arr[i];

        start = clock();
        quickSortDeterministic(arr_copy, 0, size - 1);
        end = clock();
        time_det += ((double)(end - start)) / CLOCKS_PER_SEC;

        // Randomized Quick Sort (with consecutive different pivots)
        for (int i = 0; i < size; i++)
         arr_copy[i] = arr[i];

        start = clock();
        quickSortRandomized(arr_copy, 0, size - 1);
        end = clock();
        time_rand += ((double)(end - start)) / CLOCKS_PER_SEC;

        perm_count++;

        // Store sorted results with comparison count
        fprintf(out_fp, "Permutation: ");
        for (int i = 0; i < size; i++) {
            fprintf(out_fp, "%d ", arr[i]);
        }
        fprintf(out_fp, "\nSorted: ");
        for (int i = 0; i < size; i++) {
            fprintf(out_fp, "%d ", arr_copy[i]);
        }
        fprintf(out_fp, "\nDeterministic QuickSort Comparisons: %d\n", comparisons_det);
        fprintf(out_fp, "Randomized QuickSort Comparisons: %d\n\n", comparisons_rand);
    }

    fclose(fp);
    fclose(out_fp);

    printf("Processed %d permutations of size %d.\n", perm_count, size);
    printf("Average Time (Deterministic Quick Sort): %.6f seconds\n", time_det / perm_count);
    printf("Average Time (Randomized Quick Sort): %.6f seconds\n", time_rand / perm_count);
}

// Main function
int main() {
    int size;

    printf("Enter the number of elements (<= 10): ");
    scanf("%d", &size);

    if (size > 10) {
        printf("Size too large! Please enter a value <= 10.\n");
        return 0;
    }

    generatePermutations(size);
    processPermutations(size);

    return 0;
}
