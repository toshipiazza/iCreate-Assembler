%{
#include <stdlib.h>
void yyerror(char *);
#include "assembler.tab.h"
%}

%%
[ \t\n]    ; /* skip whitespace */
"-"?[0-9]+ { yylval = atoi(yytext); return integer; }
"start"      return start;
"baud"       return baud;
"control"    return control;
"safe"       return safe;
"full"       return full;
"spot"       return spot;
"cover"      return cover;
"demo"       return demo;
"drive"      return drive;
"lsd"        return lsd;
"led"        return led;
"song"       return song;
"play"       return play;
"sensors"    return sensors;
"cad"        return cad;
"plsd"       return plsd;
"drivedir"   return drivedir;
"digout"     return digout;
"stream"     return stream;
"qlist"      return qlist;
"togglestrm" return togglestrm;
"sendir"     return sendir;
"script"     return script;
"playscript" return playscript;
"showscript" return showscript;
"waittime"   return waittime;
"waitdist"   return waitdist;
"waitangle"  return waitangle;
"waitevent"  return waitevent;
"end"        return end;
. { yyerror("invalid instruction or operand"); return EXIT_FAILURE; }
%%

int
yywrap(void)
{
  return 1;
}
