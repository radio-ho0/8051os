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
	$(CC) $(FLAGS) $(SRC)/$(FILENAME).c $(OUTPUT)/lcd.rel $(OUTPUT)/core.rel  -o $(OUTPUT)/$(FILENAME).ihx
	$(MAKEHEX) $(OUTPUT)/$(FILENAME).ihx >./$(OUTPUT)/$(FILENAME).hex

rel:
	$(CC) $(FLAGS) $(SRC)/lcd.c -c -o $(OUTPUT)/lcd.rel
	$(CC) $(FLAGS) $(SRC)/core.c -c -o $(OUTPUT)/core.rel
	
.PHONY: clean

clean:
	-rm  $(OUTPUT)/*.hex 
	-rm  $(OUTPUT)/*.rel
	

fire:
	stcflash $(OUTPUT)/$(FILENAME).bin  ###
	# I hate sudo
	#sudo stcflash timer.bin  ###
