//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#ifndef REGEX_PARSER_LEXER_H
#define REGEX_PARSER_LEXER_H

#include <string>

using It = std::string::iterator;

enum Token {
    CHAR, OR, STAR, DOT, DIGIT, L_BRACE, R_BRACE, L_PAREN, R_PAREN, END_OF_PROGRAM, UNKNOWN_LEXEME
};

class Lexer {
public:
    Lexer() = default;
    Token lex(It &first, It last);
};

#endif