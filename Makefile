CC = $(CROSS_COMPILE)gcc
CFLAGS = -g -Wall -Wextra -Werror
SRCDIR = src
TESTDIR = test
SOURCES = $(shell ls $(SRCDIR)/*.c)
TESTS = $(shell ls $(TESTDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o) $(TESTS:.c=.o)

.PHONY: all
all:	sexpr

$(SRCDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $<

sexpr: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.PHONE: clean
clean:
	rm -f $(SRCDIR)/*.o $(TESTDIR)/*.o sexpr
