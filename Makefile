CFLAGS += -Wall -Werror

all: bound caps

bound: bound.o list.o

caps: caps.o list.o

list.c: gen.sh
	./gen.sh >$@

clean:
	rm -f *.o bound caps
