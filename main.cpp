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
    CHAR, OR, REPEAT, ANY, COUNTER, IGNORE,
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
        case '*': return Token::REPEAT;
        case '.': return Token::ANY;
        case '(': return Token::L_PAREN;
        case ')': return Token::R_PAREN;
        case '{': return Token::COUNTER;
        default: return Token::UNKNOWN_TOKEN;
    }
}

struct ASTNode {
    virtual bool evaluate(It& first, It last) = 0;
    void add_child(ASTNode* child) {
        m_children.push_back(child);
    }
    std::vector<ASTNode*> m_children;
};

struct Char : ASTNode {
    bool evaluate(It& first, It last) override {

    }
    char m_char{};
};

struct Word : ASTNode {
    bool evaluate(It& first, It last) override {

    }
};

struct Or : ASTNode {
    bool evaluate(It& first, It last) override {

    }
};

struct Repeat : ASTNode {
    bool evaluate(It& first, It last) override {

    }
};

struct Any : ASTNode {
    bool evaluate(It& first, It last) override {
        return true;
    }
};

struct Group : ASTNode {
    bool evaluate(It& first, It last) override {

    }
};

struct Counter : ASTNode {
    bool evaluate(It& first, It last) override {

    }
};

struct Match : ASTNode {
    bool evaluate(It& first, It last) override {
        auto word_node = dynamic_cast<Word*>(m_children[0]);
        return word_node->evaluate(first, last);
    }
};

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

Repeat* parse_repeat(It& first, It last) {
    auto temp = first;
    auto p_char = parse_char(first, last);
    if (!p_char) {
        first = temp;
        return nullptr;
    }
    auto repeat_token = lex(first, last);
    if (repeat_token != Token::REPEAT) {
        first = temp;
        return nullptr;
    }
    auto p_repeat = new Repeat;
    p_repeat->add_child(p_char);
    return p_repeat;
}

Word* parse_word(It& first, It last) {
    auto p_word = new Word;
    auto p_repeat = parse_repeat(first, last);
    if (p_repeat) {
        p_word->add_child(p_repeat);
        first++;
    }
    auto temp = first;
    auto p_char = parse_char(first, last);
    if (!p_char) {
        first = temp;
        if (p_repeat) {
            return p_word;
        }
        return nullptr;
    }
    p_word->add_child(p_char);
    auto word = parse_word(first, last);
    if (word) {
        p_word->add_child(word);
    }
    return p_word;
}

Or* parse_or(It& first, It last) {
    auto temp = first;
    auto p_left_word = parse_word(first, last);
    if (!p_left_word) {
        first = temp;
        return nullptr;
    }
    auto or_token = lex(first, last);
    if (or_token != Token::OR) {
        first = temp;
        return nullptr;
    }
    first++;
    auto p_right_word = parse_word(first, last);
    if (!p_right_word) {
        first = temp;
        return nullptr;
    }
    auto p_or = new Or;
    p_or->add_child(p_left_word);
    p_or->add_child(p_right_word);
    return p_or;
}

Match* parse_match(It& first, It last) {
    auto p_match = new Match;
    auto temp = first;
    auto p_or = parse_or(temp, last);
    if (p_or) {
        p_match->add_child(p_or);
        return p_match;
    }
    auto p_word = parse_word(first, last);
    if (!p_word) {
        return nullptr;
    }
    p_match->add_child(p_word);
    return p_match;
}

int main(int argc, char* argv[]) {
    /*if (argc != 2) {
        std::cerr << "Incorrect argument!\n";
        return EXIT_FAILURE;
    }
    std::string input;
    std::getline(std::cin, input);
    std::cout << input << '\n';
    */
    std::string input = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";

    std::string pattern = "lo* could";
    auto pattern_begin = pattern.begin();
    auto parse_tree = parse_match(pattern_begin, pattern.end());
    if (!parse_tree) {
        std::cerr << "Parse error!\n";
        return EXIT_FAILURE;
    }

    //auto input_begin = input.begin();
    //auto result = parse_tree->evaluate(input_begin, input.end());
}