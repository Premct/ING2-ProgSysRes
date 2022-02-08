# DIRECTORIES
BINDIR = bin/
SRCDIR = src/
SAVEDIR = save/
DOCDIR = doc/
LIBDIR = lib/

# COMPILATION TOOLS
CC = gcc
FLAGS = -Wall -lm

# ALL FILES
PROG = $(BINDIR)minishell
SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.c=.o))
HEAD = $(wildcard $(LIBDIR)*.h)
MF = Makefile
DOXYFILE = Doxyfile
README = README.md
ARC = monchecour-ex9.tgz

#COMMANDS
RM = rm -r
TGZ = tar -czvf
CP = cp -r
DOXYGEN = doxygen
MKDIR = mkdir -p
TOUCH = touch

# COMPILATION
all: $(PROG)
$(PROG) : $(OBJ) $(HEAD)
	$(CC) $^ -o $(PROG)
	$(DOXYGEN) $(DOXYFILE)

$(BINDIR)%.o: $(SRCDIR)%.c
	make pre_build
	$(CC) -c $(FLAGS) $^ -o $@

# SAVE CURRENT VERSION
save: $(SRC) $(HEAD)
	$(MKDIR) $(SAVEDIR)
	$(CP) $^ $(SAVEDIR)

# RESTORE VERSION
restore:
	cp $(SAVEDIR)* $(SRCDIR)

# PACK SOURCES
package: $(SRCDIR) $(LIBDIR) $(MF) $(DOXYFILE) $(README)
	$(RM) $(PROG) $(OBJ) $(DOCDIR)*
	$(TGZ) $(ARC) $^

pre_build:
	$(MKDIR) $(BINDIR)

#BUILD ARCHITECTURE
build_arch:
	$(MKDIR) $(SRCDIR) $(LIBDIR)
	$(TOUCH) $(README)


.PHONY: clean
clean:
	$(RM) $(OBJ)