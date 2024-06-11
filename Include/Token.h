#pragma once

#include <cstddef>
#include <iostream>

#define ENUMERATE_IDENTIFIERS(I) \
    I(Number)                    \
    I(Identifier)                \
    I(LeftParen)                 \
    I(RightParen)                \
    I(LeftSquare)                \
    I(RightSquare)               \
    I(LeftCurly)                 \
    I(RightCurly)                \
    I(LessThan)                  \
    I(GreaterThan)               \
    I(Equal)                     \
    I(Plus)                      \
    I(Minus)                     \
    I(Asterisk)                  \
    I(Slash)                     \
    I(Hash)                      \
    I(Dot)                       \
    I(Comma)                     \
    I(Colon)                     \
    I(Semicolon)                 \
    I(SingleQuote)               \
    I(DoubleQuote)               \
    I(Comment)                   \
    I(Pipe)                      \
    I(Keyword)                   \
    I(End)                       \
    I(Unexpected)

class Token {
public:
    enum class Kind {
#define IDENTIFIER(name) name,
        ENUMERATE_IDENTIFIERS(IDENTIFIER)
#undef IDENTIFIER
    };

    Token(Kind kind) noexcept
        : m_kind { kind }
    {
    }

    Token(Kind kind, char const* beg, std::size_t len) noexcept
        : m_kind { kind }
        , m_lexeme(beg, len)
    {
    }

    Token(Kind kind, char const* beg, char const* end) noexcept
        : m_kind { kind }
        , m_lexeme(beg, std::distance(beg, end))
    {
    }

    Kind kind() const noexcept { return m_kind; }

    void kind(Kind kind) noexcept { m_kind = kind; }

    std::string_view lexeme() const noexcept { return m_lexeme; }

    void lexeme(std::string_view lexeme) noexcept
    {
        m_lexeme = lexeme;
    }

    friend std::ostream& operator<<(std::ostream& os, Token::Kind const& kind)
    {
        static char const* const names[] {
#define IDENTIFIER_STR(name) #name,
            ENUMERATE_IDENTIFIERS(IDENTIFIER_STR)
#undef IDENTIFIER_STR
        };
        return os << names[static_cast<int>(kind)];
    }

    bool end() const noexcept { return m_kind == Kind::End; }
    bool unexpected() const noexcept { return m_kind == Kind::Unexpected; }

private:
    Kind m_kind {};
    std::string_view m_lexeme {};
};
