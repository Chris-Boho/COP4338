#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/ioctl.h>

/*
Christopher Bohorquez
PID: 6039295
Multi-User String Device Driver
*/

#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM

#define WR_LOWER _IOW('a','a',char*)
#define RD_LOWER _IOR('a','b',char*)

#define WR_UPPER _IOW('a','c',char*)
#define RD_UPPER _IOR('a','d',char*)

#define WR_NOCHANGE _IOW('a','e',char*)
#define RD_NOCHANGE _IOR('a','f',char*)

int main(){
   int ret, fd, choice;
   char value[256];
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");
   fd = open("/dev/testchar", O_RDWR);             // Open the device with read/write access
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }

   printf("Type in a short string to send to the kernel module:\n");
   scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
   char *teststr = stringToSend;
   printf("How would you like the string to be returned(Enter a #):\n1)All Lower\n2)All Upper\n3)No Change\n");
   scanf("%d", &choice);

   printf("Writing message to the device [%s].\n", stringToSend);

   switch (choice) {
     case 1:
          ioctl(fd, WR_LOWER, (char*) &teststr);
          break;
     case 2:
          ioctl(fd, WR_UPPER, (char*) &teststr);
          break;
     case 3:
          ioctl(fd, WR_NOCHANGE, (char*) &teststr);
          break;
   }

   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }

  printf("Press ENTER to read back from the device...\n");
    getchar();
  printf("Reading from the device...\n");

  switch (choice) {
    case 1:
         ioctl(fd, RD_LOWER, (char*) &value);
         printf("Formatted text is [%s]\n", value);
         break;
    case 2:
         ioctl(fd, RD_UPPER, (char*) &value);
         printf("Formatted text is [%s]\n", value);
         break;
    case 3:
         ioctl(fd, RD_NOCHANGE, (char*) &value);
         printf("Formatted text is [%s]\n", value);
         break;
  }


  ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM

  if (ret < 0){
     perror("Failed to read the message from the device.");
     return errno;
  }
  printf("The received message is: [%s]\n", receive);
  printf("End of the program\n");
  return 0;
}
