#include <stdio.h>

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] != 0) {
                ++count;
            }
        }
    }
    int M[n];
    for (int i = 0; i < n; ++i) {
        M[i] = 0;
    }
    int A[count][3];
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                A[index][0] = j;
                A[index][1] = matrix[i][j];
                A[index][2] = index + 1;
                ++index;
                if (M[i] == 0) {
                    M[i] = index;
                }
            }
        }
        if (A[index - 1][2] != 0) {
            A[index - 1][2] = 0;
        }
    } 

    int columns[m];
    int num2 = - 1;
    int num1 = - 1;
    int max = -__INT_MAX__+2;
    printf("\n");
    for(int i = 0; i < count; ++i) {
        columns[A[i][0]] += 1;
    }
    for(int i = 0; i < m; ++i) {
        if (columns[i] >= max) {
            max = columns[i];
            num2 = num1;
            num1 = i;
        }
    }
    if (num2 == -1) {
        num2 = num1;
    }
    
    int mult = 1;
    for(int i = 0; i < count; ++i) {
        if (A[i][0] == num2) {
            mult *= A[i][1];
        }
    }

    printf("%d %d", num2, mult);
    return 0;
}