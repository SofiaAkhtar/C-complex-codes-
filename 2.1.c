// Build a Min Priority queue. Define all the operations of Priority queue. Demonstrate overflow
// and underflow conditions. Initially build the Priority Queue by taking input from a file. You must
// take the test case of Mumford-1 network demand given in Table 4 under Appendix.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100000
#define INPUT_FILE "mumford_demand.txt"
#define OUTPUT_FILE "output1.txt"

struct MinPriorityQueue {
    int heap[MAX_SIZE];
    int size;
};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct MinPriorityQueue *createMinPriorityQueue() {
    struct MinPriorityQueue *minPQ = (struct MinPriorityQueue *)malloc(sizeof(struct MinPriorityQueue));
    minPQ->size = 0;
    return minPQ;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void heapifyUp(struct MinPriorityQueue *minPQ, int i) {
    while (i > 0 && minPQ->heap[parent(i)] > minPQ->heap[i]) {
        swap(&minPQ->heap[parent(i)], &minPQ->heap[i]);
        i = parent(i);
    }
}

void heapifyDown(struct MinPriorityQueue *minPQ, int i) {
    int minIndex = i;
    int left = leftChild(i);
    int right = rightChild(i);
    if (left < minPQ->size && minPQ->heap[left] < minPQ->heap[minIndex]) {
        minIndex = left;
    }
    if (right < minPQ->size && minPQ->heap[right] < minPQ->heap[minIndex]) {
        minIndex = right;
    }
    if (minIndex != i) {
        swap(&minPQ->heap[i], &minPQ->heap[minIndex]);
        heapifyDown(minPQ, minIndex);
    }
}

void insert(struct MinPriorityQueue *minPQ, int key) {
    if (minPQ->size >= MAX_SIZE) {
        printf("Overflow: Priority Queue is full\n");
        return;
    }
    minPQ->heap[minPQ->size++] = key;
    heapifyUp(minPQ, minPQ->size - 1);
}

int deleteMin(struct MinPriorityQueue *minPQ) {
    if (minPQ->size <= 0) {
        printf("Underflow: Priority Queue is empty\n");
        return -1;
    }
    int minElement = minPQ->heap[0];
    minPQ->heap[0] = minPQ->heap[--minPQ->size];
    heapifyDown(minPQ, 0);
    return minElement;
}

void readInputFromFile(struct MinPriorityQueue *minPQ) {
    FILE *file = fopen(INPUT_FILE, "r");
    if (file == NULL) {
        printf("Error opening input file.\n");
        exit(EXIT_FAILURE);
    }
    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        insert(minPQ, num);
    }
    fclose(file);
}

void writeOutputToFile(int *output, int size) {
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file == NULL) {
        printf("Error opening output file.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", output[i]);
    }
    fclose(file);
}

// Example usage
int main() {
    struct MinPriorityQueue *minPQ = createMinPriorityQueue();

    // Read input from file
    readInputFromFile(minPQ);

    // Delete minimum elements and write to output file
    int output[MAX_SIZE];
    int index = 0;
    while (minPQ->size > 0) {
        output[index++] = deleteMin(minPQ);
    }

    // Write output to file
    writeOutputToFile(output, index);

    printf("Output written to %s\n", OUTPUT_FILE);

    return 0;
}
