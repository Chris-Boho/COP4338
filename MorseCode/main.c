#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "McodeMod.c"

/*
Christopher Bohorquez
PID: 6039295
Morse Code
*/

char *mcodestring(int asciicode);

const int dotDelay = 300000; //microseconds
const int dashDelay = 900000; //microseconds
const int sameLetterSpace = 300000; //microseconds
const int diffLetterSpace = 900000; // microseconds

FILE *LEDHandle = NULL;
const char *LEDBrightness="/sys/class/leds/beaglebone:green:usr0/brightness";

int main(int argc, char *argv[])
{
     if(!strcmp(argv[1], "-w")){

          char word[256];
          strcpy(word, argv[2]);

          //Translate each letter one by one
          for (int i = 0; word[i] != 0; i++){
               char letter = word[i];
               int num = (int)letter;
               char *mcode = mcodestring(num);

               printf("Translated Letter: %s\n", mcode);

               //46 is a dot, 45 is a dash
               for (int j = 0; mcode[j] != 0; j++) {
                    //dot
                    if (mcode[j] == 46) {
                         if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
                    		fwrite("1", sizeof(char), 1, LEDHandle);
                    		fclose(LEDHandle);
                    	}
                         //How long LED will be on...
                    	usleep(dotDelay);

                    	if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
                    		fwrite("0", sizeof(char), 1, LEDHandle);
                    		fclose(LEDHandle);
                    	}
                         //How long LED will be off...
                    	usleep(sameLetterSpace);

                    //dash
                    } else if (mcode[j] == 45) {

                         if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
                    		fwrite("1", sizeof(char), 1, LEDHandle);
                    		fclose(LEDHandle);
                    	}
                         //How long LED will be on...
                    	usleep(dashDelay);

                    	if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
                    		fwrite("0", sizeof(char), 1, LEDHandle);
                    		fclose(LEDHandle);
                    	}
                         //How long LED will be off...
                    	usleep(sameLetterSpace);
                    }
               }

               //How long the LED will off for space between letters
               usleep(diffLetterSpace);

          }
     } else{
          printf("Please enter a valid command line argument...\n");
     }


	return 0;
}
