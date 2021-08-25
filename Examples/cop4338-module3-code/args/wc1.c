#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG 0

#define IN  0 /* inside a word */
#define OUT 1 /* outside a world */

void usage()
{
  fprintf(stderr, "usage: wc [-clmw] [file ...]\n");
  exit(1);
}

void count(FILE* fp, int pl, int pw, int pc, char* fname)
{
  int c; /* input character */
  int nl, nw, nc; /* counters for lines, words, and characters */
  int state; /* whether it's in the middle of a word */

  /* counting lines, words, and characters */
  nl = nw = nc = 0;
  state = OUT;
  while((c = getc(fp)) != EOF) {
    nc++;
    switch(c) {
    case '\n':
      nl++;
      /* no break here*/
    case ' ':
    case '\t':
      state = OUT;
      break;
    default:
      if(state == OUT) {
	state = IN;
	nw++;
#if DEBUG
	printf("\n");
#endif
      }
#if DEBUG
      printf("%c", c);
#endif
    }
  }

#if DEBUG
  printf("\n");
#endif
  if(pl) printf("%8d", nl);
  if(pw) printf("%8d", nw);
  if(pc) printf("%8d", nc);
  printf(" %s\n", fname);
}

int main(int argc, char* argv[])
{
  int c; /* input character */
  int pl, pw, pc; /* whether the user wants to print line, word, and character count */
  FILE* fp; /* input file pointer */
  
  /* parse command-line arguments */
  pl = pw = pc = 0;
  while ((c = getopt(argc, argv, "clmw")) != -1) {
    switch(c) {
    case 'c':
    case 'm':
      pc = 1;
      break;
    case 'l':
      pl = 1;
      break;
    case 'w':
      pw = 1;
      break;
    case '?':
    default:
      usage();
    }
  }
  argc -= optind;
  argv += optind;
  if(!pc && !pl && !pw)
    pl = pw = pc = 1;

  if(argc == 0) {
    fp = stdin; 
    count(fp, pl, pw, pc, "");
  } else {
    int i;
    for(i=0; i<argc; i++) {
      fp = fopen(argv[i], "r");
      if(!fp) {
	perror("can't open file");
	return 1;
      }
      count(fp, pl, pw, pc, argv[i]);
      fclose(fp);
    }
  }

  return 0;
}
