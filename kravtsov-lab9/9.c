#include <stdlib.h>
#include <stdio.h>

#define I_START_POINT 5
#define J_START_POINT 5
#define L_START_POINT 4
#define I_CENTER_FIRST -10
#define J_CENTER_FIRST -10
#define I_CENTER_SECOND -20
#define J_CENTER_SECOND -20
#define RADIUS 10
#define STEPS 50

int Sign(int num) {

    if (num > 0) {
        return 1; 
    }
        
    if (num == 0) {
        return 0; 
    }
        
    return -1;  

}

int Max(int a,int b){

    if (a>b) {
        return a;
    }

    return b;
}

int Abs(int a) {
    
    if (a < 0) {
        return -a;
    }

    return a;
}


int CheckInArea(int i,int j) {
    
    int firstDistance = (i - I_CENTER_FIRST)*(i - I_CENTER_FIRST) 
    + (j - J_CENTER_FIRST)*(j - J_CENTER_FIRST);
    
    int secondDistance = (i - I_CENTER_SECOND)*(i - I_CENTER_SECOND) 
    + (j - J_CENTER_SECOND)*(j - J_CENTER_SECOND);
    
    return (firstDistance <= RADIUS*RADIUS) && (secondDistance <= RADIUS*RADIUS);

}


int IncreaseI(int k, int i, int j, int l) {
    return i/3 - Abs(i-k)*Sign(l-j);
}

int IncreaseJ(int k, int i, int j, int l) {
    return j%10 - Max(i,l)%(k+1);
}

int IncreaseL(int k, int i, int j, int l) {
    return i + (j*k)%5 + l/5 + 3;
}

int Lab9(int i, int j, int l) {
    int k = 0;

    while (k<=STEPS) {

        if (CheckInArea(i,j)) {
            printf("%d: i = %d; j = %d; l = %d\n", k, i, j, l);
            printf("Есть попадание\n");
            return 1; 
        }
        k++;
        if (k == STEPS+1) {
            printf("%d: i = %d; j = %d; l = %d\n", k-1, i, j, l);
            printf("Промах\n");
            return 0;
        }
        int newI = IncreaseI(k-1,i,j,l);
        int newJ = IncreaseJ(k-1,i,j,l);
        int newL = IncreaseL(k-1,i,j,l);
        i = newI;
        j = newJ;
        l = newL;
        
    }
        
    
}

int main() {
    Lab9(I_START_POINT,J_START_POINT,L_START_POINT);

    return 0;
}


