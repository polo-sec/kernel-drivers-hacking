/* the required header files necessary for Linux kernel development. */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* We define both the init (loading) and exit (unloading)
functions as static and returning an int. */
MODULE_LICENSE("GPL");
MODULE_VERSION("0.01")
MODULE_DESCRIPTION("An example skeleton for a Linux module");
MODULE_AUTHOR("PM")


int init_module(void){
  printk(KERN_INFO "Hello world 1.\n");
  return 0;
}

void cleanup_module(void){
  printk(KERN_INFO "Goodbye world 1.\n");
}
