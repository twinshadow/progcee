TOP=		$(realpath ${PWD})
SUBDIRS=	$(shell find src -maxdepth 1 -mindepth 1 -type d -exec basename \{\} \;)
PREFIX=		${TOP}/pkg

INCLUDES=	-I${PWD}/includes

CFLAGS+=	-g -fPIC -Wall -Werror ${INCLUDES}

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
	cd src/$(shell echo $@ | cut -d'-' -f1) && ${MAKE} CFLAGS="${CFLAGS}" TOP="${TOP}" PREFIX="${PREFIX}" install

all: ${SUBDIRS}
check: $(SUBDIRS:=-check)
analyze: $(SUBDIRS:=-analyze)
clean: $(SUBDIRS:=-clean)
	rm -rf obj
install: $(SUBDIRS:=-install)
	mkdir -p ${PREFIX}/include
	mkdir -p ${PREFIX}/lib
	cp -r includes/twinshadow ${PREFIX}/include
	ar -cvq ${PREFIX}/lib/twinshadow.a $(shell find src -name '*.o')
	${CC} ${CFLAGS} ${LDFLAGS} -shared -o ${PREFIX}/lib/twinshdow.so $(shell find src -name '*.o')
docs:
	cldoc ${CFLAGS} -- \
		--language=c --report \
		--merge=${TOP}/docs/_static \
		--output=${TOP}/docs \
		$(shell find \( -name '*.c' -or -name '*.h' \) -not -name 'check_*')

everything: clean analyze check all docs install

.PHONY: clean docs
