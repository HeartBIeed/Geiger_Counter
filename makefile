MCU     = atmega16
F_CPU   = 8000000UL
TARGET  = main
OUTPUT = build/
CC      = avr-gcc
OBJCOPY = avr-objcopy


SRC     = $(wildcard *.c)
HEADERS = $(wildcard inc/*.h)
OBJ     = $(SRC:.c=.o)

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Iinc

all: $(OUTPUT)$(TARGET).hex

$(OUTPUT)%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)$(TARGET).elf: $(OUTPUT)$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTPUT)$(TARGET).hex: $(OUTPUT)$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

