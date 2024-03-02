#pragma once

#include "board.h"
#include "trie.h"

#include <vector>
#include <string>

struct FoundWord {
    std::wstring word;
    int cost;

    FoundWord(std::wstring word, int cost) : word(std::move(word)), cost(cost) {}
};


std::vector<FoundWord> findWords(const Board& board, const WordsTrie& trie);