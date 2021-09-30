#pragma once

#include <iostream>

#include "Enums.h"

class Token {
 public:
  std::string _lexema;
  Categoria _atributo;

  Token(std::string lexema, Categoria atributo)
      : _lexema(lexema), _atributo(atributo) {}

  Token() : _lexema(""), _atributo(END) {}

  bool operator==(const Token& in) const {
    return in._lexema == this->_lexema && in._atributo == this->_atributo;
  }
};

#ifndef NDEBUG
std::ostream& operator<<(std::ostream& os, Token token) {
  std::cout << "<";
  switch (token._atributo) {
    case Categoria::IDENTIFICADOR:
      os << "Identificador";
      break;
    case Categoria::NUMERO:
      os << "Numero";
      break;
    case Categoria::RELOP:
      os << "RelOp";
      break;
    case Categoria::ASSIGN:
      os << "Assign";
      break;
  }
  os << ", " << token._lexema << ")";
  return os;
}
#endif