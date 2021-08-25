#include <stdio.h>
#include <stdlib.h>  /* contains atof() */
#include <strings.h> /* contains strcasecmp() */

double myadd(double a, double b) { return a+b; }
double mysub(double a, double b) { return a-b; }
double mymlt(double a, double b) { return a*b; }
double mydiv(double a, double b) { return a/b; }

int main(int argc, char* argv[])
{
  char* opstr;
  double oprand1, oprand2;
  double (*op)(double, double); /* what if the functions don't have the same signature? */

  if(argc != 4) {
    fprintf(stderr, "Usage: %s oprand1 operator oprand2\n", argv[0]);
    return 1;
  }

  oprand1 = atof(argv[1]);
  oprand2 = atof(argv[3]);
  opstr = argv[2];

  if(!strcasecmp(opstr, "+") || !strcasecmp(opstr, "add") || !strcasecmp(opstr, "plus")) op = &myadd;
  else if(!strcasecmp(opstr, "-") || !strcasecmp(opstr, "sub") || !strcasecmp(opstr, "minus")) op = &mysub;
  else if(!strcasecmp(opstr, "*") || !strcasecmp(opstr, "multiply") || !strcasecmp(opstr, "times")) op = &mymlt;
  else if(!strcasecmp(opstr, "/") || !strcasecmp(opstr, "divide") || !strcasecmp(opstr, "div")) op = &mydiv;
  else {
    fprintf(stderr, "ERROR: unknown operator: %s\n", opstr);
    return 2;
  }

  printf("%lf %s %lf = %lf\n", oprand1, argv[2], oprand2, (*op)(oprand1, oprand2));
  return 0;
}
