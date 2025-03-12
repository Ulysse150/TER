# Variables
CC = clang
CFLAGS = 
LDFLAGS = -lpari
INCLUDES = -I.
SOURCES =  utilities.c group.c proofProtocol.c com.c
HEADERS = utilities.h group.h proofProtocol.h
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = my_program

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean