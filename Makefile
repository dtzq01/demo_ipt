obj-m +=demo.o
include $(PWD)/ko/Makefile
demo-y := $(OBJS_DEMO)

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules -I"$(PWD)/ko"
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean