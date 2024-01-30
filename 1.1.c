// Experiment No.1: 
// 1.1 Write a program to implement binary search. The binary search must be defined in a separate function. It should be iterative version. You need to write a file which shows the execution time and memory taken along with the input details.
// 1.2 Write a program to implement binary search. The binary search must be defined in a separate function. It should be recursive version.  You need to write a file which shows the execution time and memory taken along with the input details.
// 1.3 Compare the iterative version and recursive version of binary search. Report some insights of the comparison.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>

struct return_value
{
    int index;
    double executionTime;
    long memory_usage;
};


void calculateMemory(struct return_value *result)
{

    result->memory_usage = 0;
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    result->memory_usage = pmc.PrivateUsage;

}


struct return_value binarySearch(int *arr, int size, int key)
{

    clock_t start_time = clock();

    int low = 0;
    int high = size - 1;
    int ans = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
        {
            ans = mid;
            break;
        }
        else if (arr[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }


    double execution_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;

    struct return_value result = {ans, execution_time, 0};
    calculateMemory(&result);

    return result;
}

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);


    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }


    printf("Enter sorted array elements:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Enter the element at index %d: ", i);
        scanf("%d", &arr[i]);
    }

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);


    struct return_value result = binarySearch(arr, size, key);

    if (result.index == -1)
    {
        printf("The key %d is not found in the array\n", key);
    }
    else
    {
        printf("The key %d is found at index %d in the array\n", key, result.index);
    }

    printf("Execution Time: %.6f seconds\n", result.executionTime);
    printf("Memory Usage: %ld KB\n", result.memory_usage);

    FILE *csv_file = fopen("binary_search_results.csv", "a");
    if (csv_file == NULL)
    {
        fprintf(stderr, "Error opening CSV file\n");
        free(arr); 
        return 1;
    }

    long file_size;
    fseek(csv_file, 0, SEEK_END);
    file_size = ftell(csv_file);
    if (file_size == 0)
    {
        fprintf(csv_file, "<<<<<<<<<Welcome Savant coder>>>>>>>>\n");
        fprintf(csv_file, "Array Size,Target Element,Result Index,Execution Time,Memory Usage\n");
    }

    fprintf(csv_file, "%d,%d,%d,%.6f,%ld\n", size, key, result.index, result.executionTime, result.memory_usage);
    fclose(csv_file);
    free(arr);

    return 0;
}