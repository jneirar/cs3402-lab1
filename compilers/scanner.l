%{
#include "Enums.h"
%}

%option noyywrap c++

DIGITO  [0-9]
LETRA   [a-z]
%%
{LETRA}+  return Categoria::IDENTIFICADOR;
[+-]?{DIGITO}+\.{DIGITO}* return Categoria::NUMERO; //TODO Reconocer números de punto flotante en notación exponencial, omitir comentarios en el estilo de C

"<=" return Categoria::RELOP;
">=" return Categoria::RELOP;
"=" return Categoria::ASSIGN;
"==" return Categoria::RELOP;

.|\n
%%
