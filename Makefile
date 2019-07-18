CC=gcc
CFLAGS=-g -Wall
PKG1=`pkg-config --cflags gtk+-3.0` 
PKG2=`pkg-config --libs gtk+-3.0`
MATH=-lm


all: simpleCalc

simpleCalc: simpleCalc.c
	$(CC) $(CFLAGS) $(PKG1) $@.c -o $@ $(PKG2) $(MATH)

clean:
	rm simpleCalc