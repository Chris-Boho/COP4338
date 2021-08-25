#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"

#define MAXLINE 1024

int main()
{
  char buf[MAXLINE];

  char* str;
  printf("CMD> ");
  while((str = fgets(buf, MAXLINE-1, stdin)) != NULL) {
    /* get rid of end of line */
    size_t ln = strlen(str)-1;
    if(*str && str[ln]=='\n')
      str[ln] = '\0';
    
    /* should we terminate? */
    if(!strcmp(str, "quit") || !strcmp(str, "exit"))
      break;

    if(!strncmp(str, "insert ", 6)) {
      str += 6;
      while(*str == ' ' || *str == '\t') str++;
      if(*str) {
	printf("command: insert(\'%s\')\n", str);
	insert(str);
      } else printf("insert missing argument"); 
    } else if(!strncmp(str, "delete ", 6)) {
      str += 6;
      while(*str == ' ' || *str == '\t') str++;
      if(*str) {
	printf("command: delete(\'%s\')\n", str);
	delete(str);
      } else printf("delete missing argument"); 
    } else if(!strncmp(str, "list ", 4)) {
      str += 4;
      while(*str == ' ' || *str == '\t') str++;
      if(*str) {
	printf("command: list(%d)\n", atoi(str));
	list(atoi(str));
      } else {
	printf("command: list(0)\n");
	list(0);
      }
    } else {
      printf("unrecognized command: \'%s\'\n", buf);
    }
    printf("CMD> ");
  }

  printf("bye!\n");
}
