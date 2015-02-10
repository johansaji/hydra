
LIB_NAME = libhydra.so

CFLAGS += -Wall -fno-common

LIB_NAME:
	gcc -c src/hydra.c $(CFLAGS) -I./include 
