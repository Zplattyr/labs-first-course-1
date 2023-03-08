#include <stdio.h>
#include <stdlib.h>

struct tree {      
  int key;
  struct tree *left, *right;
};

struct tree* AddNode(struct tree* p, int k) {
  if (p == NULL) {
    p = (struct tree*)malloc(sizeof(struct tree));
    p->key = k;
    p->left = p->right = NULL;
  }
  else if (k < p->key)
    p->left = AddNode(p->left, k);
  else
    p->right = AddNode(p->right, k);

  return p;
}

int IsLeaf(struct tree* p) {
  if ((p->left == NULL) && (p->right == NULL)) {
    return 1;
  }
  return 0;
}

int DeleteNode(struct tree* p, int k) {
  if (p->right != NULL && p->right->key == k) {
      if (IsLeaf(p->right)) {
        free(p->right);
        p->right = NULL;
        return 0;
      } else {
        if (p->right->right != NULL){
          p->right->key = p->right->right->key;
          DeleteNode(p->right, p->right->right->key);
        } else {
          p->right->key = p->right->left->key;
          DeleteNode(p->right, p->right->left->key);
        }
      }
  } else if (p->left != NULL && p->left->key == k) {
      if (IsLeaf(p->left)) {
        free(p->left);
        p->left = NULL;
        return 0;
      } else {
        if (p->left->right != NULL){
          p->left->key = p->left->right->key;
          DeleteNode(p->left, p->left->right->key);
        } else {
          p->left->key = p->left->left->key;
          DeleteNode(p->left, p->left->left->key);
        }
      }
  } else if (p->left != NULL && k < p->key) {
      DeleteNode(p->left, k);
  } else if (p->right != NULL && k >= p->key) {
      DeleteNode(p->right, k);
  }
  return 0;
}

void CountNodes(struct tree* p, int *nul, int *one, int *two) {
  if (p != NULL) {
    if ((p->left != NULL) && (p->right != NULL)) 
        ++*two;
      else if ((p->left == NULL) && (p->right == NULL)) 
        ++*nul;
      else 
        ++*one;
    CountNodes(p->left, nul, one, two);
    CountNodes(p->right, nul, one, two);
  }
}

void PrintTree(struct tree* p, int level) {
  if(p) {
    PrintTree(p->right, level + 1);
    for(int i = 0; i < level; ++i) printf("   ");
    printf("%d\n", p->key);
    PrintTree(p->left, level + 1);
  }
}

int main() {
  struct tree* root;
  int k;
  int num = 0;
  int elem;
  int minusFl = 1;
  root = NULL;
  int req;

  printf("Vvod znachenuy dereva: ");

  while((k = getchar()) != EOF) {
    if (k >= '0' && k <= '9') {
        num = num * 10 + (k - '0');
    }
    else if (k == ' ') {
        root = AddNode(root, num * (minusFl));
        num = 0;
        minusFl = 1;
    }
    else if (k == '-') {
        minusFl = -1;
    }
    else {
        root = AddNode(root, num * (minusFl));
        break;
    }
  };

  printf("1 - show tree(first 10 levels)\n2 - add node\n3 - remove node\n4 - check condition\n0 - exit\n\n");
  
  do {
    printf("Command: ");
    scanf("%d", &req);
    switch (req) {
        case 1:
            PrintTree(root, 10);
            break;
        case 2:
            printf("Enter the el to add: ");
            scanf("%d", &elem);
            root = AddNode(root, elem);
            PrintTree(root, 10);
            break;
        case 3:
            printf("Enter the el to remove: ");
            scanf("%d", &elem);
            DeleteNode(root, elem);
            PrintTree(root, 10);
            break;
        case 4:
            int nul = 0, one = 0, two = 0;
            CountNodes(root, &nul, &one, &two);
            if (nul == 1 && two == 0) 
                printf("Yes, a tree is a linear list of vertices\n");
            else 
                printf("No, a tree is not a linear list of vertices\n");
            break;
        default:
            printf("No such command: %d", req);
            break;
    }
  } while (req != 0);
  
  return 0;
}