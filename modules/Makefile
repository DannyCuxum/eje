#obj-m += ram.o
obj-m += cpu_201807428.o
obj-m += ram_201807428.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean