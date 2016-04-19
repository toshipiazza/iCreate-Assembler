CFLAGS  ?= -Wall -g -D_DEBUG -std=gnu99 -m32

SOURCES := iCreate.c ast/ast.c ast/analysis.c parser/assembler.tab.c parser/lex.yy.c
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

all: iCreate
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
iCreate: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm $(OBJECTS)

.PHONY: clean
