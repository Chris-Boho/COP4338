#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZ 1024

void mycopy(int fdsrc, int fddest)
{
  char buf[BUFSIZ];
  int total = 0;

  for(;;) {
    int written = 0;

    int x = read(fdsrc, buf, BUFSIZ);
    if(x < 0) { perror("ERROR: reading file"); return; }
    else if(x == 0) break;

    while (x > 0) {
      int y = write(fddest, &buf[written], x);
      if(y < 0) { perror("ERROR: writing file"); return; }
      x -= y;
      written += y;
    }

    total += written;
  }

  printf("Copied %d bytes\n", total);
}

int main(int argc, char* argv[])
{
  int fdsrc, fddest;
  int offset;

  if(argc != 4) {
    fprintf(stderr, "Usage: %s offset SRCFILE DSTFILE\n", argv[0]);
    return 1;
  }

  offset = atoi(argv[1]);

  fdsrc = open(argv[2], O_RDONLY);
  if(fdsrc < 0) { 
    fprintf(stderr, "ERROR: can't open source file to read: %s\n", argv[2]);
    return 2;
  }

  fddest = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0644);
  if(fddest < 0) { 
    fprintf(stderr, "ERROR: can't open destination file to write: %s\n", argv[3]);
    return 3;
  }

  if(offset >= 0) lseek(fdsrc, offset, SEEK_SET);
  else lseek(fdsrc, -offset, SEEK_END);

  mycopy(fdsrc, fddest);

  close(fdsrc);
  close(fddest);

  return 0;
}
