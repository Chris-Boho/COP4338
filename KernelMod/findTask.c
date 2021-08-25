#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/string.h>

/*
Christopher Bohorquez
PID: 6039295
Loadable Kernel Module 
*/

static char *name = "BLANK";     //default value
module_param(name, charp, S_IRUGO);

static int num = 0;

static int __init test_init(void){
     printk(KERN_INFO "==================================================\n");
     printk(KERN_INFO "Test Module has been loaded...\n");
     struct task_struct *task = current;

     printk(KERN_INFO "Searching for: %s\n", name);

     for_each_process(task){

          if(strcmp(task->comm, name) == 0){

               printk(KERN_INFO "Found process %s with pid [%d]\n", task->comm, task->pid);
               num = 1;
          }
     }

     if (num == 0) {
          printk(KERN_INFO "Process %s not found...\n", name);
     }

     return 0;
}

static void __exit test_exit(void){
     printk(KERN_INFO "Test Module has been unloaded...\n");
}

module_init(test_init);
module_exit(test_exit);
