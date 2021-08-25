#include <stdio.h>
#include <stdarg.h>

void myprintf(char* fmt, ...) 
{
  va_list ap;
  char* p;

  va_start(ap, fmt);
  for(p=fmt; *p; p++) {
    if(*p != '%') putchar(*p);
    else {
      switch(*++p) {
      case 'd': { int a = va_arg(ap, int); printf("%d", a); break; }
      case 'f': printf("%lf", va_arg(ap, double)); break;
      case 's': printf("%s", va_arg(ap, char*)); break;
      default: putchar(*p);
      }
    }
  }
  va_end(ap);
}

int main()
{
  myprintf("int=%d, double=%f, string=\"%s\"\n", 10, 3.1415, "hello world!");
  return 0;
}
