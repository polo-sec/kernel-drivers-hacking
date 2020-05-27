#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
/* Include two new headers that will allow us to send data to and from the user
using file referance (fs) and user access (uaccess) to safely read from address
into variable*/
#include <linux/fs.h>
#include <linux/uaccess.h>

/* Define the device name */
#define DEVICE_NAME "lkm_device"

/* Define four functions prototypes, for when the device is opened, closed, read
from and written to */
static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

/* Create our struct which points each of those to the right function */
static struct file_operations fops = {
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

/* When we request a major number for the device, we need a place to write it
to */
static int major;

/* Release device method */
static int dev_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "lkm_device device opened\n");
   return 0;
}
/* Write device method */
static ssize_t dev_write(struct file *filep, const char *buffer,
                         size_t len, loff_t *offset) {

   printk(KERN_INFO "Sorry, lkm_device is read only\n");
   return -EFAULT;
}
/* Release device method */
static int dev_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "lkm_device device closed\n");
   return 0;
}
/* Read device method */
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    /* First we have to track errors */
    int errors = 0;

    /* Now we can set a message from kernel space into the user space */
    char *message = "99 Red Balloons";

    /* Because of memory control, we have to define the message length as well */
    int message_len = strlen(message);

    /* Now we can utilise the buffer variable, which we are using as a buffer
    between kernel space and user space to copy the message to user space-
    using copy_to_user with the paramaters (copy to),(data to copy),(bytes) */
    errors = copy_to_user(buffer, message, message_len);

    /* Lastly, return the message that has been sent- or the error if there
    has been one */
    return errors == 0 ? message_len : -EFAULT;
}

/* Now we're going to adjust our init function, so that we can register our
character device (chrdev), with 3 paramaters: (giveMajorNumber [0=dynamic],
device name, the struct that points the operation to the right function */
static int __init lkm_device_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "lkm_device load failed\n");
        return major;
    }

    printk(KERN_INFO "lkm_device module has been loaded: %d\n", major);
    return 0;
}

/* Exit function */
static void __exit lkm_device_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "lkm_device module has been unloaded\n");
}

module_init(lkm_device_init);
module_exit(lkm_device_exit);
