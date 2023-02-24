#include <stdio.h>
void pri_arr (int ncol, int nlines, int a[]) {
  int i, j;

  for(i = 0; i < nlines; i++)
    for (j = 0; j < ncol || (puts(""), 0); j++)
      printf("%d ", a[i * ncol + j]);
}


int main()
{
  puts("2 dim");
  int a[3][4] = {{1, 2, 3, 4},
         {11, 12, 13, 14},
         {21, 22, 23, 24}};
  pri_arr(4, 3, &a[0][0]);
}