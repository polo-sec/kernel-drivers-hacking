#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("0.01")
MODULE_DESCRIPTION("An example skeleton for a Linux module");
MODULE_AUTHOR("PM")

static int __init lkm_example_init(void) {
  printk(KERN_INFO "Hello World! \n");
}

static void __exit lkm_example_exit(void) {
  printk(KERN_INFO "Goodbye, World \n");
}

module_init(lkm_example_init)
module_
