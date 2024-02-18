# This is a makefile that can be used to build the two program on Unix.
# The Unix make utility looks for a file named "makefile" by default.
#
# If you type "make" at the Unix prompt in the same directory as this
# file, the make utility will build the default rule. The default rule
# in turn tries to build the Savings and Invest rules. These two rules
# compile the executables for Savings and Invest.
#
# We'll learn more about makefiles towards the end of the course.

# Defines compiler we'll be using
CC=gcc

# Standard compilation flags we use in CS1142
# -g         Add debug symbols, useful for using some debugging tools
# -std=c99   Compile against C99 standard
# -pedantic  Strict adherence to the standard
# -Wall      Turn on all the warning messages
# -Wextra    Turn on even more warning messages
# -O1        Level 1 performance optimization

CFLAGS=-g -std=c99 -pedantic -Wall -Wextra -O1

# Linker flags. While you probably don't need any special math functions
# for this assignment, but we always link this library just in case.
LDFLAGS=-lm

default: Savings Invest

Savings: Savings.c
	${CC} ${CFLAGS} -o Savings Savings.c ${LDFLAGS}

Invest: Invest.c
	${CC} ${CFLAGS} -o Invest Invest.c ${LDFLAGS}

# Typing "make clean" will remove any compiled executables.
clean:
	rm Savings Invest
