CC = sdcc
FLAGS = -mmcs51 --model-small --std-c99
FILENAME = main
SRC = src
OUTPUT = output

MAKEHEX = packihx

all: bin

bin: hex
	hex2bin $(OUTPUT)/$(FILENAME).hex

hex: rel
#	$(CC) $(FLAGS) $(SRC)/$(FILENAME).c -o $(OUTPUT)/$(FILENAME).ihx
	$(CC) $(FLAGS) $(SRC)/$(FILENAME).c $(OUTPUT)/lcd1602.rel $(OUTPUT)/distancer.rel $(OUTPUT)/core.rel -o $(OUTPUT)/$(FILENAME).ihx
	$(MAKEHEX) $(OUTPUT)/$(FILENAME).ihx >./$(OUTPUT)/$(FILENAME).hex

rel:
	$(CC) $(FLAGS) $(SRC)/core.c -c -o $(OUTPUT)/core.rel
	$(CC) $(FLAGS) $(SRC)/lcd1602.c -c -o $(OUTPUT)/lcd1602.rel
	$(CC) $(FLAGS) $(SRC)/distancer.c -c -o $(OUTPUT)/distancer.rel
	
.PHONY: clean

clean:
	-rm  $(OUTPUT)/*.hex 
	-rm  $(OUTPUT)/*.asm
	-rm  $(OUTPUT)/*.rel

	

fire:
	stcflash $(OUTPUT)/$(FILENAME).bin  ###
	# I hate sudo
	#sudo stcflash timer.bin  ###
