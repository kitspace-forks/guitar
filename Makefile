CC=gcc
CFLAGS=-c -Wall `pkg-config --cflags jack`
LDFLAGS=`pkg-config --libs jack`
SOURCES=main.c jack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=guitarseq

all: $(SOURCES) $(EXECUTABLE)

run:
	./$(EXECUTABLE)
runx:
	./emulated/emulated|./$(EXECUTABLE)

clean:
	rm -f ${EXECUTABLE} ${OBJECTS}

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@