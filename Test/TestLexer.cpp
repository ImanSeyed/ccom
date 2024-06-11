#include "Lexer.h"
#include "Token.h"
#include <gtest/gtest.h>
#include <vector>

TEST(TestLexer, should_validate_multi_digit)
{
    char const* const code = "int main() {"
                             "return 100;"
                             "}";
    Lexer lex(code);
    std::vector<Token> const tokens = lex.get_tokens();

    EXPECT_EQ(tokens[6].lexeme(), "100");
}

void VALIDATE_TOKENS(char const* const code)
{
    Lexer lex(code);
    std::vector<Token> const tokens = lex.get_tokens();

    EXPECT_TRUE(Token::Kind::Keyword == tokens[0].kind() && "int" == tokens[0].lexeme());
    EXPECT_TRUE(Token::Kind::Identifier == tokens[1].kind() && "main" == tokens[1].lexeme());
    EXPECT_TRUE(Token::Kind::LeftParen == tokens[2].kind() && "(" == tokens[2].lexeme());
    EXPECT_TRUE(Token::Kind::RightParen == tokens[3].kind() && ")" == tokens[3].lexeme());
    EXPECT_TRUE(Token::Kind::LeftCurly == tokens[4].kind() && "{" == tokens[4].lexeme());
    EXPECT_TRUE(Token::Kind::Keyword == tokens[5].kind() && "return" == tokens[5].lexeme());
    EXPECT_TRUE(Token::Kind::Number == tokens[6].kind() && "0" == tokens[6].lexeme());
    EXPECT_TRUE(Token::Kind::Semicolon == tokens[7].kind() && ";" == tokens[7].lexeme());
    EXPECT_TRUE(Token::Kind::RightCurly == tokens[8].kind() && "}" == tokens[8].lexeme());
}

TEST(TestLexer, should_ignore_newlines)
{
    char const* const code = "int\n"
                             "main\n"
                             "(\n"
                             ")\n"
                             "{\n\n\n"
                             "return\n"
                             "0\n"
                             ";\n\n\n"
                             "}\n";

    VALIDATE_TOKENS(code);
}

TEST(TestLexer, should_work_without_newlines)
{
    char const* const code = "int main(){return 0;}";

    VALIDATE_TOKENS(code);
}

TEST(TestLexer, should_ignore_spaces)
{
    char const* const code = "int    main      (  )  {   return 0;  }";

    VALIDATE_TOKENS(code);
}
