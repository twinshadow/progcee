TOP=		$(realpath ${PWD})
SUBDIRS=	$(shell find src -maxdepth 1 -mindepth 1 -type d -exec basename \{\} \;)

CFLAGS+=	-I${PWD}/includes -g -fPIC -Wall -Werror

all: ${SUBDIRS}

${SUBDIRS}:
	cd src/$@ && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}"

${SUBDIRS:=-check}:
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}" check

${SUBDIRS:=-analyze}:
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}" analyze

${SUBDIRS:=-clean}:
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} clean

${SUBDIRS:=-install}:
	mkdir -p "${TOP}/obj"
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}" PREFIX="${TOP}/obj" install

all: ${SUBDIRS}
check: $(SUBDIRS:=-check)
analyze: $(SUBDIRS:=-analyze)
clean: $(SUBDIRS:=-clean)
	rm -rf obj
install: $(SUBDIRS:=-install)
	mkdir obj/include
	cp -r includes/twinshadow obj/include

everything: clean analyze check all install

.PHONY: clean
