OBJ_NAME=	$(shell basename "${PWD}")

SRCS=		$(wildcard [!(check_)]*.c)
CHECK_SRCS=	$(wildcard check_*.c)
OBJS=		$(SRCS:.c=.o)
CHECK_OBJS=	$(CHECK_SRCS:.c=.co)

ifdef DEBUG
CFLAGS+=	-O0
endif

ifndef TOP
TOP=		../..
CFLAGS+=	-I${TOP}/includes -g
PREFIX=		${TOP}/obj
endif

${OBJ_NAME}.a : ${OBJS}
	ar -cvq $@ $^

${OBJ_NAME}.so: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -shared -o $@ $^

%.co : %.c
	${CC} -lcheck ${CFLAGS} -o $@ $^ ${OBJS}

all: ${OBJS}

check-build: ${OBJS} ${CHECK_OBJS}

check-run: check-build
	@set ERROR_CHECK=0;			\
	for CHK in ${CHECK_OBJS}; do		\
		valgrind --suppressions=${TOP}/ts_valgrind.supp --quiet $$CHK;\
		if [ "$$?" -ne 0 ]; then	\
			set ERROR_CHECK=1;	\
		fi;				\
	done;					\
	exit $$ERROR_CHECK

check: check-run

analyze:
	clang --analyze ${CFLAGS} ${SRCS}

install: ${OBJ_NAME}.a
	mkdir -p ${PREFIX}/lib
	install ${OBJ_NAME}.a ${PREFIX}/lib/${OBJ_NAME}.a

clean:
	rm -f *.o *.co ${OBJ_NAME}.a ${OBJ_NAME}.so

.PHONY: clean check install
