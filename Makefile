CC=gcc
CFLAGS=-c -std=c99 `pkg-config --cflags jack`
LDFLAGS=`pkg-config --libs jack`
SOURCES=main.c jack.c args.c notes.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=guitarseq

all: $(SOURCES) $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

clean:
	rm -f ${EXECUTABLE} ${OBJECTS}

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


#cool stuff:
runx: all
	./emulated/emulated|./$(EXECUTABLE) -o