#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned int value;
    struct node* next;
    struct node* prev;
} node;

node* Create(unsigned int value) {
    node* root = (node*)malloc(sizeof(node));
    root->next = NULL;
    root->prev = NULL;
    root->value = value;
    return root;
}

void Insert(node* root, int index, unsigned int value) {
    for (int i = 0; i < index; ++i) {
        if (root->next == NULL) {
            printf("Index out of range");
            exit(1);
        }
        root = root->next;
    }
    node* tmp = (node*)malloc(sizeof(node));
    tmp->next = NULL;
    tmp->prev = root;
    tmp->value = value;
    root->next = tmp;
    return;
}

void Print(node* root) {
    root = root->next;
    while (root != NULL) {
        printf("%u ", root->value);
        root = root->next;
    }
    printf("\n");
}

node* PushFront(node* root, unsigned int value) {
    node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = value;
    tmp->next = root;
    tmp->prev = NULL;
    if (root) {
        root->prev = tmp;
    }
    root = tmp;
    return root;
}

void Erase(node* root, int index) {
    for (int i = 0; i < index; ++i) {
        if (root == NULL) {
            printf("Index out of range");
            exit(1);
        }
        root = root->next;
    }
    root->next = root->next->next;
    return;
}

int Size(node* root) {
    int count = 0;
    while (root != NULL) {
        root = root->next;
        ++count;
    }
    return count - 1;
}

int FindIndex(node* root, unsigned int elem) {
    int size = Size(root);
    for (int i = 0; i < size; ++i) {
        if (root == NULL) {
            printf("Can't find elem");
            exit(1);
        }
        if(root -> value == elem) {
            return i;
        }
        root = root->next;
    } 
}

unsigned int Find(node* root, int index) {
    for (int i = 0; i < index; ++i) {
        if (root == NULL) {
            printf("Index out of range");
            exit(1);
        }
        root = root->next;
    }
    return root -> value;
}

node* Solve(node* root, int k) {
    unsigned int elem = Find(root, Size(root));
    for(int i = 0; i < k + 1; ++i) {
        root = PushFront(root, elem);
    }
    return root;
}

int main() {
    int n;
    int k;
    scanf("%d", &n);
    unsigned int value;  
    scanf("%u", &value);
    node* list = Create(value);
    for (int i = 0; i < n - 1; ++i) {
        unsigned int value;  
        scanf("%u", &value);
        Insert(list, i, value);
    }
    scanf("%d", &k);
    list = Solve(list, k);
    Print(list);
    return 0;
}