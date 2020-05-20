
FILENAME = Compiler
CPP = main.cpp
OUT = $(FILENAME)
INC = inc
RESULT = res.bin
INPUT = asm.txt
CFLAGS = -I$(INC)


all: build run clean

debug: build 
	./$(OUT) $(INPUT) $(RESULT) debug

build:
	g++ $(CFLAGS) $(CPP) -o $(OUT)

run: build
	./$(OUT) $(INPUT) $(RESULT)


clean:
	@rm -f disassembler.txt
	@rm -f tmp*