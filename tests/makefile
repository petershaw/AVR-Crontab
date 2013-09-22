
PROJECTNAME=libavrcron-tests

# list of all sources
PRJSRC = $(shell find ./src* -name *.c)
PRJSRC += $(filter %.c, $(shell grep -Ril "@Test-Compile" ../src))
PRJSRC += ./cu/cu.c

CFILES=$(filter %.c, $(PRJSRC))

TARGETDIR=./target
OBJECTDIR=./build

# binaries
CC = gcc
REMOVE=rm
MKDIR_P=mkdir -p

# additional includes (e.g. -I/path/to/mydir)
INC = ./cu

# libraries to link in (e.g. -lmylib)
LIBS =

CFLAGS = -I $(INC) \
	-g -Wall \
	-pedantic \
	--std=gnu99 \
	-DIGNOREINTESTS=1 \
	-Wgnu 
	
LDFLAGS = -I. $(INC) -DIGNOREINTESTS=1 -L "$${LIBPATH}" -lm $(LIBS)

TRG=$(TARGETDIR)/$(PROJECTNAME)

# List all object files we need to create
_OBJDEPS=$(CFILES:.c=.o)
OBJDEPS=$(_OBJDEPS:./src=$(OBJECTDIR)/src)

# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

.SUFFIXES : .c .o .out .s .h

dir_guard=$(MKDIR_P) $(OBJECTDIR)/$(subst ../,,$(@D))

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean

all: prepare $(TRG)

showsource: 
	# $(PRJSRC);

prepare:
	$(MKDIR_P) $(OBJECTDIR)
	$(MKDIR_P) $(TARGETDIR)
	$(MKDIR_P) regressions
	@echo -- $(OBJDEPS)

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(shell find $(OBJECTDIR) -type f -name *.o)

#### Generating object files ####
# object from C
.c.o:
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $(OBJECTDIR)/$(subst ../,,$@)
	
clean:
	$(REMOVE) -f $(TRG)
	$(REMOVE) -rf $(TARGETDIR)
	$(REMOVE) -f $(OBJDEPS)
	$(REMOVE) -f $(LST)
	$(REMOVE) -rf $(OBJECTDIR)
	$(REMOVE) -rf regressions
	