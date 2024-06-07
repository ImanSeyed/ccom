#include "Lexer.h"
#include "Token.h"
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "USAGE: ccom /path/to/code.c\n";
        return -1;
    }

    std::ifstream source_file { argv[1] };
    if (!source_file) {
        std::cerr << "Failed to open the " << argv[1] << "\n";
        return -2;
    }

    std::string code((std::istreambuf_iterator<char>(source_file)),
        std::istreambuf_iterator<char>());

    Lexer lex(code.data());
    for (auto token = lex.next();
         token.kind() != Token::Kind::End && token.kind() != Token::Kind::Unexpected;
         token = lex.next()) {
        std::cout << std::setw(12) << token.kind() << " |" << token.lexeme()
                  << "|\n";
    }
    return 0;
}
