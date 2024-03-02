#include "tests.h"
#include "test_runner.h"
#include "common/board.h"
#include "common/corpus.h"
#include "common/find.h"
#include "common/line_reader.h"

#include <optional>
#include <sstream>
#include <string>

using std::wstringstream;
using std::endl;
using std::wstring;

void testLineReader() {
    wstringstream ss(L"line1\nline2\nline3");
    wistream_line_reader line_reader;
    ASSERT_EQUAL(L"line1", *line_reader.readLine(ss))
    ASSERT_EQUAL(L"line2", *line_reader.readLine(ss))
    ASSERT_EQUAL(L"line3", *line_reader.readLine(ss))
    auto eof = line_reader.readLine(ss);
    if (eof) {
        ASSERT(false)
    }
}

void testParseEmptyDictionary() {
    wstringstream ss(L"");
    wistream_line_reader line_reader;
    Corpus corpus(line_reader, ss);
    ASSERT_EQUAL(0u, corpus.words().size())
}

void testParseSimpleDictionary() {
    wstringstream ss;
    ss << L"1" << endl;
    ss << L"ЁЖ	NOUN,anim,masc sing,nomn" << endl;
    ss << L"ЕЖА	NOUN,anim,masc sing,gent" << endl;
    ss << L"ЕЖУ	NOUN,anim,masc sing,datv" << endl;
    ss << L"ЕЖА	NOUN,anim,masc sing,accs" << endl;
    ss << L"ЕЖОМ	NOUN,anim,masc sing,ablt" << endl;
    ss << L"ЕЖЕ	NOUN,anim,masc sing,loct" << endl;
    ss << L"ЕЖИ	NOUN,anim,masc plur,nomn" << endl;
    ss << L"ЕЖЕЙ	NOUN,anim,masc plur,gent" << endl;
    ss << L"ЕЖАМ	NOUN,anim,masc plur,datv" << endl;
    ss << L"ЕЖЕЙ	NOUN,anim,masc plur,accs" << endl;
    ss << L"ЕЖАМИ	NOUN,anim,masc plur,ablt" << endl;
    ss << L"ЕЖАХ	NOUN,anim,masc plur,loct" << endl;
    ss << L"" << endl;
    ss << L"2" << endl;
    ss << L"ХЁЖ	NOUN,inan,masc sing,nomn" << endl;
    ss << L"ЕЖА	NOUN,inan,masc sing,gent" << endl;
    ss << L"ЕЖУ	NOUN,inan,masc sing,datv" << endl;
    ss << L"ЁЖ	NOUN,inan,masc sing,accs" << endl;
    ss << L"ЕЖОМ	NOUN,inan,masc sing,ablt" << endl;
    ss << L"ЕЖЕ	NOUN,inan,masc sing,loct" << endl;
    ss << L"ЕЖИ	NOUN,inan,masc plur,nomn" << endl;
    ss << L"ЕЖЕЙ	NOUN,inan,masc plur,gent" << endl;
    ss << L"ЕЖАМ	NOUN,inan,masc plur,datv" << endl;
    ss << L"ЕЖИ	NOUN,inan,masc plur,accs" << endl;
    ss << L"ЕЖАМИ	NOUN,inan,masc plur,ablt" << endl;
    ss << L"ЕЖАХ	NOUN,inan,masc plur,L" << endl;

    ss.seekp(0);

    wistream_line_reader line_reader;
    Corpus corpus(line_reader, ss);
    const auto& words = corpus.words();
    ASSERT_EQUAL(2u, words.size())
    ASSERT_EQUAL(L"ЁЖ", words[0])
    ASSERT_EQUAL(L"ХЁЖ", words[1])
}

Board makeTestBoard() {
    wstringstream ss;
    ss << L"д с к а рс3" << endl;
    ss << L"и бх2 о к к" << endl;
    ss << L"р а дс2 в я" << endl;
    ss << L"а ю ах3 в б" << endl;
    ss << L"р ы к а р" << endl;
    ss.seekp(0);
    return readBoard(ss);
}

vector<wstring> makeTestDictionary() {
    wstringstream ss;
    ss << L"1" << endl;
    ss << L"ЁЖ	NOUN,anim,masc sing,nomn" << endl;
    ss << L"2" << endl;
    ss << L"ЕГДАЕ	NOUN,inan,masc sing,nomn" << endl;
    ss << L"2" << endl;
    ss << L"ЕГДАД	NOUN,inan,masc sing,nomn" << endl;
    ss << L"1" << endl;
    ss << L"КРАКОВЯК	NOUN,anim,masc sing,nomn" << endl;
    ss << L"1" << endl;
    ss << L"БРАВАДА	NOUN,anim,masc sing,nomn" << endl;
    ss << L"1" << endl;
    ss << L"ВДОВА	NOUN,anim,masc sing,nomn" << endl;
    ss << L"1" << endl;
    ss << L"ДИАДА	NOUN,anim,masc sing,nomn" << endl;
    ss.seekp(0);
    wistream_line_reader line_reader;
    return Corpus(line_reader, ss).words();
}

void testReadBoard() {
    auto board = makeTestBoard();
    ASSERT_EQUAL(5u, board.size())
    ASSERT_EQUAL(5u, board[0].size())
    ASSERT_EQUAL(L'Д', board[0][0].letter)
}

void testFindWordsOnBoard() {
    auto board = makeTestBoard();
    auto words = makeTestDictionary();
    WordsTrie trie{words};
    auto found = findWords(board, trie);

    ASSERT_EQUAL(4u, found.size())

    ASSERT_EQUAL(L"КРАКОВЯК", found[0].word)
    ASSERT_EQUAL(108, found[0].cost)

    ASSERT_EQUAL(L"БРАВАДА", found[1].word)
    ASSERT_EQUAL(76, found[1].cost)

    ASSERT_EQUAL(L"ВДОВА", found[2].word)
    ASSERT_EQUAL(50, found[2].cost)

    ASSERT_EQUAL(L"ДИАДА", found[3].word)
    ASSERT_EQUAL(50, found[3].cost)

    // ASSERT_EQUAL(112u, found.size())

    // ASSERT_EQUAL(L"КРАКОВЯК", found[0].word)
    // ASSERT_EQUAL(108, found[0].cost)

    // ASSERT_EQUAL(L"БРАВАДА", found[1].word)
    // ASSERT_EQUAL(76, found[1].cost)

    // ASSERT_EQUAL(L"ВДОВА", found[2].word)
    // ASSERT_EQUAL(50, found[2].cost)

    // ASSERT_EQUAL(L"ДИАДА", found[3].word)
    // ASSERT_EQUAL(50, found[3].cost)
}

void runTests(TestRunner& tr) {
    RUN_TEST(tr, testLineReader);
    RUN_TEST(tr, testParseEmptyDictionary);
    RUN_TEST(tr, testParseSimpleDictionary);
    RUN_TEST(tr, testReadBoard);
    RUN_TEST(tr, testFindWordsOnBoard);
}
