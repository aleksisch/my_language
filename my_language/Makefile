FILENAME = Assembler
CPP = main.cpp
OUT = $(FILENAME)
INC = inc
RESULT = output.asm
INPUT = example/fyb.txt


all: build run clean

debug: build

build:
	@g++ -I$(INC) $(CPP) -o $(OUT)

run:
	@./$(OUT) $(INPUT) $(RESULT)

clean:
	@rm -f tmp*