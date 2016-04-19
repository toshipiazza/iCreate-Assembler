%{
#include <stdio.h>
#include "../ast/ast.h"
#include "../ast/analysis.h"
int yylex(void);
void yyerror(char *);
%}

%token integer
%token start
%token baud
%token control
%token safe
%token full
%token spot
%token cover
%token demo
%token drive
%token lsd
%token led
%token song
%token play
%token sensors
%token cad
%token plsd
%token drivedir
%token digout
%token stream
%token qlist
%token togglestrm
%token sendir
%token script
%token playscript
%token showscript
%token waittime
%token waitdist
%token waitangle
%token waitevent
%token end

%union {
  int    val;
  struct _ast_t *ast;
}

%type<ast> instruction_list instruction integer_tail_byte
%type<val> integer

%%
program:
       instruction_list { analyze_ast($1); ast_free($1); }

instruction_list:
       instruction instruction_list { $$ = ast_set_next($1, $2); }
       |                            { $$ = NULL; }
       ;

instruction:
           start               { $$ = create_op_node(128, 0); }
           | baud integer      { $$ = create_op_node(129, 1, create_arg_node_1byte($2, NULL)); }
           | control           { $$ = create_op_node(130, 0); }
           | safe              { $$ = create_op_node(131, 0); }
           | full              { $$ = create_op_node(132, 0); }
           | spot              { $$ = create_op_node(134, 0); }
           | cover             { $$ = create_op_node(135, 0); }
           | demo integer      { $$ = create_op_node(136, 1, create_arg_node_1byte($2, NULL)); }
           | drive integer integer
                               { $$ = create_op_node(137, 2, create_arg_node_2byte($2, NULL),
                                                             create_arg_node_2byte($3, NULL)); }
           | lsd integer       { $$ = create_op_node(138, 1, create_arg_node_1byte($2, NULL)); }
           | led integer integer integer
                               { $$ = create_op_node(139, 3, create_arg_node_1byte($2, NULL),
                                                             create_arg_node_1byte($3, NULL),
                                                             create_arg_node_1byte($4, NULL)); }
           | song integer integer_tail_byte
                               { $$ = create_op_node(140, 1, create_arg_node_1byte($2, $3));   }
           | play integer      { $$ = create_op_node(141, 1, create_arg_node_1byte($2, NULL)); }
           | sensors integer   { $$ = create_op_node(142, 1, create_arg_node_1byte($2, NULL)); }
           | cad               { $$ = create_op_node(143, 0); }
           | plsd integer integer integer
                               { $$ = create_op_node(134, 3, create_arg_node_1byte($2, NULL),
                                                             create_arg_node_1byte($3, NULL),
                                                             create_arg_node_1byte($4, NULL)); }
           | drivedir integer integer
                               { $$ = create_op_node(145, 2, create_arg_node_2byte($2, NULL),
                                                             create_arg_node_2byte($3, NULL)); }
           | digout integer    { $$ = create_op_node(147, 1, create_arg_node_1byte($2, NULL)); }
           | stream integer_tail_byte
                               { $$ = create_op_node(148, 1, $2); }
           | qlist integer_tail_byte
                               { $$ = create_op_node(149, 1, $2); }
           | togglestrm integer
                               { $$ = create_op_node(150, 1, create_arg_node_1byte($2, NULL)); }
           | sendir integer    { $$ = create_op_node(151, 1, create_arg_node_1byte($2, NULL)); }
           | script instruction_list end
                               { $$ = create_op_node(152, 1, $2); }
           | playscript        { $$ = create_op_node(153, 0); }
           | showscript        { $$ = create_op_node(154, 0); }
           | waittime integer  { $$ = create_op_node(155, 1, create_arg_node_1byte($2, NULL)); }
           | waitdist integer  { $$ = create_op_node(156, 1, create_arg_node_2byte($2, NULL)); }
           | waitangle integer { $$ = create_op_node(157, 1, create_arg_node_2byte($2, NULL)); }
           | waitevent integer { $$ = create_op_node(158, 1, create_arg_node_1byte($2, NULL)); }
           ;

integer_tail_byte:
            integer integer_tail_byte   { $$ = create_arg_node_1byte($1, $2); }
            |                           { $$ = NULL; }
            ;
%%

void
yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}
