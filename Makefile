CFLAGS += -Wall -Werror
TARG=\
	caps\
	bound\
	inherit\
	uninherit\

all: $(TARG)

$(TARG): list.o

list.c: gen.sh
	./gen.sh >$@

clean:
	rm -f *.o list.c $(TARG)
