#makefile for hangman project ECE2524.
#
SHELL=/bin/bash

# Build hangman executable
hangman: main.o
	clang -o hangman main.o

main.o: main.c
	clang -c -o main.o main.c
