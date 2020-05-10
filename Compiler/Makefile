FILENAME = Compiler
CPP = main.cpp
OUT = $(FILENAME)
INC = inc
OUT = output

all: clean build

build:
	@g++ -I$(INC) $(CPP)
	@./a.out
	@chmod +x $(OUT) 

clean:
	rm -f ./$(OUT)