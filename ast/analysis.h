#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "ast.h"

void analyze_ast(ast_t *);
int get_ast_char(ast_t *, char **);

#endif
