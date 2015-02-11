
LIB_NAME = libhydra.so

CFLAGS += -Wall -fno-common


LIB_NAME:
	gcc -c src/hydra.c $(CFLAGS) -I./include 

test_app: 
	gcc test/main.c src/hydra.c  $(CFLAGS) -I./include -pthread
