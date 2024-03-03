#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

using std::istream;
using std::wistream;
using std::wstring;
using std::string;
using std::optional;
using std::nullopt;
using std::wcout;
using std::endl;


template <typename TStream>
class wstring_line_reader {
public:
    virtual optional<wstring> readLine(TStream& in) = 0;
    virtual ~wstring_line_reader() = default;
};

class wistream_line_reader : public wstring_line_reader<wistream> {
public:
    optional<wstring> readLine(wistream& in) override {
        if (in.eof()) {
            return nullopt;
        }
        wstring line;
        getline(in, line);
        return line;
    }
};

class istream_line_reader : public wstring_line_reader<istream> {
public:
    optional<wstring> readLine(istream& in) override {
        if (in.eof()) {
            return nullopt;
        }
        string line;
        getline(in, line);
        return std::filesystem::path(line).wstring();
    }
};
