#pragma once
#include <vector>
#include <string>
#include <iostream>

using std::wstring;
using std::wstring_view;
using std::vector;

class DictConverter {
public:
  template <typename TLineReader, typename TStream>
  void convert(TLineReader& in, TStream& is, std::wostream& os) {
    enum class ParseState { LookForNumber, Word };
    auto parse_state = ParseState::LookForNumber;
    vector<wstring> dictionary;
    for (auto lineMaybe = in.readLine(is);
            lineMaybe;
            lineMaybe = in.readLine(is)) {
        const auto& line = *lineMaybe;
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
                os << word << L'\n';
            }
            parse_state = ParseState::LookForNumber;
            continue;
        } else if (line[0] >= '0' && line[0] <= '9') {
            parse_state = ParseState::Word;
            continue;
        }
    }
    this->_words = std::move(dictionary);
  }
  const std::vector<std::wstring>& words() const;
private:
  bool isSane(std::wstring_view word) const;
  std::vector<std::wstring> _words;
};

