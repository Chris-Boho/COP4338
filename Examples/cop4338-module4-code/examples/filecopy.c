#include <stdio.h>
#include <stdlib.h>

#define BUFSIZ 1024

void mycopy(FILE* fpsrc, FILE* fpdest)
{
  char buf[BUFSIZ];
  int total = 0;

  for(;;) {
    int x = fread(buf, 1, BUFSIZ, fpsrc);
    if(x > 0) {
      int y = fwrite(buf, 1, x, fpdest);
      if(y < x) {
	fprintf(stderr, "ERROR: writing file\n");
	break;
      }
      total += y;
    } else break;
  }

  printf("Copied %d bytes\n", total);
}

int main(int argc, char* argv[])
{
  FILE *fpsrc, *fpdest;
  int offset;

  if(argc != 4) {
    fprintf(stderr, "Usage: %s offset SRCFILE DSTFILE\n", argv[0]);
    return 1;
  }

  offset = atoi(argv[1]);

  fpsrc = fopen(argv[2], "r");
  if(!fpsrc) { 
    fprintf(stderr, "ERROR: can't open source file to read: %s\n", argv[2]);
    return 2;
  }

  fpdest = fopen(argv[3], "w");
  if(!fpdest) { 
    fprintf(stderr, "ERROR: can't open destination file to write: %s\n", argv[3]);
    return 3;
  }

  if(offset >= 0) fseek(fpsrc, offset, SEEK_SET);
  else fseek(fpsrc, -offset, SEEK_END);

  mycopy(fpsrc, fpdest);

  fclose(fpsrc);
  fclose(fpdest);

  return 0;
}
