#include "corpus.h"
#include <memory>
#include <iostream>
#include <string_view>

using std::wistream;
using std::vector;
using std::wstring;
using std::wstring_view;


const vector<wstring>& Corpus::words() const {
    return this->_words;
};

bool Corpus::isSane(wstring_view word) const {
    if (word.size() < 2) {
        return false;
    }
    return std::all_of(word.begin(), word.end(), [](wchar_t c) {
        return (c >= L'А' && c <= L'Я') || c == L'Ё';
    });
}

