#include <stdio.h>



void swap1(int i, int j)
{
  int t;

  t = i;
  i = j;
  j = t;
}




void swap2(int* i, int* j)
{
  int t;

  t = *i;
  *i = *j;
  *j = t;
}

int main()
{
  int x, a, b;
  int* y;

  x = 5;
  printf("value of x is %d, address of x is %p\n", x, &x);

  y = &x;
  printf("value of y is %p, address of y is %p, object pointed by y is %d\n", y, &y, *y);

  *y = 10; *y = *y * 3;
  printf("x is %d, *y is %d\n", x, *y);

  a = 100; b = 200;

  printf("pre-swap1: a=%d, &a=%p\n", a, &a);
  printf("b=%d, &b=%p\n", b, &b);

  swap1(a, b);

  printf("after-swap1: a=%d, &a=%p\n", a, &a);
  printf("b=%d, &b=%p\n", b, &b);

  swap2(&a, &b);

  printf("after-swap2: a=%d, &a=%p\n", a, &a);
  printf("b=%d, &b=%p\n", b, &b);

  return 0;
}
