#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int sz, i;
  int* x;

  if(argc != 2) { printf("USAGE: %s <size>\n", argv[0]); return -1; }
  sz = atoi(argv[1]);
  if(sz <= 0) { printf("ERROR: wrong size (%s)\n", argv[1]); return -2; }

#if 0
  double myarray[sz]; // this is WRONG!
  myarray[1] = 1.0; // REGARDLESS, this is WRONG!
#endif
  
  x = (int*)malloc(sz*sizeof(int));
  if(!x) { printf("ERROR: unable to allocate memory of size %d\n", sz); return -3; }

  for(i=0; i<sz; i++) x[i] = i*10;
  for(i=0; i<sz; i++) printf("%d: %d\n", i, x[i]);
  
  free(x);

  return 0;
}
