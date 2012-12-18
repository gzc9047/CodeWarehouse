obj-m := helloWorldLKM.o
KDIR  := /lib/modules/$(shell uname -r)/build
oPWD   := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
