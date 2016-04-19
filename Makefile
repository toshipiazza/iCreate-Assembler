CFLAGS  ?= -Wall -Werror -g -D_DEBUG -std=gnu89
LDFLAGS := -pthread

SOURCES := iCreate.c ast/ast.c parser/assembler.tab.c parser/lex.yy.c parser/attributes.c
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

all: iCreate
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
iCreate: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
clean:
	rm $(OBJECTS)

.PHONY: clean
