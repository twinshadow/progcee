
OBJECTS=charbuf.o

ifndef KPVER
KPVER := $(shell uname -r)
endif

obj-m+= ${OBJECTS}

all:
	make -C /lib/modules/${KPVER}/build M=${PWD} modules
clean:
	make -C /lib/modules/${KPVER}/build M=${PWD} clean

