#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "McodeMod.c"

char *mcodestring(int asciicode);

int main(int argc, char *argv[])
{
     if(!strcmp(argv[1], "-w")){

          char word[256];
          strcpy(word, argv[2]);

          for (int i = 0; word[i] != 0; i++){
               char letter = word[i];
               int num = (int)letter;
               char *mcode = mcodestring(num);
               printf("Translated Letter: %s\n", mcode);
          }
     } else{
          printf("Please enter a valid command line argument...\n");
     }


	return 0;
}
