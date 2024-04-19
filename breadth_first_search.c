#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

struct Node* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    struct Node* node = newNode(postOrder[(*postIndex)--]);

    if (inStart == inEnd)
        return node;

    int inIndex = search(inOrder, inStart, inEnd, node->data);

    node->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);

    node->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}

void bfs_traversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int main() {

    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int postIndex = 6;


    struct Node* root = bst_construct(inOrder, postOrder, 0, 6, &postIndex);

    printf("BFS Traversal: ");
    bfs_traversal(root);
    printf("\n");

    return 0;
}

