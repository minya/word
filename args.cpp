#include "args.h"


Args parseArgs(int argc, char** argv) {
    Args args;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            args.filename = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0) {
            args.tests_run = true;
        }
    }
    return args;
}