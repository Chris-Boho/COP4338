#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/ctype.h>
#include <linux/mutex.h>

/*
Christopher Bohorquez
PID: 6039295
Multi-User String Device Driver
*/

#define DEVICE_NAME "testchar"
#define CLASS_NAME "test"

#define WR_LOWER _IOW('a','a',char*)
#define RD_LOWER _IOR('a','b',char*)

#define WR_UPPER _IOW('a','c',char*)
#define RD_UPPER _IOR('a','d',char*)

#define WR_NOCHANGE _IOW('a','e',char*)
#define RD_NOCHANGE _IOR('a','f',char*)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris");
MODULE_DESCRIPTION("A simple linux char driver");
MODULE_VERSION("0.1");

char* value = " ";
char temp[256];
static int majorNumber;
static char message[256] = {0};
static short size_of_message;
static int numberOpens = 0;
static struct class* testcharClass = NULL;
static struct device* testcharDevice = NULL;
static DEFINE_MUTEX(ebbchar_mutex);

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);
static long dev_ioctl(struct file *f , unsigned int cmd, unsigned long arg);

void stringUpr(char s[]){
    int len,i;
    len=strlen(s);

    for(i=0;i<len;i++)
        s[i]=toupper(s[i]);
}

void stringLwr(char s[]){
    int len,i;
    len=strlen(s);

    for(i=0;i<len;i++)
        s[i]=tolower(s[i]);
}

static struct file_operations fops =
{
  .open = dev_open,
  .read = dev_read,
  .write = dev_write,
  .release = dev_release,
  .unlocked_ioctl = dev_ioctl,
};

static int __init testchar_init(void){
  printk(KERN_INFO "TestChar: Initializing the TestChar LKM...\n");
  mutex_init(&ebbchar_mutex);

  //register major number
  majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
  if (majorNumber < 0) {
    printk(KERN_ALERT "TestChar failed to register a major number...\n");
    return majorNumber;
  }
  printk(KERN_INFO "TestChar: registered correctly with major number %d\n", majorNumber);

  //register device class
  testcharClass = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(testcharClass)) {
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_ALERT "Failed to register device class...\n");
    return PTR_ERR(testcharClass);
  }
  printk(KERN_INFO "TestChar: device class registed correctly\n");

  //register device driver
  testcharDevice = device_create(testcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
  if (IS_ERR(testcharDevice)) {
    class_destroy(testcharClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_ALERT "Failed to create the device\n");
    return PTR_ERR(testcharDevice);
  }
  printk(KERN_INFO "TestChar: device class created correctly\n");
  return 0;
}

static void __exit testchar_exit(void){
  device_destroy(testcharClass, MKDEV(majorNumber, 0));
  class_unregister(testcharClass);
  class_destroy(testcharClass);
  unregister_chrdev(majorNumber, DEVICE_NAME);
  mutex_destroy(&ebbchar_mutex);
  printk(KERN_INFO "TestChar: Goodbye from the LKM!\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
     if(!mutex_trylock(&ebbchar_mutex)){
      printk(KERN_ALERT "EBBChar: Device in use by another process");
      return -EBUSY;

     }
     numberOpens++;
     printk(KERN_INFO "Device has been opened %d time(s)\n", numberOpens);
     return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
     sprintf(message, "%s(%zu letters)", buffer, len);
     size_of_message = strlen(message);
     printk(KERN_INFO "Received %zu characters from the user\n", len);
     return len;
}

static int dev_release(struct inode *inodep, struct file *filep) {
     mutex_unlock(&ebbchar_mutex);
     printk(KERN_INFO "Device closed...\n");
     return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
     int error_count = 0;

   error_count = copy_to_user(buffer, message, size_of_message);

   if (error_count==0){
      printk(KERN_INFO "Sent %d characters to the user\n", size_of_message);
      return (size_of_message=0);
   }
   else {
      printk(KERN_INFO "Failed to send %d characters to the user\n", error_count);
      return -EFAULT;
   }
}

static long dev_ioctl(struct file *f , unsigned int cmd, unsigned long arg){

     switch(cmd){

          case WR_LOWER:
              copy_from_user(&value ,(char*) arg, sizeof(value));
              strcpy(temp, value);
              stringLwr(temp);

              printk(KERN_INFO "Value = %s\n", temp);
              break;

          case RD_LOWER:
              copy_to_user((char*) arg, temp, strlen(temp));
              break;

          case WR_UPPER:
               copy_from_user(&value ,(char*) arg, sizeof(value));
               strcpy(temp, value);
               stringUpr(temp);

               printk(KERN_INFO "Value = %s\n", temp);
               break;

          case RD_UPPER:
               copy_to_user((char*) arg, temp, strlen(temp));
               break;

          case WR_NOCHANGE:
               copy_from_user(&value ,(char*) arg, sizeof(value));
               strcpy(temp, value);
               printk(KERN_INFO "Value = %s\n", value);
               break;

          case RD_NOCHANGE:
               copy_to_user((char*) arg, temp, strlen(temp));
               break;
    }
    return 0;
}

module_init(testchar_init);
module_exit(testchar_exit);
