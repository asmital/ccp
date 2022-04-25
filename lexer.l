%{
#include "parser.tab.hpp"
#include <iostream>
#include <stdbool.h>
#include <string>
using namespace std;
// extern int yyerror(char* s);

bool get_bool(char* str);
char* get_str(char* str);
%}

%option noyywrap

%%
([0-9]*[.])?[0-9]+          { yylval.val = atoi(yytext); return NUM;}
(true|false)                { yylval.b = get_bool(yytext); return BOOL; }
"("                         { return OPP; }
")"                         { return CLP; }
"{"                         { return OPB; }
"}"                         { return CLB; }
"["                         { return OPSB; }
"]"                         { return CLSB; }
","                         { return CMA; }
"\\"                        { return ENDSEC; }
"+"                         { return ADD; }
"-"                         { return SUB; }
"*"                         { return MUL; }
"/"                         { return DIV; }
"="                         { return ASG; }
"^"                         { return EXP; }
":"                         { return COL; }
">"                         { return GT; }
"<"                         { return LT; }
"<>"                        { return NE; }
"=="                        { return EQ; }
">="                        { return GTE; }
"<="                        { return LTE; }
"update"                    { return UPDATE_TK; }
"setup"                     { return SETUP_TK; }
"let"                       { return LET; }
"if"                        { return IF; }
"then"                      { return THEN; }
"else"                      { return ELSE; }
"endif"                     { return ENDIF; }
"keybind"                   { return KEYBD; }
([a-zA-Z_][a-zA-Z0-9_]*)    { yylval.str = strdup(yytext); return ID; }
\"(\\.|[^"\\])*\"           { yylval.str = strdup(yytext); return STR; }
\n                          { }
[ \t]                       {;}
;                           { return EOS;}
.                           {}
%%

bool get_bool(char* str) {
    return strcmp("true", str);
}

