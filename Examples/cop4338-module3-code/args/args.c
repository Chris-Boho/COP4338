#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int i;
  printf("you entered %d command-line argument(s):\n", argc);
  for(i=0; i<argc; i++) 
    printf("argv[%d]: %s\n", i, argv[i]);
  
  // want to turn a string to int, long, or double?
  if(argc != 4) { printf("USAGE: %s <int> <long> <double>\n", argv[0]); return -1; }
  int arg1 = atoi(argv[1]);
  long arg2 = atol(argv[2]);
  double arg3 = atof(argv[3]);
  printf("arg1=%d, arg2=%ld, arg3=%lf\n", arg1, arg2, arg3);

  return 0;
}
