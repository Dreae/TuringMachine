CFLAGS=-g -Wall
SOURCES=ruleset.c turing.c tape.c main.c
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) turing

turing: $(OBJECTS)

clean:
	rm *.o turing
