#pragma once

#include <FlexLexer.h>

#include "Token.hpp"

namespace utec {
namespace compilers {

class FlexScanner : public yyFlexLexer {
 public:
  FlexScanner(std::istream& arg_yyin, std::ostream& arg_yyout)
      : yyFlexLexer(arg_yyin, arg_yyout) {}
  FlexScanner(std::istream* arg_yyin = nullptr,
              std::ostream* arg_yyout = nullptr)
      : yyFlexLexer(arg_yyin, arg_yyout) {}

  Token get_token() {
    int value;
    if ((value = yylex()) == 0) return Token();

    return Token(yytext, (Categoria)value);
  }
};

}  // namespace compilers
}  // namespace utec