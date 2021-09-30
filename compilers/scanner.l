%{
#include "Enums.h"
%}

%option noyywrap c++

DIGITO  [0-9]
LETRA   [a-z]
%%
{LETRA}+  return Categoria::IDENTIFICADOR;
[+-]?{DIGITO}+\.{DIGITO}* return Categoria::NUMERO;

"<=" return Categoria::RELOP;
">=" return Categoria::RELOP;
"=" return Categoria::ASSIGN;
"==" return Categoria::RELOP;

.|\n
%%
