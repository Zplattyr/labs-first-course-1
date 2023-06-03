#include <stdio.h>

int BinarySearch(int left, int right, int value, float* key) {
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (value > key[middle]) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    printf("Enter num of pairs\n");
    int n;
    scanf("%d", &n);
    float key[n];
    int value[n];
    printf("Enter pairs separated by space\n");
    for (int i = 0; i < n; ++i) {
        scanf("%f %d", &key[i], &value[i]);
    }
    for (int i = 1; i < n; ++i) {
        int index = BinarySearch(0, i, key[i], key);
        for (int j = index; j <= i; ++j) {
            float tmpKey = key[i];
            int tmpValue = value[i];
            key[i] = key[j];
            value[i] = value[j];
            key[j] = tmpKey;
            value[j] = tmpValue;
        }
    }
    printf("Enter nums of reqs\n");
    int m;
    scanf("%d", &m);
    printf("Enter keys\n");
    for (int i = 0; i < m; ++i) {
        float resKey;
        scanf("%f", &resKey);
        int index = BinarySearch(0, n, resKey, key);
        if (key[index] == resKey) {
            printf("%d\n", value[index]);
        } else {
            printf("This key does not exist\n");
        }
    }
    return 0;
}