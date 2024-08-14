PREFIX := /usr/local

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror $(shell pkg-config --cflags vte-2.91)
LDFLAGS = $(shell pkg-config --libs vte-2.91)

BINNAME = anterminal

all: $(BINNAME)

$(BINNAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lconfig
	rm $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

install: $(BINNAME)
	mkdir -p $(PREFIX) $(PREFIX)/bin $(PREFIX)/share/applications
	install -Dvm755 ./$(BINNAME) $(PREFIX)/bin/$(BINNAME)
	install -Dvm755 ./$(BINNAME).desktop $(PREFIX)/share/applications/$(BINNAME).desktop

$(PREFIX)/bin/$(BINNAME): install

uninstall: $(PREFIX)/bin/$(BINNAME)
	rm $(PREFIX)/bin/$(BINNAME)
	rm $(PREFIX)/share/applications/$(BINNAME).desktop

clean: ./$(BINNAME)
	rm $(BINNAME)
