		obj-m :=simple.o  
		KERNEL :=/usr/src/kernels/$(uname -r)/  
		PWD :=$(shell pwd)  
		modules :  
    		$(MAKE) -C $(KERNEL) M=$(PWD) modules  
		.PHONEY:clean  
		clean :  
    		rm -f *.o *.ko  