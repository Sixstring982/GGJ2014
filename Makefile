CC := gcc
CFLAGS := -g -Wall -pedantic -ansi -Werror -std=c89
ALLDEPS := 
SRCDIR := src
BUILDDIR := build

SRCEXT := c
HDRPAT := -name *.h
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
HEADERS := $(shell find $(SRCDIR) -type f $(HDRPAT))
ALLDEP += $(HEADERS)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB := -lm
INC := -I include

all: $(OBJECTS)
	@echo "$(CC) $(CFLAGS) $(INC) -o build/sub $(OBJECTS)"; $(CC) $(CFLAGS) $(INC) -o build/sub $(OBJECTS)

$(BUILDDIR)/%.o:	$(SRCDIR)/%.$(SRCEXT) $(ALLDEP)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm build/*.o