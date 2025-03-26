# Variables
CC = clang
CFLAGS = 
LDFLAGS = -lpari
INCLUDES = -I.
SOURCES1 = utilities.c group.c proofProtocol.c main1.c
SOURCES2 = utilities.c group.c proofProtocol.c elliptic.c main2.c
HEADERS1 = utilities.h group.h proofProtocol.h
HEADERS2 = utilities.h group.h proofProtocol.h elliptic.h
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
EXECUTABLE1 = main1
EXECUTABLE2 = main2

# Règles
all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECUTABLE2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main1.o: main1.c $(HEADERS1)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

main2.o: main2.c $(HEADERS2)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS1) $(OBJECTS2) $(EXECUTABLE1) $(EXECUTABLE2)

.PHONY: all clean