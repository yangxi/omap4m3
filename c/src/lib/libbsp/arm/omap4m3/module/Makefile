# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
default: rproc

ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabi-
KERNELDIR ?= /lib/modules/3.4.0-rc1+/build
PWD = `pwd`

ifeq ($(KERNELRELEASE),)

.PHONY: clean.
clean:
	rm -rf *.o *.~ *.ko *.mod.c

rproc:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

else
	obj-m:= rproc.o
endif
