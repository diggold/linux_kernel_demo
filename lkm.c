/*lkm.c*/
 
#include <linux/module.h>    
#include <linux/kernel.h>   
#include <linux/init.h>
#include <linux/syscalls.h>

#include "zeroevil.h"

MODULE_LICENSE("GPL");

unsigned long ** sct;


asmlinkage long
(*real_unlink)(const char __user *pathname);

asmlinkage long 
fake_unlink(const char __user * pathname)
{
	printk("lkm unlink: %s\n", pathname);
	return real_unlink(pathname);
}
 
static int lkm_init(void)
{
    printk("Arciryas:module loaded\n");
	//list_del_init(&__this_module.list);
	//kobject_del(&THIS_MODULE->mkobj.kobj);
	//
	
	
	sct = get_sct();
	printk("sct : %lx\n", sct );
	//if(sct == NULL){
	//	printk("error sct.\n");
	//	return -1;	
	//}

	disable_wp();

	real_unlink = (void *)sct[__NR_unlink];
	sct[__NR_unlink] = (void *) fake_unlink;

//	HOOK_SCT(sct, unlink);
	enable_wp();


    return 0;    
}
 
static void lkm_exit(void)
{
    printk("Arciryas:module removed\n");
	disable_wp();
	
	sct[__NR_unlink] = (void *)real_unlink;

//	UNHOOK_SCT(sct, unlink);
	enable_wp();
}
 
module_init(lkm_init);
module_exit(lkm_exit);


