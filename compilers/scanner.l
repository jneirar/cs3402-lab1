%{
#include "Enums.h"
%}

%option noyywrap c++

DIGITO  [0-9]
LETRA   [a-zA-Z]
%%
entero return Categoria::INT;
sin_tipo return Categoria::VOID;
retorno return Categoria::RETURN;
mientras return Categoria::WHILE;
si return Categoria::IF;
sino return Categoria::ELSE;
main return Categoria::MAIN;

{LETRA}+  return Categoria::IDENTIFICADOR;
[+-]?{DIGITO}+\.{DIGITO}*[[eE]{DIGITO}+]? return Categoria::NUMERO; 
[+-]?{DIGITO}+ return Categoria::NUMERO;

"<" return Categoria::RELOP;
">" return Categoria::RELOP;
"<=" return Categoria::RELOP;
">=" return Categoria::RELOP;
"==" return Categoria::RELOP;
"!=" return Categoria::RELOP;

"=" return Categoria::ASSIGN;

"+" return Categoria::ADDOP;
"-" return Categoria::SUBOP;
"*" return Categoria::MULOP;
"/" return Categoria::DIVOP;

";" return Categoria::SEMICOLON;
"," return Categoria::COLON;
"(" return Categoria::OPPAR;
")" return Categoria::CLPAR;
"[" return Categoria::OPCOR;
"]" return Categoria::CLCOR;
"{" return Categoria::OPBRA;
"}" return Categoria::CLBRA;

"@" return Categoria::ERROR;

[\/.\*].*[\*.\/]

[\/.\*](.|\n)*[\*.\/]

.|\n
%%
