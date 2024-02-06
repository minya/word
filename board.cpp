#include "board.h"
#include "trie.h"

#include <string_view>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

template <typename TStream>
class wstring_line_reader {
public:
    virtual wstring readLine(TStream& in) = 0;
    virtual ~wstring_line_reader() = default;
};

class wistream_line_reader : public wstring_line_reader<wistream> {
public:
    wstring readLine(wistream& in) override {
        wstring line;
        getline(in, line);
        return line;
    }
};

class istream_line_reader : public wstring_line_reader<istream> {
public:
    wstring readLine(istream& in) override {
        string line;
        getline(in, line);
        return std::filesystem::path(line).wstring();
    }
};


template <typename TStream, typename TLineReader>
Board readBoard(TStream& in_stream, TLineReader reader) {
    Board board(5, vector<BoardCell>(5));
    for (int i = 0; i < 5; i++) {
        wstring line = reader.readLine(in_stream);
        int col = 0;

        wstring_view sv{line};
        while (!sv.empty()) {
            auto space_pos = sv.find(L' ');
            space_pos = space_pos == string_view::npos ? sv.size() : space_pos + 1;
            wstring_view cell_str = sv.substr(0, space_pos);
            sv.remove_prefix(space_pos);
            auto& cell = board[i][col];
            col++;
            cell.letter = towupper(cell_str[0]);

            if (cell_str.size() <= 2) {
                continue;
            } 

            if (cell_str[1] == L'х') {
                cell.flags = cell_str[2] == '2' 
                    ? CellFlags::DoubleLetter
                    : CellFlags::TripleLetter;
            } else if (cell_str[1] == L'с') {
                cell.flags = cell_str[2] == '2' 
                    ? CellFlags::DoubleWord
                    : CellFlags::TripleWord;
            } else {
                cell.flags = CellFlags::None;
            }
        }
    }
    return board;
}

Board readBoard(std::istream& in_stream) {
    return readBoard(in_stream, istream_line_reader());
}

Board readBoard(std::wistream& in_stream) {
    return readBoard(in_stream, wistream_line_reader());
}

unsigned int BoardCell::step_multiplier() const {
    switch (flags) {
        case CellFlags::DoubleLetter:
            return 2;
        case CellFlags::TripleLetter:
            return 3;
        default:
            return 1;
    }
}

unsigned int BoardCell::word_multiplier() const {
    switch (flags) {
        case CellFlags::DoubleWord:
            return 2;
        case CellFlags::TripleWord:
            return 3;
        default:
            return 1;
    }
}

unsigned int charIndex(wchar_t c) {
    switch (c)
    {
    case L'А':
    case L'а':
        return 0;
    case L'Б':
    case L'б':
        return 1;
    case L'В':
    case L'в':
        return 2;
    case L'Г':
    case L'г':
        return 3;
    case L'Д':
    case L'д':
        return 4;
    case L'Е':
    case L'е':
    case L'Ё':
    case L'ё':
        return 5;
    case L'Ж':
    case L'ж':
        return 6;
    case L'З':
    case L'з':
        return 7;
    case L'И':
    case L'и':
        return 8;
    case L'Й':
    case L'й':
        return 9;
    case L'К':
    case L'к':
        return 10;
    case L'Л':
    case L'л':
        return 11;
    case L'М':
    case L'м':
        return 12;
    case L'Н':
    case L'н':
        return 13;
    case L'О':
    case L'о':
        return 14;
    case L'П':
    case L'п':
        return 15;
    case L'Р':
    case L'р':
        return 16;
    case L'С':
    case L'с':
        return 17;
    case L'Т':
    case L'т':
        return 18;
    case L'У':
    case L'у':
        return 19;
    case L'Ф':
    case L'ф':
        return 20;
    case L'Х':
    case L'х':
        return 21;
    case L'Ц':
    case L'ц':
        return 22;
    case L'Ч':
    case L'ч':
        return 23;
    case L'Ш':
    case L'ш':
        return 24;
    case L'Щ':
    case L'щ':
        return 25;
    case L'Ъ':
    case L'ъ':
        return 26;
    case L'Ы':
    case L'ы':
        return 27;
    case L'Ь':
    case L'ь':
        return 28;
    case L'Э':
    case L'э':
        return 29;
    case L'Ю':
    case L'ю':
        return 30;
    case L'Я':
    case L'я':
        return 31;
    default: 
        throw invalid_argument("Invalid character");
    }
}