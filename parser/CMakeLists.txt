add_library(parser assembler.tab.c assembler.tab.h lex.yy.c)
target_link_libraries(parser ast)
