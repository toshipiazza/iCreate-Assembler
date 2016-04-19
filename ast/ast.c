#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "analysis.h"

const handle_args_t handle_args[159] = {
  [128] = start_handle_args,
  [129] = baud_handle_args,
  [130] = control_handle_args,
  [131] = safe_handle_args,
  [132] = full_handle_args,
  [134] = spot_handle_args,
  [135] = cover_handle_args,
  [136] = demo_handle_args,
  [137] = drive_handle_args,
  [138] = lsd_handle_args,
  [138] = led_handle_args,
  [140] = song_handle_args,
  [141] = play_handle_args,
  [142] = sensors_handle_args,
  [143] = cad_handle_args,
  [144] = plsd_handle_args,
  [145] = drivedir_handle_args,
  [147] = digout_handle_args,
  [148] = stream_handle_args,
  [149] = qlist_handle_args,
  [150] = togglestrm_handle_args,
  [151] = sendir_handle_args,
  [152] = script_handle_args,
  [153] = playscript_handle_args,
  [154] = showscript_handle_args,
  [155] = waittime_handle_args,
  [156] = waitdist_handle_args,
  [157] = waitangle_handle_args,
  [158] = waitevent_handle_args
};

void
ast_free(ast_t *ast)
{
  /* deep recursion! */
  if (ast) {
    ast_free(ast->next_instruction);
    ast_free(ast->arguments);
    free(ast);
  }
}

ast_t *
ast_set_next(ast_t *a, ast_t *next)
{
  a->next_instruction = next;
  return a;
}

ast_t *
create_op_node(char opcode, int num_args, ...)
{
  va_list ap;
  ast_t **arg;

  ast_t *node = (ast_t *) malloc(sizeof(ast_t));
  node->is_operation = 1;
  node->payload.opcode = opcode;
  node->next_instruction = NULL;

  if (num_args > 0) {
    /* insert args */
    va_start(ap, num_args);
    arg = &node->arguments;
    for (int i = 0; i < num_args; ++i) {
      *arg = va_arg(ap, ast_t *);
      arg = &(*arg)->arguments;
    }
    va_end(ap);
  } else {
    node->arguments = NULL;
  }

  return node;
}

ast_t *
create_arg_node_2byte(int value, ast_t *next)
{
  ast_t *node = (ast_t *) malloc(sizeof(ast_t));
  node->is_operation = 0;
  node->payload.value2b = value;
  node->arguments = next;
  node->next_instruction = NULL;
  return node;
}

ast_t *
create_arg_node_1byte(int value, ast_t * next)
{
  ast_t *node = (ast_t *) malloc(sizeof(ast_t));
  node->is_operation = 0;
  node->payload.value1b = value;
  node->arguments = next;
  node->next_instruction = NULL;
  return node;
}

static int
num_args(ast_t *a, int i)
{
  if (a == NULL)
    return i;
  else return num_args(a->arguments, i+1);
}

static char *
handle_zero_args(char *instr, ast_t *a, int *length)
{
  assert(a->is_operation);

  int args;
  if ((args = num_args(a->arguments, 0)) != 0) {
    fprintf(stderr, "ERROR: num_arguments\n");
    fprintf(stderr, "\"%s\" expected 0 arguments, got %d\n", instr, args);
    return NULL;
  }
  *length = 1;
  char *ret = (char *) malloc(sizeof(char) * 2);
  ret[0] = a->payload.opcode;
  ret[1] = '\0';
  return ret;
}

static char *
handle_one_byte_args(char *instr, ast_t *a, int expected_args, int *length)
{
  assert(a->is_operation);
  int args;
  if ((args = num_args(a->arguments, 0)) != expected_args) {
    fprintf(stderr, "ERROR: num_arguments\n");
    fprintf(stderr, "\"%s\" expected %d arguments, got %d\n", instr, expected_args, args);
    return NULL;
  }

  *length = (expected_args + 1);
  /* +1 for opcode, +1 for null byte */
  char *ret = (char *) malloc(sizeof(char) * (expected_args + 2));
  ret[0] = a->payload.opcode;
  ret[expected_args + 1] = '\0';

  char *tmp = ret + 1;
  ast_t *arg = a->arguments;
  while (arg != NULL) {
    *tmp = arg->payload.value1b;
    arg = arg->arguments;
    tmp++;
  }

  return ret;
}

static char *
handle_two_byte_args(char *instr, ast_t *a, int expected_args, int *length)
{
  assert(a->is_operation);
  int args;
  if ((args = num_args(a->arguments, 0)) != expected_args) {
    fprintf(stderr, "ERROR: num_arguments\n");
    fprintf(stderr, "\"%s\" expected %d arguments, got %d\n", instr, expected_args, args);
    return NULL;
  }

  *length = (expected_args*2 + 1);
  /* +1 for opcode, +1 for null byte */
  char *ret = (char *) malloc(sizeof(char) * (expected_args*2 + 2));
  ret[0] = a->payload.opcode;
  ret[expected_args*2 + 1] = '\0';

  char *tmp = ret + 1;
  ast_t *arg = a->arguments;
  while (arg != NULL) {
    tmp[0] = (char) (arg->payload.value2b >> 8);
    tmp[1] = (char) arg->payload.value2b;
    arg = arg->arguments;
    tmp += 2;
  }

  return ret;
}

char *
start_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("start", a, length);
}

char *
baud_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("baud", a, 1, length);
}

char *
control_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("control", a, length);
}

char *
safe_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("safe", a, length);
}

char *
full_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("full", a, length);
}

char *
spot_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("spot", a, length);
}

char *
cover_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("cover", a, length);
}

char *
demo_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("demo", a, 1, length);
}

char *
drive_handle_args(ast_t *a, int *length)
{
  return handle_two_byte_args("drive", a, 2, length);
}

char *
lsd_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("lsd", a, 1, length);
}

char *
led_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("led", a, 3, length);
}

char *
song_handle_args(ast_t *a, int *length)
{
  fprintf(stderr, "ERROR: Method not implemented (song).\n");
  return NULL;
}

char *
play_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("play", a, 1, length);
}

char *
sensors_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("sensors", a, 1, length);
}

char *
cad_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("cad", a, length);
}

char *
plsd_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("plsd", a, 3, length);
}

char *
drivedir_handle_args(ast_t *a, int *length)
{
  return handle_two_byte_args("drivedir", a, 2, length);
}

char *
digout_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("digout", a, 1, length);
}

char *
stream_handle_args(ast_t *a, int *length)
{
  fprintf(stderr, "ERROR: Method not implemented (stream).\n");
  return NULL;
}

char *
qlist_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("qlist", a, 2, length);
}

char *
togglestrm_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("togglestrm", a, 1, length);
}

char *
sendir_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("sendir", a, 1, length);
}

char *
script_handle_args(ast_t *a, int *length)
{
  char *out;
  int len = get_ast_char(a->arguments, &out);

  /* return format [script opcode][len][script] + '\0' */
  char *ret = (char *) malloc(sizeof(char) * (len + 2 + 1));
  ret[0] = a->payload.opcode;
  ret[1] = (char) len;
  ret[len + 2] = '\0';
  memcpy(ret + 2, out, len);

  *length = len + 2;
  free(out);
  return ret;
}

char *
playscript_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("playscript", a, length);
}

char *
showscript_handle_args(ast_t *a, int *length)
{
  return handle_zero_args("showscript", a, length);
}

char *
waittime_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("waittime", a, 1, length);
}

char *
waitdist_handle_args(ast_t *a, int *length)
{
  return handle_two_byte_args("waitdist", a, 1, length);
}

char *
waitangle_handle_args(ast_t *a, int *length)
{
  return handle_two_byte_args("waitangle", a, 1, length);
}

char *
waitevent_handle_args(ast_t *a, int *length)
{
  return handle_one_byte_args("waitevent", a, 1, length);
}

