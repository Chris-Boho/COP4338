#include <stdio.h>
#include <stdlib.h>

/* this is how you declare a struct */
struct Point {
     double x; double y; char* name;
};

struct Point callbyval(struct Point v)
{
  printf("V: x=%lf, y=%lf, name=%s\n", v.x, v.y, v.name);
  v.x += 10.0; v.y = 1.0;
  return v;
}

struct Point* callbyref(struct Point* v)
{
  printf("V: x=%lf, y=%lf, name=%s\n", v->x, v->y, v->name);
  v->x += 10; v->y = 1;
  return v;
}

struct Point* callbyref_error(struct Point* v)
{
  struct Point k, *p;
  k = *v;
  k.x += 10; k.y = 1;
  p = &k; // ERROR: function returns address of local variable
  return p;
}

int main()
{
  int i;

#if 0
  struct A { int a; double b; float c; };
  struct B { int a; float c; double b; };

  struct A x = { 1, 3.0, 1e6 };
  printf("x.a=%d, x.b=%lf, x.c=%f\n", x.a, x.b, x.c);

  printf("size(A)=%d, size(B)=%d\n", (int)sizeof(struct A), (int)sizeof(struct B));
#endif

  /* this is how you instantiate a struct (its fields are not initialized) */
  struct Point u, s, *t;

  /* this is how you instantiate and initialize a struct */
  struct Point w = { 1.0, 1.0, "(1,1)" };

  struct Point z[] = {
    { 3, 4, "(3,4)" },
    { 5, 6, "(5,6)" },
    { 0, 9, "(0,9)" }
  };

  printf("w.x=%lf, w.y=%lf, w.name=%s\n", w.x, w.y, w.name);
  for(i=0; i<sizeof(z)/sizeof(struct Point); i++)
    printf("z[%d]: x=%lf, y=%lf, name=%s\n", i, z[i].x, z[i].y, z[i].name);

  /* assignment (you can do the same to pass the struct as an argument
     or use it as a return value); note however the string is not
     copied (the pointer is) */
  u = w;
  printf("U: x=%lf, y=%lf, name=%s\n", u.x, u.y, u.name);

  struct Point* p;
  p = malloc(sizeof(struct Point));
  (*p).x = 3; // equvalent of "p->x = 3";
  p->y = 5;
  p->name = "my name";
  printf("p: x=%lf, y=%lf, name=%s\n", p->x, p->y, p->name);

  u = *p;
  printf("U: x=%lf, y=%lf, name=%s\n", u.x, u.y, u.name);

  free(p);

  s = callbyval(w);
  printf("W: x=%lf, y=%lf, name=%s\n", w.x, w.y, w.name);
  printf("S: x=%lf, y=%lf, name=%s\n", s.x, s.y, s.name);

  t = callbyref(&w);
  //t = callbyref_error(&w);
  printf("W: x=%lf, y=%lf, name=%s\n", w.x, w.y, w.name);
  printf("T: x=%lf, y=%lf, name=%s\n", t->x, t->y, t->name);

  return 0;
}


#if 0






  printf("sizeof(A)=%d, sizeof(B)=%d\n", (int)sizeof(struct A), (int)sizeof(struct B));

  /* sizeof */
  printf("sizeof(Point)=%d,%d\n", (int)sizeof(w), (int)sizeof(struct Point));



  return 0;
}

#endif
