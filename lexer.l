%{
#include "parser.tab.hpp"
#include <iostream>
#include <stdbool.h>
using namespace std;
// extern int yyerror(char* s);
%}

%option noyywrap

%%
"["                         { return OPSB;}
"setup"                     { return SETUP_TK;}
"]"                         { return CLSB;}
/* ([0-9]*[.])?[0-9]+          { printf("NUM %s\n", yytext); }
(true|false)                { printf("BOOL %s\n", yytext);}
"("                         { printf("OPP\n");}
")"                         { printf("CLP\n");}
"{"                         { printf("OPB\n");}
"}"                         { printf("CLB\n");}
"["                         { printf("OPSB\n");}
"]"                         { printf("CLSB\n");}
","                         { printf("CMA\n");}
"\\"                        { printf("ENDSEC\n");}
"+"                         { printf("ADD\n");}
"-"                         { printf("SUB\n");}
"*"                         { printf("MUL\n");}
"/"                         { printf("DIV\n");}
"="                         { printf("ASG\n");}
"^"                         { printf("EXP\n");}
":"                         { printf("COL\n");}
">"                         { printf("GT\n");}
"<"                         { printf("LT\n");}
"<>"                        { printf("NE\n");}
"=="                        { printf("EQ\n");}
">="                        { printf("GTE\n");}
"<="                        { printf("LTE\n");}
"update"                    { printf("UPDATE_TK\n");}
"setup"                     { printf("SETUP_TK\n");}
"let"                       { printf("LET\n");}
"if"                        { printf("IF\n");}
"then"                      { printf("THEN\n");}
"else"                      { printf("ELSE\n");}
"endif"                     { printf("ENDIF\n");}
"keybind"                   { printf("KEYBD\n");}
([a-zA-Z_][a-zA-Z0-9_]*)    { printf("ID %s\n", yytext);}
\"(\\.|[^"\\])*\"           { printf("STR %s\n", yytext);}
\n                          { }
[ \t]                       {;}
;                           {printf("EOS\n");}
.                           {printf("Unknown symbol %s\n", yytext);} */
%%
