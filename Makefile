SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Include flags for GTK+ 3 and VTE
CFLAGS = -Wall -Werror $(shell pkg-config --cflags vte-2.91) -I/opt/homebrew/include
LDFLAGS = $(shell pkg-config --libs vte-2.91) -L/opt/homebrew/lib -lconfig

BINNAME = anterminal

all: $(BINNAME)

$(BINNAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lconfig
	rm $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(BINNAME) $(OBJS)

