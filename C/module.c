#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>


#define BUFFER_SIZE 128
#define PROC_NAME "module" 

int simple_init(void)
{
	int now_tick_freq = HZ;
	
	
	printk(KERN_INFO "Loading Kernel module\n");
	
	printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
	printk(KERN_INFO "Value of jiffies is %lu\n", now_tick);
	printk(KERN_INFO "Value of HZ is %d\n", now_tick_freq);
	return 0;
}


void simple_exit(void)
{
	
	unsigned long int a = 00;

	unsigned int b = 24;
	
	unsigned long now_tick = jiffies;
	
	printk(KERN_INFO "The CGD of %lu and %u is %lu\n", a, b, gcd(a,b));

	printk(KERN_INFO "Value of jiffies is %lu\n", now_tick);
	
	printk(KERN_INFO "Removing Kernel Module\n");
}


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("J");

