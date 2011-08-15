CFLAGS += -Wall -Werror

all: bound inherit caps

bound: bound.o list.o

inherit: inherit.o list.o

caps: caps.o list.o

list.c: gen.sh
	./gen.sh >$@

clean:
	rm -f *.o bound caps
