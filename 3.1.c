#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE "mumford_demand.txt"
#define OUTPUT_FILE "output.txt"

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high, int* num_swaps) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*num_swaps)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*num_swaps)++;
    return (i + 1);
}

// Recursive function to perform Quick Sort
void quickSort(int arr[], int low, int high, int* num_swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, num_swaps);
        quickSort(arr, low, pi - 1, num_swaps);
        quickSort(arr, pi + 1, high, num_swaps);
    }
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        perror("Error opening input file");
        return 1;
    }
    int arr[100000]; 
    int num_elements = 0;
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        arr[num_elements++] = num;
    }
    fclose(file);

    clock_t start_time = clock();


    int num_swaps = 0;
    quickSort(arr, 0, num_elements - 1, &num_swaps);


    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  
    FILE* output_file = fopen(OUTPUT_FILE, "w");
    if (!output_file) {
        perror("Error opening output file");
        return 1;
    }
    for (int i = 0; i < num_elements; i++) {
        fprintf(output_file, "%d ", arr[i]);
    }
    fprintf(output_file, "\n\nExecution time: %f seconds\n", execution_time);
    fprintf(output_file, "Number of swaps: %d\n", num_swaps);
    fclose(output_file);

    return 0;
}
