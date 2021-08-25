#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>

/*
Christopher Bohorquez
PID: 6039295
Waveform Assignment
Must be run with "sudo" to work because it needs access to /dev/input !
*/

int main(int argc, char *argv[])
{
     int fd, bytes;
     int i = 0;
     struct input_event keyboard;

     //On my machine the keyboard is event2, however it might be different
     //on another machine
     const char *pDevice = "/dev/input/event2";

     // Open Keyboard for raw data
      fd = open(pDevice, O_RDONLY | O_NONBLOCK);
      if(fd == -1)
      {
          printf("ERROR Opening %s\n", pDevice);
          return -1;
      }

     //Opens a file to write to
     FILE *dataFile;
     dataFile = fopen(argv[1], "w");
     if (dataFile == NULL){
          printf("Error\n");
          return 0;
     }

     while(i < atoi(argv[2]))
     {

          // Read Keyboard Data
          bytes = read(fd, &keyboard, sizeof(keyboard));

          //Checks if a key is pressed!
          if(keyboard.code == 3)
          {
              /*
               This shows the event/state code of the key currently pressed,
               but it has different codes for the different states of the key,
               so its not every accurate.

               For example, a key has different codes depending on if it
               is in the process of being pressed, being held, or released.

               Might be wrong, but this is what I've understood from testing different things so far.

               It as buggy and outputted "1", even if the key was released seconds ago,
               unless "3" was specified as the code being checked for.
              */

              //printf("Key State Code: %d\n",keyboard.code);
              printf("1\n");
              fputs("1", dataFile);
              i++;
              sleep(1);
          }
          else
          {
              //printf("Key State Code: %d\n",keyboard.code);

              // Nothing to read
              printf("0\n");
              fputs("0", dataFile);
              i++;
              sleep(1);
          }
     }

 return 0;
}
