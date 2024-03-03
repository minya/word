#include "common/dict_converter.h"
#include "common/line_reader.h"

#include <iostream>
#include <fstream>
#include <string>


using std::wistream;
using std::wostream;
using std::istream;

struct Args {
    std::string input_file;
    std::string output_file;
};

Args parseArgs(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::exit(1);
    }
    return {argv[1], argv[2]};
}


void convertDictionaryToPlain(istream& is, wostream& os) {
    os.imbue(std::locale("ru_RU.UTF-8"));
    istream_line_reader line_reader;
    DictConverter converter;
    converter.convert(line_reader, is, os);
}

int main(int argc, char* argv[]) {
    auto args = parseArgs(argc, argv);
    std::ifstream ifs(args.input_file);
    std::wofstream ofs(args.output_file);
    convertDictionaryToPlain(ifs, ofs);
    return EXIT_SUCCESS;
}
