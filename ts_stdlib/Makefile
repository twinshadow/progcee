TOP=		$(realpath ${PWD})
SUBDIRS=	$(shell find src -maxdepth 1 -mindepth 1 -type d -exec basename \{\} \;)

CFLAGS+=	-I${PWD}/includes

all: ${SUBDIRS}

${SUBDIRS}:
	cd src/$@ && ${MAKE} CFLAGS="${CFLAGS}"

${SUBDIRS:=-check}:
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" check

${SUBDIRS:=-clean}:
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} clean

${SUBDIRS:=-install}:
	mkdir -p "${TOP}/obj"
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}" PREFIX="${TOP}/obj" install

all: ${SUBDIRS}
check: $(SUBDIRS:=-check)
clean: $(SUBDIRS:=-clean)
	rm -rf obj
install: $(SUBDIRS:=-install)

.PHONY: clean
