TARGET=cc
SRC=main.c vector.c utility.c map.c lex.c parse.c x86_64_gen.c type.c env.c ast.c analyze.c string_builder.c cpp.c token.c stdlib.c SIMPLE_gen.c
SRC_ASM=system.s
CC=gcc
FLAGS=-O0 -g3 -Wall -std=c11 -fno-builtin  -fno-stack-protector -static -nostdlib

$(TARGET): $(SRC) $(SRC_ASM) test.inc cc.h
	$(CC) -o $@ $(SRC) $(SRC_ASM) $(FLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean
