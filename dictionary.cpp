#include "dictionary.h"
#include <memory>
#include <iostream>
#include <string_view>

using std::wistream;
using std::vector;
using std::wstring;
using std::wstring_view;


bool isSane(wstring_view word) {
    if (word.size() < 2) {
        return false;
    }
    return std::all_of(word.begin(), word.end(), [](wchar_t c) {
        return (c >= L'А' && c <= L'Я') || c == L'Ё';
    });
}

Dictionary::Dictionary(wistream& in) {
    enum class ParseState { LookForNumber, Word };
    vector<wstring> dictionary;
    auto parse_state = ParseState::LookForNumber;
    wstring line;
    while (getline(in, line)) {
        if (parse_state == ParseState::Word) {
            auto word_end = line.find_first_of('\t');
            if (word_end == wstring::npos) {
                parse_state = ParseState::LookForNumber;
                continue;
            }
            wstring_view word(line);
            word.remove_suffix(word.size() - word_end);
            wstring_view type(line);
            type.remove_prefix(word_end + 1);
            type.remove_suffix(type.size() - 4);
            if (
                    type != L"ADVB" &&
                    type != L"NOUN" &&
                    type != L"ADJF" &&
                    type != L"INFN" &&
                    type != L"PTRF" &&
                    type != L"GRND"
                ) {
                parse_state = ParseState::LookForNumber;
                continue;
            }
            if (isSane(word)) {
                dictionary.emplace_back(word.begin(), word.end());
            }
            parse_state = ParseState::LookForNumber;
            continue;
        } else if (line[0] >= '0' && line[0] <= '9') {
            parse_state = ParseState::Word;
            continue;
        }
    }
    this->_words = std::move(dictionary);
};

const vector<wstring>& Dictionary::words() const {
    return this->_words;
};
