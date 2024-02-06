#pragma once

#include <vector>
#include <string>
#include <iostream>

using Char = wchar_t;

unsigned int charIndex(Char c);

enum class CellFlags : int16_t {
    None = 0,
    DoubleLetter = 1,
    TripleLetter = 2,
    DoubleWord = 4,
    TripleWord = 8
};

struct BoardCell {
    Char letter;
    CellFlags flags;

    unsigned int step_multiplier() const;
    unsigned int word_multiplier() const;
};

using Board = std::vector<std::vector<BoardCell>>;

Board readBoard(std::wistream& in);
Board readBoard(std::istream& in);
