#include <stdio.h>

void display(FILE* in, FILE* out)
{
  int c;
  while((c = fgetc(in)) != EOF) fputc(c, out);
}

int main(int argc, char* argv[])
{
  FILE *fptr, *fptr_out;
  if(argc == 1) {
    fptr = stdin;
    fptr_out = stdout;
  } else if(argc == 2) {
    fptr = fopen(argv[1], "r");
    if(!fptr) {
      fprintf(stderr, "ERROR: can't open file (to read): %s\n", argv[1]);
      return -1;
    }
    fptr_out = stdout;
  } else if(argc == 3) {
    fptr = fopen(argv[1], "r");
    if(!fptr) {
      fprintf(stderr, "ERROR: can't open file (to read): %s\n", argv[1]);
      return -1;
    }
    fptr_out = fopen(argv[2], "w");
    if(!fptr_out) {
      fprintf(stderr, "ERROR: can't open file (to write): %s\n", argv[2]);
      return -1;
    }
  } else {
    fprintf(stderr, "ERROR: wrong arguments!\n");
    return -1; 
  }

  display(fptr, fptr_out);

  if(argc >= 2) fclose(fptr);
  if(argc >= 3) fclose(fptr_out);
  return 0;
}
