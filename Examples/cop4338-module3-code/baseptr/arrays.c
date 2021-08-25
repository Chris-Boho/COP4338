#include <stdio.h>

int main()
{
  int x[5] = { 100, 110, 120, 130, 140 };
  int *y;
  int i;

  printf("x=%p, *x=%d, *(x+2)=%d\n", x, *x, *(x+2));
  for(i=0; i<5; i++)
    printf("x[%d]=%d, &x[%d]=%p\n", i, x[i], i, &x[i]);
  printf("&x=%p\n", &x);

  y = x;
  for(i=0; i<5; i++) {
    *y = *y+5;
    y++;
  }
  for(i=0; i<5; i++)
    printf("x[%d]=%d, &x[%d]=%p\n", i, x[i], i, &x[i]);

  /* on the contrary, you cannot do 'x++' since x is an array variable!!! */

  y = &x[2];
  printf("4: value of y is %p, address of y is %p, object pointed by y is %d\n", y, &y, *y);
  printf("4: value of y[2] is %d, address of y[2] is %p\n", y[2], &y[2]);

  return 0;
}
