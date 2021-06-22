obj-m +=custom.o
include $(PWD)/ko/Makefile
custom-y := $(OBJS_CUSTOM)

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean