#include "common/corpus.h"
#include "common/line_reader.h"

#include <iostream>
#include <fstream>
#include <string>


using std::wistream;
using std::wostream;
using std::istream;


void convertDictionaryToPlain(istream& is, std::wostream& os) {
    istream_line_reader line_reader;
    Corpus corpus(line_reader, is);
    for (const auto& word : corpus.words()) {
        os << word << std::endl;
    }
}

int main() {
    std::ifstream ifs("dict.opcorpora.txt");
    std::wofstream ofs("dict.txt");
    convertDictionaryToPlain(ifs, ofs);
}
