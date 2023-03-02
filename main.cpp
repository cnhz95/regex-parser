//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#include "lexer.h"
#include "parser.h"
#include <iostream>

/*
 * Recursive descent parser implementing the following BNF grammar
 * <match> := <expr>
 * <expr> := <subexpr> [<expr>]
 * <subexpr> := <group> | <or> | <count> | <word>
 * <group> := <'('> <expr> <')'>
 * <or> := <word> <'+'> <word>
 * <word> := <simple> [<word>]
 * <simple> := <star> | <count> | <char>
 * <star> := <char> <'*'> | <dot> <'*'>
 * <count> := <char> <'{'> <digit> <'}'> | <dot> <'{'> <digit> <'}'>
 * <char> := [A-Za-z]
 * <dot> := '.'
 */

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong argument!\n";
        return EXIT_FAILURE;
    }
    std::string pattern = argv[1];
    auto pattern_begin = pattern.begin();
    Parser parser(pattern_begin, pattern.end());
    auto root = parser.get_match();
    if (!root) {
        std::cerr << "Parsing error!\n";
        return EXIT_FAILURE;
    }
    std::string input;
    std::getline(std::cin >> std::ws, input);
    if (input.empty()) {
        std::cerr << "No input found!\n";
        return EXIT_FAILURE;
    }
    auto input_begin = input.begin();
    bool result = root->evaluate(input_begin, input.end());
    std::cout << "Match " << (result ? "found!\n" : "couldn't be found!\n");
    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}