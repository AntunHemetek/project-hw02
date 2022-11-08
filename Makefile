SRC=$(wildcard src/*.c)
EXESRC=$(wildcard exesrc/*.c)
BIN=$(wildcard bin/*.bin)
OBJ=$(patsubst %.c, %.o, $(SRC))
EXEOBJ=$(patsubst %.c, %.o, $(EXESRC))
INC=inc/
EXE=$(patsubst exesrc/%.c, exe/%.elf, $(EXESRC))
#EXE=exe/test_dft.elf exe/test_idft.elf

CFLAGS=-I $(INC)

.SECONDARY:

all: $(EXE)

exe/%.elf: exesrc/%.o $(OBJ)
	gcc $(OBJ) $< -o $@ -lm
	
%.o: %.c
	gcc -c $< $(CFLAGS) -o $@
	
run: $(EXE)
	$(foreach elf, $(EXE), $(elf);)
	
clean:
	rm -f $(OBJ) $(EXE) $(EXEOBJ) $(BIN)
	
print:
	echo $(SRC)
	echo $(EXESRC)
	echo $(OBJ)
	echo $(BIN)
	echo $(INC)
	echo $(EXE)
