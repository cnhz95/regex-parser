# Regex-like parser

Recursive-descent parser implementing the following EBNF grammar:
```
<match> := <expr>
<expr> := <subexpr> [<expr>]
<subexpr> := <group> | <or> | <count> | <word>
<group> := '(' <expr> ')'
<or> := <word> '+' <word>
<word> := <simple> [<word>]
<simple> := <count> | <greedy> | <char>
<count> := <char> '{' <digit> '}' | <any> '{' <digit> '}'
<greedy> := <char> '*' | <any> '*'
<char> := [A-Za-z]
<digit> := [0-9]
<any> := '.'
```
## Usage
Run from the terminal using, for example, the command `./regex-parser "lo* could.{3}" < input.txt`
