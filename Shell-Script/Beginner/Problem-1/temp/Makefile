CC := gcc

INC := -I include

DFLAGS := -g -DDEBUG
CFLAGS := $(INC) -DCOLOR 


.PHONY: clean all setup

all: setup
	$(CC) $(CFLAGS) -o icssh -lreadline
	
debug: setup
	$(CC) $(DFLAGS) $(CFLAGS)  -o icssh -lreadline
	

