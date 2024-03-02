#pragma once

#include "board.h"

#include <string>
#include <memory>

const size_t ALPHABET_SIZE = 32;

struct TrieNode {
    Char data;
    bool isEndOfWord;
    std::unique_ptr<TrieNode> children[ALPHABET_SIZE];

    explicit TrieNode(Char data);
};

class WordsTrie {
public:
    class iterator {
      public:
        explicit iterator(const TrieNode* node = nullptr);

        bool operator == (const iterator& other) const;
        bool operator != (const iterator& other) const;

        const TrieNode& get() const;

      private:
        const TrieNode* _node;
    };

    explicit WordsTrie(const std::vector<std::wstring>& words);
    void insert(const std::wstring& word);

    WordsTrie::iterator begin() const;
    WordsTrie::iterator end() const;

    WordsTrie::iterator find_next(const WordsTrie::iterator& current, Char next_char) const;

private:
    std::unique_ptr<TrieNode> _root;
};
