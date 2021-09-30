#include <gtest/gtest.h>

#include <strstream>

#include "FlexScanner.hpp"

using namespace utec::compilers;

TEST(SimpleTest, basicTest) {
  std::istrstream str("a=-2.7E4");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("-2.7E4", Categoria::NUMERO)};
  EXPECT_EQ(tokens, expected);
}

TEST(CommentTest, hasComments) {
  std::istrstream str("a = b /* shouldn't be printed */ c = d");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("b", Categoria::IDENTIFICADOR),
                                 Token("c", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("d", Categoria::IDENTIFICADOR)};
  EXPECT_EQ(tokens, expected);
}

TEST(ErrorTest, basicTest) {
  std::istrstream str("a = b\n@");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("b", Categoria::IDENTIFICADOR),
                                 Token("@", Categoria::ERROR),
                                 };
  EXPECT_EQ(tokens, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}