#目标文件

obj-m := line_p.o  
obj-m := dfs_p.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

all:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		@rm -rf *.mod.*
clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
