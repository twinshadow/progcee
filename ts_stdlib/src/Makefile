SRCS=		$(wildcard [!(check_)]*.c)
CHECK_SRCS=	$(wildcard check_*.c)
OBJS=		$(SRCS:.c=.o)
CHECK_OBJS=	$(CHECK_SRCS:.c=.co)

ifdef (${DEBUG})
CFLAGS+=	-g -O0
endif

ifndef (${TOP})
CFLAGS+=	-I../../includes
endif

%.a: %.o
	ar -cvq $@ $^

%.so: %.o
	${CC} ${CFLAGS} ${LDFLAGS} -shared -o $@ $^

%.co : %.c
	${CC} -lcheck ${CFLAGS} -o $@ $^ ${OBJS}

all: ${OBJS}

check-build: ${OBJS} ${CHECK_OBJS}

check-run: check-build
	@for CHK in ${CHECK_OBJS}; do	\
		$$CHK;			\
	done

check: check-run

clean:
	rm -f ${OBJS} ${CHECK_OBJS}

.PHONY: clean check
