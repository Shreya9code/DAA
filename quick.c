#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000  

int comparisons = 0;  // Counter for comparisons

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (Last element as pivot)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;  

    for (int j = low; j < high; j++) {
        comparisons++;  
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);
}

// QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Generate random numbers and save to file
void generateRandomNumbers(int size, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    srand(time(0));  
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d\n", rand() % 10000);  
    }
    fclose(fp);
}

// Read numbers from file
int readNumbers(int arr[], const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    int size = 0;
    while (fscanf(fp, "%d", &arr[size]) != EOF) {
        size++;
    }
    fclose(fp);
    return size;
}

// Write sorted numbers to file
void writeSortedNumbers(int arr[], int size, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}

// Main function
int main() {
    int arr[MAX_SIZE], size;
    int sizes[] = {10, 100, 1000};
    char ran_filename[20], out_filename[20];

    for (int i = 0; i < 3; i++) {
        comparisons = 0;  // Reset counter

        // Create filenames dynamically
        sprintf(ran_filename, "ran_%d.txt", sizes[i]);
        sprintf(out_filename, "out_%d.txt", sizes[i]);

        generateRandomNumbers(sizes[i], ran_filename);  
        size = readNumbers(arr, ran_filename);  

        quickSort(arr, 0, size - 1);  

        writeSortedNumbers(arr, size, out_filename);  

        printf("Size: %d, Comparisons: %d (Results in %s)\n", sizes[i], comparisons, out_filename);
    }

    return 0;
}
