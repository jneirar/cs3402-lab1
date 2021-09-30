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

TEST(LTTest, basicTest) {
  std::istrstream str("a < 5\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("a", Categoria::IDENTIFICADOR),
                                 Token("<", Categoria::RELOP),
                                 Token("5", Categoria::NUMERO)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(ifTest, basicTest) {
  std::istrstream str("si(a == b) a = c;\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("si", Categoria::IF),
                                 Token("(", Categoria::OPPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token("==", Categoria::RELOP),
                                 Token("b", Categoria::IDENTIFICADOR),
                                 Token(")", Categoria::CLPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("c", Categoria::IDENTIFICADOR),
                                 Token(";", Categoria::SEMICOLON)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(bracketsTest, basicTest) {
  std::istrstream str("{a = b}\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }

  std::vector<Token> expected = {Token("{", Categoria::OPBRA),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("b", Categoria::IDENTIFICADOR),
                                 Token("}", Categoria::CLBRA)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(ifeLSETest, basicTest) {
  std::istrstream str("si(a) a;\nsino{ a = c}");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                        
  std::vector<Token> expected = {Token("si", Categoria::IF),
                                 Token("(", Categoria::OPPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token(")", Categoria::CLPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token(";", Categoria::SEMICOLON),
                                 Token("sino", Categoria::ELSE),
                                 Token("{", Categoria::OPBRA),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("c", Categoria::IDENTIFICADOR),
                                 Token("}", Categoria::CLBRA)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(whileTest, basicTest) {
  std::istrstream str("mientras(a) a;\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                        
  std::vector<Token> expected = {Token("mientras", Categoria::WHILE),
                                 Token("(", Categoria::OPPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token(")", Categoria::CLPAR),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token(";", Categoria::SEMICOLON)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(mulTest, basicTest) {
  std::istrstream str("a = b * c;\n");

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
                                 Token("*", Categoria::MULOP),
                                 Token("c", Categoria::IDENTIFICADOR),
                                 Token(";", Categoria::SEMICOLON)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(divTest, basicTest) {
  std::istrstream str("a = b / c;\n");

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
                                 Token("/", Categoria::DIVOP),
                                 Token("c", Categoria::IDENTIFICADOR),
                                 Token(";", Categoria::SEMICOLON)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(declarationTest, basicTest) {
  std::istrstream str("entero a = 1;\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                        
  std::vector<Token> expected = {Token("entero", Categoria::INT),
                                 Token("a", Categoria::IDENTIFICADOR),
                                 Token("=", Categoria::ASSIGN),
                                 Token("1", Categoria::NUMERO),
                                 Token(";", Categoria::SEMICOLON)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(voidTest, basicTest) {
  std::istrstream str("sin_tipo funct\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                        
  std::vector<Token> expected = {Token("sin_tipo", Categoria::VOID),
                                 Token("funct", Categoria::IDENTIFICADOR)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(mainTest, basicTest) {
  std::istrstream str("sin_tipo main()\n{\nretorno 0;\n}\n");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                         
  std::vector<Token> expected = {Token("sin_tipo", Categoria::VOID),
                                 Token("main", Categoria::MAIN),
                                 Token("(", Categoria::OPPAR),
                                 Token(")", Categoria::CLPAR),
                                 Token("{", Categoria::OPBRA),
                                 Token("retorno", Categoria::RETURN),
                                 Token("0", Categoria::NUMERO),
                                 Token(";", Categoria::SEMICOLON),
                                 Token("}", Categoria::CLBRA)
                                 };
  EXPECT_EQ(tokens, expected);
}

TEST(multilineCommentTest, basicTest) {
  std::istrstream str("a/* Este es un \n comentario \n multilínea\n*/");

  FlexScanner scanner(str, std::cout);
  std::vector<Token> tokens;

  while (1) {
    auto token = scanner.get_token();
    if (token._atributo == END) break;
    tokens.push_back(token);
  }
                         
  std::vector<Token> expected = {Token("a", Categoria::IDENTIFICADOR)
                                 };
  EXPECT_EQ(tokens, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}