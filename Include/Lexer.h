#pragma once

#include "Token.h"
#include <string_view>
#include <unordered_set>

using namespace std::literals;

class Lexer {
public:
    Lexer(char const* beg) noexcept
        : m_beg { beg }
    {
    }

    Token next() noexcept;

private:
    Token identifier() noexcept;
    Token number() noexcept;
    Token slash_or_comment() noexcept;
    Token atom(Token::Kind) noexcept;

    char peek() const noexcept { return *m_beg; }
    char get() noexcept { return *m_beg++; }

    char const* m_beg = nullptr;

    std::unordered_set<std::string_view> const m_keywords {
        "break"sv,
        "case"sv,
        "char"sv,
        "const"sv,
        "continue"sv,
        "default"sv,
        "do"sv,
        "else"sv,
        "enum"sv,
        "for"sv,
        "goto"sv,
        "if"sv,
        "int"sv,
        "return"sv,
        "switch"sv,
        "void"sv,
        "while"sv,
    };
};

static inline bool is_identifier_char(char c) noexcept
{
    return (std::isdigit(c) || std::isalpha(c) || c == '_') ? true : false;
}
