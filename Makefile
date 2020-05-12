ASM_DIR = my_language
COMPILER_DIR = compiler
TRANSLATOR_DIR = translator

FILENAME = Assembler

INPUT = square_eq.txt
ASM_FILE = output.asm
BINARY_FILE = result.bin
ELF_FILE = program.elf
FLAG = all


all: make_asm compile make_elf run

make_asm:
	@make $(FLAG) -C $(ASM_DIR) INPUT=../$(INPUT) RESULT=../$(ASM_FILE)

compile:
	@make $(FLAG) -C $(COMPILER_DIR) INPUT=../$(ASM_FILE) RESULT=../$(BINARY_FILE)

make_elf:
	@make $(FLAG) -C $(TRANSLATOR_DIR) INPUT=../$(BINARY_FILE) RESULT=../$(ELF_FILE)

run:
	@./$(ELF_FILE)

clean:
	@rm -f $(BINARY_FILE)
	@rm -f $(ELF_FILE)
	@rm -f $(ASM_FILE)
