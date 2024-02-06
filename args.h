#pragma once

#include <string>


struct Args {
    std::string filename;
    bool tests_run = false;
};

Args parseArgs(int argc, char** argv);