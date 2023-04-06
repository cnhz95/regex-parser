#include "lexer.h"

Token Lexer::lex(It &first, It last) const {
    while (std::isspace(*first) && first != last) {
        first++;
    }
    if (first == last) {
        return Token::END_OF_PROGRAM;
    }
    if (*first >= 'A' && *first <= 'z') {
        return Token::CHAR;
    }
    if (*first >= '0' && *first <= '9') {
        return Token::DIGIT;
    }
    switch (*first) {
        case '+':
            return Token::OR;
        case '*':
            return Token::GREEDY;
        case '.':
            return Token::ANY;
        case '(':
            return Token::L_PAREN;
        case ')':
            return Token::R_PAREN;
        case '{':
            return Token::L_BRACE;
        case '}':
            return Token::R_BRACE;
        default:
            return Token::UNKNOWN_LEXEME;
    }
}