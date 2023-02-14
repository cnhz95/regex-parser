//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#include <iostream>
#include <string>
#include <vector>

using It = std::string::iterator;

enum Token {
    CHAR, OR, STAR, DOT, COUNTER, IGNORE, GROUP,
    L_PAREN, R_PAREN, UNKNOWN_TOKEN, END_OF_PROGRAM
};

Token lex(It& first, It last) {
    while (std::isspace(*first) && first != last) {
        first++;
    }
    if (*first >= 'A' && *first <= 'z') {
        return Token::CHAR;
    }
    if (first == last) {
        return Token::END_OF_PROGRAM;
    }
    switch (*first) {
        case '+': return Token::OR;
        case '*': return Token::STAR;
        case '.': return Token::DOT;
        case '(': return Token::L_PAREN;
        case ')': return Token::R_PAREN;
    }
    return Token::UNKNOWN_TOKEN;
}

struct ASTNode {
    virtual bool evaluate(std::string pattern) = 0;
    void add_child(ASTNode* child) {
        m_children.push_back(child);
    }
    std::vector<ASTNode*> m_children;
};

struct Char : ASTNode {
    bool evaluate(std::string pattern) override {

    }
    char m_char{};
};

struct Word : ASTNode {
    bool evaluate(std::string pattern) override {

    }
};

struct Or : ASTNode {
    bool evaluate(std::string pattern) override {

    }
};

struct Match : ASTNode {
    bool evaluate(std::string pattern) override {

    }
};

// <char> -> [a-zA-Z]
Char* parse_char(It& first, It last) {
    auto char_token = lex(first, last);
    if (char_token != Token::CHAR) {
        return nullptr;
    }
    auto p_char = new Char;
    p_char->m_char = *first;
    first++;
    return p_char;
}

// <word> -> <char> [<word>]
Word* parse_word(It& first, It last) {
    auto p_char = parse_char(first, last);
    if (!p_char) {
        return nullptr;
    }
    auto p_word = new Word;
    p_word->add_child(p_char);
    auto word = parse_word(first, last);
    if (word) {
        p_word->add_child(word);
    }
    return p_word;
}

// <parse> -> <word>
Match* parse_match(It& first, It last) {
    auto p_word = parse_word(first, last);
    if (!p_word) {
        return nullptr;
    }
    auto p_match = new Match;
    p_match->add_child(p_word);
    return p_match;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect argument!\n";
        return EXIT_FAILURE;
    }
    std::string input;
    std::getline(std::cin, input);
    std::cout << input << std::endl;

    auto start = input.begin();
    auto parse_tree = parse_match(start, input.end());
    if (!parse_tree) {
        std::cerr << "Parse error!\n";
        return EXIT_FAILURE;
    }
    auto result = parse_tree->evaluate(argv[1]);
}