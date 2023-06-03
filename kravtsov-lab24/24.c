#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>

typedef struct _Node {
    char value;
    struct _Node* next;
    struct _Node* prev; 
} Node;

typedef struct _Stack {
    int size;
    Node* head;
    Node* tail;
} Stack;

Stack* StackCreate() {
    Stack* tmp = (Stack*) malloc(sizeof(Stack));
    tmp -> size = 0;
    tmp -> head = tmp -> tail = NULL;
    return tmp;
}

int StackSize(Stack* stack) {
    return stack -> size;
}

int StackIsEmpty(Stack* stack) {
    return (StackSize(stack) > 0 ? 1 : 0);
}

void StackPush(Stack* stack, char value) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp -> value = value;
    tmp -> next = NULL;
    tmp -> prev = stack -> tail;
    if (stack -> tail) {
        stack -> tail -> next = tmp;
    }
    stack -> tail = tmp;

    if (stack -> head == NULL) {
        stack -> head = tmp;
    }
    ++stack -> size;
}

char StackPop(Stack* stack) {
    Node* next;
    char tmp;
    if (stack -> tail == NULL) {
        exit(4);
    }

    next = stack -> tail;
    stack -> tail = stack -> tail -> prev;
    if (stack -> tail) {
        stack -> tail -> next = NULL;
    }
    if (next == stack -> head) {
        stack -> head = NULL;
    }
    tmp = next -> value;
    free(next);

    --stack -> size;
    return tmp;
}

void StackPrint(Stack* stack) {
    Node* tmp = stack -> head;
    while (tmp) {
        printf("%c ", tmp -> value);
        tmp = tmp -> next;
    }
    printf("\n");
}

char *convertInNotation(Stack* stack, char *phrase, char *phraseInNotation, int *index, int *countOfBracket, int *countOfUnarMinus, int n) {
    for (int i = 0; i < n; ++i) {
        if (phrase[i] == '-' && (phrase[i - 1] == '(' || i == 0)) {
            StackPush(stack, phrase[i]);
            phraseInNotation[*index] = '|';
            ++*index;
            ++*countOfUnarMinus;
        } else if (StackIsEmpty(stack) == 0) {
            if (phrase[i] == '+' || phrase[i] == '-' || phrase[i] == '*' || phrase[i] == '/' || phrase[i] == '(') {
                if (phrase[i] == '(') {
                    ++*countOfBracket;
                }
                StackPush(stack, phrase[i]);
            } else {
                phraseInNotation[*index] = phrase[i];
                ++*index;
            }
        } else if (phrase[i] == '*' || phrase[i] == '/') {
            StackPush(stack, phrase[i]);
        } else if (phrase[i] == '+' || phrase[i] == '-') {
            char elem = StackPop(stack);
            if (elem == '*' || elem == '/') {
                phraseInNotation[*index] = elem;
                ++*index;
                char elem2;
                while (StackIsEmpty(stack) == 1) {
                    elem2 = StackPop(stack);
                    if (elem2 == '(') {
                        StackPush(stack, elem2);
                        break;
                    }
                    phraseInNotation[*index] = elem2;
                    ++*index;
                }
                StackPush(stack, phrase[i]);
            } else {
                StackPush(stack, elem);
                StackPush(stack, phrase[i]);
            }
        } else if (phrase[i] == '(') {
            ++*countOfBracket;
            StackPush(stack, phrase[i]);
        } else if (phrase[i] == ')') {
            ++*countOfBracket;
            char elem2;
            while (StackIsEmpty(stack) == 1) {
                elem2 = StackPop(stack);
                if (elem2 == '(') {
                    break;
                }
                phraseInNotation[*index] = elem2;
                ++*index;
            }
        } else {
            phraseInNotation[*index] = phrase[i];
            ++*index;
        }
    }
    char elem2;
    while (StackIsEmpty(stack) == 1) {
        elem2 = StackPop(stack);
        phraseInNotation[*index] = elem2;
        ++*index;
    }
    return phraseInNotation;
}

void FindElems(Node* tree, int numInt, char* nums) {
    for(int i = 0; i < numInt - 1; ++i) {
        nums[i] = tree -> prev -> value;
        tree = tree -> next;
    }
    nums[numInt - 1] = tree -> value;
}

void newExpression(Node* tree2, int numInt, char* nums, char multiplicator) {
    for(int i = numInt - 1; i >= 1; --i) {
        if (i > 1) {
            char value = nums[i];
            Node* tmp1 = (Node*) malloc(sizeof(Node));
            Node* tmp2 = (Node*) malloc(sizeof(Node));
            Node* tmp3 = (Node*) malloc(sizeof(Node));
            tmp1 -> value = '*';
            tmp2 -> value = multiplicator;
            tmp3 -> value = value;
            tmp1 -> prev = tmp2;
            tmp1 -> next = tmp3;
            tree2 -> next = tmp1;
            Node* tmp4 = (Node*) malloc(sizeof(Node));
            tmp4 -> value = '-';
            tree2 -> prev = tmp4;
            tree2 = tree2 -> prev;
        } else {
            char value1 = nums[0];
            char value2 = nums[1];
            Node* tmp1 = (Node*) malloc(sizeof(Node));
            Node* tmp2 = (Node*) malloc(sizeof(Node));
            Node* tmp3 = (Node*) malloc(sizeof(Node));
            tmp1 -> value = '*';
            tmp2 -> value = multiplicator;
            tmp3 -> value = value2;
            tmp1 -> prev = tmp2;
            tmp1 -> next = tmp3;
            tree2 -> next = tmp1;
            Node* tmp4 = (Node*) malloc(sizeof(Node));
            Node* tmp5 = (Node*) malloc(sizeof(Node));
            Node* tmp6 = (Node*) malloc(sizeof(Node));
            tmp4 -> value = '*';
            tmp5 -> value = multiplicator;
            tmp6 -> value = value1;
            tmp4 -> prev = tmp5;
            tmp4 -> next = tmp6;
            tree2 -> prev = tmp4;
        }
    }
}

void TreePrint(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree -> value == '-'){
        TreePrint(tree -> prev);
        printf("-%c*%c", tree -> next -> prev -> value, tree -> next -> next -> value);
    } else if (tree -> value == '*') {
        printf("%c*%c", tree -> prev -> value, tree -> next -> value);
    }
}

int main() {
    Stack* stack = StackCreate();
    int n;
    scanf("%d", &n);
    char phrase[n];
    char *phraseInNotation = malloc(2 * n);
    scanf("%s", phrase);
    int index = 0;
    int countOfBracket = 0;
    int countOfUnarMinus = 0;
    int numInt = 0;
    phraseInNotation = convertInNotation(stack, phrase, phraseInNotation, &index, &countOfBracket, &countOfUnarMinus, n);
    // printf("%s\n", phraseInNotation);
    Node* matrixOfTrees[n];
    index = 0;
    for(int i = 0; i < n - countOfBracket + countOfUnarMinus; ++i) {
        if (phraseInNotation[i] == '+' || phraseInNotation[i] == '-' || phraseInNotation[i] == '*' || phraseInNotation[i] == '/' || phraseInNotation[i] == '(') {
            --index;
            Node* tree = (Node*) malloc(sizeof(Node));
            tree -> value = phraseInNotation[i];
            tree -> next = matrixOfTrees[index];
            tree -> prev = matrixOfTrees[index - 1];
            --index;
            matrixOfTrees[index] = tree;
            ++index;
        } else {
            if (phraseInNotation[i] == '|') {
                Node* tree = (Node*) malloc(sizeof(Node));
                tree = NULL;
                matrixOfTrees[index] = tree;
                ++index;
            } else {
                Node* tree = (Node*) malloc(sizeof(Node));
                tree -> value = phraseInNotation[i];
                tree -> next = NULL;
                tree -> prev = NULL;
                matrixOfTrees[index] = tree;
                ++index;
                ++numInt;
            }
        }
    }
    // for(int i = 0; i < n; ++i) {
    //     printf("%c ", matrixOfTrees[i] -> value);
    // }
    Node* tree1 = matrixOfTrees[0];
    char multiplicator = tree1 -> prev -> value;
    tree1 = tree1 -> next;
    // printf("%c ", tree1 -> prev -> value);
    numInt -= 1;
    char nums[numInt];
    // printf("%d\n", numInt);
    Node* tree2 = (Node*) malloc(sizeof(Node));
    tree2 -> value = '-';
    FindElems(tree1, numInt, nums);
    // for(int i = 0; i < numInt; ++i) {
    //     printf("%c ", nums[i]);
    // }
    newExpression(tree2, numInt, nums, multiplicator);
    // printf("%c ", tree2 -> prev -> next -> value);
    TreePrint(tree2);
    printf("\n");
    return 0;
}