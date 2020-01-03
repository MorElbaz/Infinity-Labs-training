CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra

C_SOURCES = $(filter-out $(wildcard *test*), $(wildcard *.c))
TESTS_C = $(wildcard *test.c)
TESTS_DBG_C = $(wildcard *test_d.c)
TESTS_OUT = ${TESTS_C:.c=.out}
TESTS_DBG_OUT = $(TESTS_DBG_C:.c=.out)
OBJS_DBG = ${C_SOURCES:.c=_gdb.o}
OBJS = ${C_SOURCES:.c=.o}

-include depends 

all: libutils.so libutils.gdb.so test
libs: libutils.so
test: ${TESTS_OUT} ${TESTS_DBG_OUT}

%.o: %.c
	${CC} ${CFLAGS} -fpic -c $(filter %.c ,$<)

libutils.so: $(OBJS)
	${CC} -shared $(OBJS) -o $@ -lm


%_gdb.o: CFLAGS += -g
%_gdb.o: %.c
	${CC} ${CFLAGS} -fpic -c $(filter %.c ,$<) -o $@

libutils.gdb.so: ${OBJS_DBG}
	${CC} -shared $(OBJS_DBG) -o $@ -lm


%_test.out: %_test.c libutils.so
	${CC} ${CFLAGS} $< libutils.so -lm -o $@


%_test_d.out: CFLAGS += -g
%_test_d.out: %_test_d.c libutils.gdb.so
	${CC} ${CFLAGS} $< libutils.gdb.so -lm -o $@


.PHONY: depends clean
depends: 
	${CC} -MM ${C_SOURCES} > depends

clean:
	rm $(wildcard *.gch) $(wildcard ~*) *.o *.so *.out
 
