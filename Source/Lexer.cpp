#include "Lexer.h"
#include <unordered_set>

Token Lexer::atom(Token::Kind kind) noexcept { return Token(kind, m_beg++, 1); }

Token Lexer::next() noexcept
{
    while (std::isspace((peek())))
        get();

    char c = peek();

    if (std::isalpha(c))
        return identifier();

    if (std::isdigit(c))
        return number();

    switch (c) {
    case '\0':
        return Token(Token::Kind::End, m_beg, 1);
    case '(':
        return atom(Token::Kind::LeftParen);
    case ')':
        return atom(Token::Kind::RightParen);
    case '[':
        return atom(Token::Kind::LeftSquare);
    case ']':
        return atom(Token::Kind::RightSquare);
    case '{':
        return atom(Token::Kind::LeftCurly);
    case '}':
        return atom(Token::Kind::RightCurly);
    case '<':
        return atom(Token::Kind::LessThan);
    case '>':
        return atom(Token::Kind::GreaterThan);
    case '=':
        return atom(Token::Kind::Equal);
    case '+':
        return atom(Token::Kind::Plus);
    case '-':
        return atom(Token::Kind::Minus);
    case '*':
        return atom(Token::Kind::Asterisk);
    case '/':
        return slash_or_comment();
    case '#':
        return atom(Token::Kind::Hash);
    case '.':
        return atom(Token::Kind::Dot);
    case ',':
        return atom(Token::Kind::Comma);
    case ':':
        return atom(Token::Kind::Colon);
    case ';':
        return atom(Token::Kind::Semicolon);
    case '\'':
        return atom(Token::Kind::SingleQuote);
    case '"':
        return atom(Token::Kind::DoubleQuote);
    case '|':
        return atom(Token::Kind::Pipe);
    default:
        return atom(Token::Kind::Unexpected);
    }
}

Token Lexer::identifier() noexcept
{
    char const* start = m_beg;

    get();
    while (is_identifier_char(peek()))
        get();

    std::string_view identifier_v { start, static_cast<std::size_t>(std::distance(start, m_beg)) };

    if (m_keywords.find(identifier_v) != m_keywords.end()) {
        return Token(Token::Kind::Keyword, start, m_beg);
    }

    return Token(Token::Kind::Identifier, start, m_beg);
}

Token Lexer::number() noexcept
{
    char const* start = m_beg;

    get();
    while (std::isdigit(peek()))
        get();

    return Token(Token::Kind::Number, start, m_beg);
}

Token Lexer::slash_or_comment() noexcept
{
    char const* start = m_beg;

    get();
    if (peek() == '/') {
        get();
        start = m_beg;
        while (peek() != '\0') {
            if (get() == '\n') {
                return Token(Token::Kind::Comment, start,
                    std::distance(start, m_beg) - 1);
            }
        }
        return Token(Token::Kind::Unexpected, m_beg, 1);
    }

    return Token(Token::Kind::Slash, start, 1);
}
