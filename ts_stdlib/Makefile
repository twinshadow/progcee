DEBUG ?= NO

ifeq (${DEBUG}, NO)
DEBUG=		-g
OPTIMIZATION=	-O0
else
DEBUG=
OPTIMIZATION=	-Os
endif

CFLAGS= ${OPTIMIZATION} ${DEBUG} -I${PWD}/includes

SUBDIRS=	$(shell find src -maxdepth 1 -mindepth 1 -type d -exec basename \{\} \;)

${SUBDIRS}:
	cd src/$@ && ${MAKE} CFLAGS="${CFLAGS}"

clean:
	for dir in $(SUBDIRS); do 		\
		cd src/$$dir && ${MAKE} clean; 	\
		cd - ; \
	done;
