#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/slab.h> 
 
static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

struct tostring_s {
  int pointer;
  unsigned long long int tostring_stack[64];
  ssize_t (*tostring_read)(struct file *f, char __user *buf, size_t len, loff_t *off); 
};

static struct tostring_s tostring;

 
static int tostring_open(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Tostring: open()\n");
  return 0;
}
 
static int tostring_close(struct inode *i, struct file *f)
{
  printk(KERN_INFO "Tostring: close()\n");
  return 0;
}
 
static ssize_t tostring_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "Tostring: read()\n");
  return(tostring.tostring_read)(f, buf, len, off); 
}

static ssize_t tostring_read_hexa(struct file *f, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "Tostring: read_hexa()\n");
  if (tostring.pointer > 0)
    return(snprintf(buf,len,"%16llx\n",tostring.tostring_stack[--tostring.pointer]));
  else return(0);
}

static ssize_t tostring_read_dec(struct file *f, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "Tostring: read_dec()\n");
  if (tostring.pointer > 0)
    return(snprintf(buf,len,"%lld\n",tostring.tostring_stack[--tostring.pointer]));
  else return(0);
}


 
static ssize_t tostring_write(struct file *f, const char __user *buf,size_t len, loff_t *off)
{
 
  char *bufk;
  
  printk(KERN_INFO "Tostring: write()\n");
  // rajout du 0 final
  
  bufk = kmalloc(len + 1, GFP_DMA);

 
  if (bufk){
 
    if (copy_from_user(bufk, buf, len))
        return -EFAULT;
 
    bufk[len] = '\0';
    
    
    if (bufk[0]=='M') {
      if (bufk[1]=='H') tostring.tostring_read= tostring_read_hexa;
      else if (bufk[1]=='D') tostring.tostring_read= tostring_read_dec;
    }
    else {
      printk("tostring: insertion %d\n",*((int *) bufk));
      tostring.tostring_stack[tostring.pointer++]= *((long long int *) bufk);;      
    }
  }
  kfree(bufk);
  return len;
 
}
 
static struct file_operations pugs_fops =
{
  .owner = THIS_MODULE,
  .open = tostring_open,
  .release = tostring_close,
  .read = tostring_read,
  .write = tostring_write
};
 
static int __init tostring_init(void) /* Constructor */
{
  printk(KERN_INFO "Tostring registered");
  tostring.pointer=0;
  tostring.tostring_read= tostring_read_hexa;
  if (alloc_chrdev_region(&first, 0, 1, "tostring") < 0)
  {
    return -1;
  }
  if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
  {
    unregister_chrdev_region(first, 1);
    return -1;
  }
  if (device_create(cl, NULL, first, NULL, "tostring") == NULL)
  {
    printk(KERN_INFO "Tostring error");
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
  cdev_init(&c_dev, &pugs_fops);
  if (cdev_add(&c_dev, first, 1) == -1)
  {
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
 
  printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
  return 0;
}
 
static void __exit tostring_exit(void) /* Destructor */
{
    unregister_chrdev_region(first, 3);
    printk(KERN_INFO "Tostring unregistered");
}
 
module_init(tostring_init);
module_exit(tostring_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("F.Boisson");
MODULE_DESCRIPTION("Module Tostring Integers Dec/Hex");
