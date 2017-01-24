#include <stdio.h>

int sum(int, int);
void swap(int *, int *);

int x = 5;
int y = 3;

int main(int argc, char **argv)
{
  int z = sum(x,y);
  swap(&x, &y);

  printf("z (sum) = %d, swapped x = %d, y = %d\n", z, x, y);
  return 0;
}

int sum(int a, int b)
{
  int t = a + b;
  return t;
}

void swap(int *xp, int * yp)
{
  int t0 = *xp;
  int t1 = *yp;
  
  *xp = t1;
  *yp = t0;
}

