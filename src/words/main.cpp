#include "args.h"
#include "common/board.h"
#include "common/find.h"
#include "common/trie.h"
#include "common/corpus.h"
#include "common/line_reader.h"

#include <iostream>
#include <fstream>
#include <string>


using std::vector;
using std::wifstream;
using std::wcout;
using std::wcin;
using std::endl;
using std::cin;
using std::cout;
using std::wstring;


void printWords(const vector<FoundWord>& words) {
    for (size_t i = 0; i < 50; ++i) {
        wcout << words[i].cost << L' ' << words[i].word << endl;
    }
    cout << "Total words found: " << words.size() << endl;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout.imbue(std::locale("ru_RU.UTF-8"));
    cin.imbue(std::locale("ru_RU.UTF-8"));
    wcout.imbue(std::locale("ru_RU.UTF-8"));
    wcin.imbue(std::locale("ru_RU.UTF-8"));

    auto args = parseArgs(argc, argv);


    wifstream ifs(args.filename);
    ifs.imbue(std::locale("ru_RU.UTF-8"));
    cout << "Reading dictionary from " << args.filename << "..." << endl;
    wistream_line_reader reader;
    Corpus dictionary(reader, ifs);
    const auto& words = dictionary.words();
    WordsTrie trie(words);
    cout << "Dictionary read complete. Size is " << words.size() << "." << endl;

    while (true) {
        auto board = readBoard(cin);
        wcout << L"Board read complete." << endl;
        const auto foundWords = findWords(board, trie);
        cout << "Board processed" << endl;
        printWords(foundWords);
    }
}


