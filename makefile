CC=gcc
LDFLAGS=-framework CoreFoundation -framework IOKit

SRCDIR=src
BINDIR=bin

SRC=$(SRCDIR)/iMoan.c
TARGET=$(BINDIR)/iMoan

all:
	$(CC) $(LDFLAGS) $(SRC) -o $(TARGET)

clean:
	$(RM) *.o
	$(RM) .$(BIN)/$(TARGET)

.PHONY: clean
