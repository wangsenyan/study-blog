#目标文件
obj-m := birthday.o  
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

all:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		@rm -rf *.mod.*
clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean