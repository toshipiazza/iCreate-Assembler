#ifndef AST_H_
#define AST_H_

#include <stdint.h>

typedef struct _ast_t {
  short is_operation;
  union {
    uint8_t  opcode;
    uint16_t value2b;
    uint8_t  value1b;
  } payload;
  struct _ast_t *arguments;
  struct _ast_t *next_instruction;
} ast_t;

ast_t *ast_set_next(ast_t *, ast_t *);
ast_t *create_op_node(char, int, ...);
ast_t *create_arg_node_2byte(int, ast_t *);
ast_t *create_arg_node_1byte(int, ast_t *);
void ast_free(ast_t *);

char *start_handle_args(ast_t *, int *);
char *baud_handle_args(ast_t *, int *);
char *control_handle_args(ast_t *, int *);
char *safe_handle_args(ast_t *, int *);
char *full_handle_args(ast_t *, int *);
char *spot_handle_args(ast_t *, int *);
char *cover_handle_args(ast_t *, int *);
char *demo_handle_args(ast_t *, int *);
char *drive_handle_args(ast_t *, int *);
char *lsd_handle_args(ast_t *, int *);
char *led_handle_args(ast_t *, int *);
char *song_handle_args(ast_t *, int *);
char *play_handle_args(ast_t *, int *);
char *sensors_handle_args(ast_t *, int *);
char *cad_handle_args(ast_t *, int *);
char *plsd_handle_args(ast_t *, int *);
char *drivedir_handle_args(ast_t *, int *);
char *digout_handle_args(ast_t *, int *);
char *stream_handle_args(ast_t *, int *);
char *qlist_handle_args(ast_t *, int *);
char *togglestrm_handle_args(ast_t *, int *);
char *sendir_handle_args(ast_t *, int *);
char *script_handle_args(ast_t *, int *);
char *playscript_handle_args(ast_t *, int *);
char *showscript_handle_args(ast_t *, int *);
char *waittime_handle_args(ast_t *, int *);
char *waitdist_handle_args(ast_t *, int *);
char *waitangle_handle_args(ast_t *, int *);
char *waitevent_handle_args(ast_t *, int *);

/* maps opcodes to the corresponding *_handle_args method */
typedef char *(*const handle_args_t)(ast_t *, int *);
extern handle_args_t handle_args[159];

#endif
