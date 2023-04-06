#ifndef REGEX_PARSER_LEXER_H
#define REGEX_PARSER_LEXER_H

#include <string>

using It = std::string::iterator;

enum Token {
    CHAR, DIGIT, OR, GREEDY, ANY, L_PAREN, R_PAREN, L_BRACE, R_BRACE, END_OF_PROGRAM, UNKNOWN_LEXEME
};

class Lexer {
public:
    Lexer() = default;
    Token lex(It &first, It last) const;
};

#endif