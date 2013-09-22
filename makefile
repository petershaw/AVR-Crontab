#######################################################################
######                That-Is-The-Box-Of-My-Wife                 ######
#######################################################################
###### Project:   AVR-Crontab
###### Developer: Peter Shaw
###### Date: 2013
###### URL: https://github.com/petershaw/AVR-Crontab
#######################################################################

PROJECTNAME = libavrcron


# Directory to generate objects
OBJECTDIR=./build
# directory to store the product
TARGETDIR=./target

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar
AVRDUDE = avrdude
REMOVE = rm -f
MKDIR_P = mkdir -p

# Name of target controller
MCU = atmega328p

# Frequency of the controller
F_CPU = 16000000UL

# id to use with programmer
# default: PROGRAMMER_MCU=$(MCU)
PROGRAMMER_MCU = m328p

# Programmer to use with avrdude
PROGRAMMER=usbasp

# port to use a bootloader
# This should be the port for your MCU.
BOOTLOADER_PORT = /dev/tty.SLAB_USBtoUART

# baud to use a bootloader
BOOTLOADER_BAUD = 9600

# C Source files
PRJSRC = $(shell find ./src* -name *.c)

# additional includes (e.g. -I/path/to/mydir)
INC = 

# libraries to link in (e.g. -lmylib)
LIBS = 


# Optimization level,
# use s (size opt), 1, 2, 3 or 0 (off)
OPTLEVEL = s

# HEXFORMAT -- format for .hex file output
HEXFORMAT = ihex

# compiler
CFLAGS = -I$(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL)  \
		-c \
         -DF_CPU=$(F_CPU)                          \
         -fpack-struct -fshort-enums               \
         -funsigned-bitfields -funsigned-char      \
         -Wall -Wstrict-prototypes                 \
         -Wa,-ahlms=$(OBJECTDIR)/$(firstword                    \
                    $(filter %.lst, $(<:.c=.lst)))

# linker
LDFLAGS = -Wl,-Map,$(TRG).map -mmcu=$(MCU)  \
          -L "$${LIBPATH}"                  \
          -lm $(LIBS)


##### automatic target names ####
TRG=$(TARGETDIR)/$(PROJECTNAME).out
DUMPTRG=$(TARGETDIR)/$(PROJECTNAME).s

# Start by splitting source files by type
#  C
CFILES=$(filter %.c, $(PRJSRC))

# List all object files we need to create
_OBJDEPS=$(CFILES:.c=.o)
OBJDEPS=$(_OBJDEPS:./src=$(OBJECTDIR)/src)

# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

# All the possible generated assembly
# files (.s files)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.s))

.SUFFIXES : .c .o .out .s .h .hex .ee.hex

dir_guard=$(MKDIR_P) $(OBJECTDIR)/$(@D)

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean
all: prepare test $(TRG) $(HEXTRG)

prepare:
	$(MKDIR_P) $(OBJECTDIR)
	$(MKDIR_P) $(TARGETDIR)

test:
	$(MAKE) -C tests

$(TRG): $(OBJDEPS)
	$(AR) rcs $(TARGETDIR)/$(PROJECTNAME).a $(filter-out x86_64, $(shell find $(OBJECTDIR) -type f -name *.o)) 
	$(MAKE) -f makefile_x86_64

#### Generating assembly ####
# asm from C
%.s: %.c
	$(dir_guard)
	$(CC) -S $(CFLAGS) $< -o $(OBJECTDIR)/$@

#### Generating object files ####
# object from C
.c.o:
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $(OBJECTDIR)/$@

#### Information ####
info:
	which $(CC)
	$(CC) -v
	avr-ld -v

#### Cleanup ####
clean:
	$(REMOVE) $(TRG) $(TRG).map $(DUMPTRG)
	$(REMOVE) -r $(TARGETDIR)
	$(REMOVE) $(OBJDEPS)
	$(REMOVE) $(LST)
	$(REMOVE) $(GENASMFILES)
	$(REMOVE) -r $(OBJECTDIR)
	$(MAKE) -C tests clean

