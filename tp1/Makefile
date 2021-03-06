# DIRECTORIES
BINDIR = bin/
SRCDIR = src/
SAVEDIR = save/
DOCDIR = doc/
LIBDIR = lib/

# COMPILATION TOOLS
CC = gcc
FLAGS = -Wall -lm
CLEAN = clean

# ALL FILES
PROG = $(BINDIR)tp1
SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.c=.o))
HEAD = $(wildcard $(LIBDIR)*.h)
MF = Makefile
DOXYFILE = Doxyfile
README = README.md
ARC = monchecour-tp1.tgz

#COMMANDS
RM = rm -r
TGZ = tar -czvf
CP = cp
DOXYGEN = doxygen
MKDIR = mkdir -p
MAKE = make

# COMPILATION
all: $(PROG)
	$(MAKE) $(CLEAN)
$(PROG) : $(OBJ) $(HEAD)
	$(CC) $^ -o $(PROG)
	$(DOXYGEN) $(DOXYFILE)

$(BINDIR)%.o: $(SRCDIR)%.c
	$(MAKE) pre_build
	$(CC) -c $(FLAGS) $^ -o $@

# SAVE CURRENT VERSION
save: $(SRC) $(HEAD)
	$(CP) $^ $(SAVEDIR)

# RESTORE VERSION
restore:
	cp $(SAVEDIR)* $(SRCDIR)

# PACK SOURCES
package: $(BINDIR) $(SRCDIR) $(DOCDIR) $(MF) $(DOXYFILE) $(README)
	$(RM) $(PROG) $(OBJ) $(DOCDIR)*
	$(TGZ) $(ARC) $^

#BUILD ARCHITECTURE
arch:
	mkdir $(BINDIR) $(SRCDIR) $(DOCDIR) $(SAVEDIR)
	touch $(README)

pre_build:
		$(MKDIR) $(BINDIR)

.PHONY: clean
clean:
	$(RM) $(OBJ)