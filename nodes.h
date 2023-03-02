//
// Christian Hernandez
// DT096G Programspråksteori
// Laboration 1
//

#ifndef REGEX_PARSER_NODES_H
#define REGEX_PARSER_NODES_H

#include <vector>

struct ASTNode {
    virtual bool evaluate(It& first, It last) = 0;
    void add_child(ASTNode* child) {
        m_children.push_back(child);
    }
    std::vector<ASTNode*> m_children;
};

struct Dot : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        first++;
        return true;
    }
};

struct Char : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return *first++ == m_char;
    }
    char m_char{};
};

struct Count : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        for (int i = 0; i < m_count; i++) {
            if (!m_children[0]->evaluate(first, last)) {
                return false;
            }
        }
        return true;
    }
    int m_count{};
};

struct Greedy : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return true;
    }
};

struct Star : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        while (m_children[0]->evaluate(first, last)) {}
        return true;
    }
};

struct Simple : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return m_children[0]->evaluate(first, last);
    }
};

struct Word : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        auto temp = first;
        for (auto child : m_children) {
            if (!child->evaluate(first, last)) {
                first = temp;
                return false;
            }
        }
        return true;
    }
};

struct Or : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return m_children[0]->evaluate(first, last) || m_children[1]->evaluate(first, last);
    }
};

struct Group : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return m_children[0]->evaluate(first, last);
    }
};

struct Subexpr : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        return m_children[0]->evaluate(first, last);
    }
};

struct Expr : ASTNode {
    bool evaluate(It& first, It last) override {
        if (first == last) {
            return false;
        }
        auto temp = first;
        for (auto child : m_children) {
            if (!child->evaluate(first, last)) {
                first = temp;
                return false;
            }
        }
        return true;
    }
};

struct Match : ASTNode {
    bool evaluate(It& first, It last) override {
        while (first != last) {
            if (m_children[0]->evaluate(first, last)) {
                return true;
            }
            first++;
        }
        return false;
    }
};

#endif