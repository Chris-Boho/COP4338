#include <stdio.h>

/* copy from b to a */
void mystrcpy(char* a, char* b)
{
  /* we assume both a and b can't be null */
 
  /* beginner version */
  while(*b != '\0') {
    *a = *b;
    a++;
    b++;
  }
  *a = *b; /* copy the null character */

  /* expert version */ 
  //while((*a++ = *b++));
}

void mystrcmp(char* a, char* b)
{
  /* we assume both a and b can't be null */
  while(*a == *b) {
    if(*a == '\0') printf("4: a is equal to b\n");
    a++; b++;
  }
  if(*a < *b) printf("4: a is less than b\n");
  else printf("4: a is greater than b\n");
}

void mystrcat(char* a, char* b)
{
  /* we assume both a and b can't be null */
  while(*a) a++;
  while((*a++ = *b++));
}


int mylen(char* s)
{
  if(!s) return 0;

  int l = 0;
  while(s[l++]);
  return l-1;
}

int main()
{
  char* x = "string";
  char y[] = "this";
  char z[100];
  int w[10];

  printf("sizeof(x)=%lu, sizeof(y)=%lu, sizeof(z)=%lu, sizeof(w)=%lu\n", 
	 sizeof(x), sizeof(y), sizeof(z), sizeof(w));

  printf("x=%p, &x=%p, *x='%c',%d, x:\"%s\"\n", x, &x, *x, *x, x);
  printf("y=%p, &y=%p, *y='%c',%d, y:\"%s\"\n", y, &y, *y, *y, y);
  
  x++;
  printf("x=%p, &x=%p, *x='%c',%d, x:\"%s\"\n", x, &x, *x, *x, x);

  /*
  y++;
  printf("y=%p, &y=%p, *y='%c',%d, y:\"%s\"\n", y, &y, *y, *y, y);
  */

  printf("len(x)=%d, len(y)=%d, len(z)=%d\n", mylen(x), mylen(y), mylen(z));
  printf("len(\"\")=%d\n", mylen(""));
  printf("len(0)=%d\n", mylen(0));
  return 0;


  x++;
  printf("2: value of x is %p, address of x is %p, object pointed by x is '%c', string pointed by x is \"%s\"\n", 
	 x, &x, *x, x);
  /* you cannot do y++ */

  mystrcpy(z, x); /* what happens if you do mystrcpy(x, y) instead? */
  printf("3: value of z is %p, address of z is %p, object pointed by z is '%c', string pointed by z is \"%s\"\n", 
	 z, &z, *z, z);

  mystrcmp(x, y);

  mystrcat(z, y);
  printf("3: value of z is %p, address of z is %p, object pointed by z is '%c', string pointed by z is \"%s\"\n", 
	 z, &z, *z, z);

  return 0;
}
