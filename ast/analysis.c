#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "analysis.h"
#include "ast.h"

typedef struct {
  char *data;
  size_t len;
} bin_string_t;

void
bin_string_concat(bin_string_t *bstring, char *data, int len)
{
  bstring->data = (char *) realloc(bstring->data, len + bstring->len + 1);
  memcpy(bstring->data + bstring->len, data, len);
  bstring->len += len;
  bstring->data[bstring->len] = '\0';
  free(data);
}

bin_string_t *
bin_string_init(void)
{
  bin_string_t *ret = (bin_string_t *) malloc(sizeof(bin_string_t));
  ret->data = (char *) malloc(sizeof(char));
  ret->data[0] = '\0';
  ret->len = 0;
  return ret;
}

void
bin_string_free(bin_string_t *bstring)
{
  free(bstring->data);
  free(bstring);
}

int
analyze_ast_recursive(ast_t *ast, bin_string_t *bstring)
{
  if (ast) {
    int length;
    char *res = handle_args[ast->payload.opcode](ast, &length);
    /* check error condition */
    if (res == NULL)
      return 0;

    /* concat */
    bin_string_concat(bstring, res, length);
    return analyze_ast_recursive(ast->next_instruction, bstring);
  }
  return 1;
}

void
analyze_ast(ast_t *ast)
{
  bin_string_t *data = bin_string_init();
  if (analyze_ast_recursive(ast, data)) {
    for (int i = 0; i < data->len; ++i) {
      printf("%u ", (unsigned char) data->data[i]);
    }
    printf("\n");
  }
  bin_string_free(data);
}

int
get_ast_char(ast_t *ast, char **in)
{
  bin_string_t *data = bin_string_init();
  *in = NULL;
  if (analyze_ast_recursive(ast, data)) {
    *in = data->data;
  }
  int len = data->len;
  free(data);
  return len;
}
