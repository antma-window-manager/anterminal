SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror $(shell pkg-config --cflags vte-2.91)
LDFLAGS = $(shell pkg-config --libs vte-2.91)

BINNAME = anterminal

all: $(BINNAME)

$(BINNAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean: $(OBJS) $(BINNAME)
	rm $(OBJS) $(BINNAME)
