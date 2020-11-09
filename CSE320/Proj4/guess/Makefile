
proj= guess

objs = $(proj).o

CC=gcc
CFLAGS := $(CFLAGS) -Wall

.PHONY: all
all: $(proj)

$(proj): $(objs)
.PHONY: clean
clean:
	rm -f $(proj)
	rm -f *.o
