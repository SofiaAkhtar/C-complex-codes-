#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE "mumford_demand.txt"
#define OUTPUT_FILE "output2.txt"

// Structure for a node in the binary tree
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (!temp) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node in the binary tree
struct Node* insert(struct Node* root, int data) {
    if (!root) {
        return newNode(data);
    }
    if (data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

// Function to heapify a subtree rooted with the node 'root'
void heapify(struct Node* root) {
    if (!root)
        return;
    struct Node *smallest = root;
    struct Node *l = root->left;
    struct Node *r = root->right;
    if (l && l->data < smallest->data)
        smallest = l;
    if (r && r->data < smallest->data)
        smallest = r;
    if (smallest != root) {
        int temp = root->data;
        root->data = smallest->data;
        smallest->data = temp;
        heapify(smallest);
    }
}

// Function to do heap sort
void heapSort(struct Node* root) {
    if (!root)
        return;
    heapSort(root->left);
    heapSort(root->right);
    heapify(root);
}

// Function to delete a binary tree
void deleteTree(struct Node* root) {
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Function to measure execution time and perform heap sort
void measureAndSort(struct Node* root) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    heapSort(root);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Open the output file for writing
    FILE* output_file = fopen(OUTPUT_FILE, "w");
    if (!output_file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Function to print sorted data to output file
    void printSorted(struct Node* root, FILE* output_file) {
        if (!root)
            return;
        printSorted(root->left, output_file);
        fprintf(output_file, "%d ", root->data);
        printSorted(root->right, output_file);
    }

    // Print sorted data to output file
    printSorted(root, output_file);

    // Print execution time and space complexity to the output file
    fprintf(output_file, "\n\nExecution time: %f seconds\n", cpu_time_used);
    fprintf(output_file, "Space complexity: O(n)\n");

    // Close the output file
    fclose(output_file);
}

int main() {
    // Read input from file and build the binary tree
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        perror("Error opening input file");
        return 1;
    }
    int num;
    struct Node* root = NULL;
    while (fscanf(file, "%d", &num) != EOF) {
        root = insert(root, num);
    }
    fclose(file);

    // Measure execution time and perform heap sort
    measureAndSort(root);

    // Delete the binary tree to free memory
    deleteTree(root);

    return 0;
}
