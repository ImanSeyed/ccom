#include "Lexer.h"
#include "Token.h"
#include <fstream>
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
    std::vector<Token> tokens = lex.get_tokens();

    // TODO: parse tokens...

    return 0;
}
