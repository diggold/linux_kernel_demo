TARGET= test_lkm
obj-m   := ${TARGET}.o
${TARGET}-objs := lkm.o zeroevil.o
 
KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)
 
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f *.o *.ko
