//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#ifndef REGEX_PARSER_PARSER_H
#define REGEX_PARSER_PARSER_H

#include "lexer.h"
#include "nodes.h"
#include <iostream>

class Parser {
public:
    Parser(It& first, It last);
    Match* get_match() { return m_match; }

private:
    Match* parse_match(It& first, It last);
    Expr* parse_expr(It& first, It last);
    Subexpr* parse_subexpr(It& first, It last);
    Group* parse_group(It& first, It last);
    Or* parse_or(It& first, It last);
    Simple* parse_simple(It& first, It last);
    Word* parse_word(It& first, It last);
    Greedy* parse_greedy(It& first, It last);
    Star* parse_star(It& first, It last);
    Count* parse_count(It& first, It last);
    Char* parse_char(It& first, It last);
    Dot* parse_dot(It& first, It last);

    Lexer m_lexer;
    Match* m_match;
};

#endif