#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE "mumford_demand.txt"
#define OUTPUT_FILE "output2.txt"

// Function to merge two subarrays arr[l..m] and arr[m+1..r]
void merge(int arr[], int l, int m, int r, int* num_swaps) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            *num_swaps += n1 - i; // Increment number of swaps
        }
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Recursive function to perform Merge Sort
void mergeSort(int arr[], int l, int r, int* num_swaps) {
    if (l < r) {
        int m = l + (r - l) / 2; // Calculate mid point

        // Recursively sort the two halves
        mergeSort(arr, l, m, num_swaps);
        mergeSort(arr, m + 1, r, num_swaps);

        // Merge the sorted halves
        merge(arr, l, m, r, num_swaps);
    }
}

int main() {
    // Read input from file
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        perror("Error opening input file");
        return 1;
    }
    int arr[100000]; // Assuming a maximum of 1000 elements in the input file
    int num_elements = 0;
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        arr[num_elements++] = num;
    }
    fclose(file);

    // Measure execution time
    clock_t start_time = clock();

    // Perform Merge Sort
    int num_swaps = 0;
    mergeSort(arr, 0, num_elements - 1, &num_swaps);

    // Calculate execution time
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Write sorted array, execution time, and number of swaps to output file
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
