//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#include "parser.h"

Parser::Parser(It &first, It last) : m_match(parse_match(first, last)) {}

Match* Parser::parse_match(It& first, It last) {
    Expr* p_expr = parse_expr(first, last);
    if (!p_expr) {
        return nullptr;
    }
    auto p_match = new Match;
    p_match->add_child(p_expr);
    return p_match;
}

Expr* Parser::parse_expr(It& first, It last) {
    Subexpr* p_subexpr = parse_subexpr(first, last);
    if (!p_subexpr) {
        return nullptr;
    }
    auto p_expr = new Expr;
    p_expr->add_child(p_subexpr);
    Expr* r_expr = parse_expr(first, last);
    if (r_expr) {
        p_expr->add_child(r_expr);
    }
    return p_expr;
}

Subexpr* Parser::parse_subexpr(It& first, It last) {
    It temp = first;
    auto p_subexpr = new Subexpr;
    Group* p_group = parse_group(first, last);
    if (p_group) {
        p_subexpr->add_child(p_group);
        return p_subexpr;
    }
    first = temp;
    Or* p_or = parse_or(first, last);
    if (p_or) {
        p_subexpr->add_child(p_or);
        return p_subexpr;
    }
    first = temp;
    Word* p_word = parse_word(first, last);
    if (p_word) {
        p_subexpr->add_child(p_word);
        return p_subexpr;
    }
    first = temp;
    return nullptr;
}

Group* Parser::parse_group(It& first, It last) {
    if (m_lexer.lex(first, last) != Token::L_PAREN) {
        return nullptr;
    }
    It temp = first;
    first++;
    Expr* p_expr = parse_expr(first, last);
    if (!p_expr) {
        first = temp;
        return nullptr;
    }
    if (m_lexer.lex(first, last) != Token::R_PAREN) {
        first = temp;
        return nullptr;
    }
    first++;
    auto p_group = new Group;
    p_group->add_child(p_expr);
    return p_group;
}

Or* Parser::parse_or(It& first, It last) {
    It temp = first;
    Word* p_left_word = parse_word(first, last);
    if (!p_left_word) {
        first = temp;
        return nullptr;
    }
    if (m_lexer.lex(first, last) != Token::OR) {
        first = temp;
        return nullptr;
    }
    first++;
    Word* p_right_word = parse_word(first, last);
    if (!p_right_word) {
        first = temp;
        return nullptr;
    }
    auto p_or = new Or;
    p_or->add_child(p_left_word);
    p_or->add_child(p_right_word);
    return p_or;
}

Word* Parser::parse_word(It& first, It last) {
    auto p_word = new Word;
    Simple* p_simple = parse_simple(first, last);
    if (!p_simple) {
        return nullptr;
    }
    p_word->add_child(p_simple);
    Word* r_word = parse_word(first, last);
    if (r_word) {
        p_word->add_child(r_word);
    }
    return p_word;
}

Simple* Parser::parse_simple(It& first, It last) {
    It temp = first;
    auto p_simple = new Simple;
    Star* p_star = parse_star(first, last);
    if (p_star) {
        p_simple->add_child(p_star);
        return p_simple;
    }
    first = temp;
    Count* p_count = parse_count(first, last);
    if (p_count) {
        p_simple->add_child(p_count);
        return p_simple;
    }
    first = temp;
    Char* p_char = parse_char(first, last);
    if (p_char) {
        p_simple->add_child(p_char);
        return p_simple;
    }
    first = temp;
    return nullptr;
}

Star* Parser::parse_star(It& first, It last) {
    It temp = first;
    Dot* p_dot = nullptr;
    Char* p_char = parse_char(first, last);
    if (!p_char) {
        first = temp;
        p_dot = parse_dot(first, last);
        if (!p_dot) {
            first = temp;
            return nullptr;
        }
    }
    if (m_lexer.lex(first, last) != Token::STAR) {
        first = temp;
        return nullptr;
    }
    first++;
    auto p_star = new Star;
    p_char ? p_star->add_child(p_char) : p_star->add_child(p_dot);
    return p_star;
}

Count* Parser::parse_count(It& first, It last) {
    It temp = first;
    Dot* p_dot = nullptr;
    Char* p_char = parse_char(first, last);
    if (!p_char) {
        first = temp;
        p_dot = parse_dot(first, last);
        if (!p_dot) {
            first = temp;
            return nullptr;
        }
    }
    if (m_lexer.lex(first, last) != Token::L_BRACE) {
        first = temp;
        return nullptr;
    }
    first++;
    if (m_lexer.lex(first, last) != Token::DIGIT) {
        first = temp;
        return nullptr;
    }
    int count = *first - '0'; // ASCII '0' = 48
    first++;
    if (m_lexer.lex(first, last) != Token::R_BRACE) {
        first = temp;
        return nullptr;
    }
    first++;
    auto p_count = new Count;
    p_char ? p_count->add_child(p_char) : p_count->add_child(p_dot);
    p_count->m_count = count;
    return p_count;
}

Char* Parser::parse_char(It& first, It last) {
    if (m_lexer.lex(first, last) != Token::CHAR) {
        return nullptr;
    }
    auto p_char = new Char;
    p_char->m_char = *first;
    first++;
    return p_char;
}

Dot* Parser::parse_dot(It& first, It last) {
    if (m_lexer.lex(first, last) != Token::DOT) {
        return nullptr;
    }
    first++;
    auto p_dot = new Dot;
    return p_dot;
}