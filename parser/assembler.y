%{
#include <stdio.h>
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

%%
program:
       instruction program
       |
       ;

instruction:
  start
  | baud integer
  | control
  | safe
  | full
  | spot
  | cover
  | demo integer
  | drive integer integer
  | lsd integer
  | led integer integer integer
  | song integer integer integer_tail
  | play integer
  | sensors integer
  | cad
  | plsd integer integer integer
  | drivedir integer integer
  | digout integer
  | stream integer integer_tail
  | qlist integer integer_tail
  | togglestrm integer
  | sendir integer
  | script program end
  | playscript
  | showscript
  | waittime integer
  | waitdist integer
  | waitangle integer
  | waitevent integer
  ;

integer_tail:
            integer integer_tail
            |
            ;
%%

void
yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}
