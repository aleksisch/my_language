FILENAME = translator
CPP = main.cpp
OUT = $(FILENAME)
INC = inc
INPUT = assembler.bin
RESULT = output
CFLAGS = -I$(INC)

all: build run

build:
	@g++ $(CFLAGS) $(CPP) -o $(OUT)

run: 
	@./$(OUT) $(INPUT) $(RESULT)
	@chmod +x $(RESULT) 