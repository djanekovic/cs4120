#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <getopt.h>

#include "xi_driver.h"

int main(int argc, char **argv)
{
    XIDriver driver;
    std::vector<std::string> filenames;

    struct option long_options[] = {
        { "help", no_argument, 0, 'h' },
        { "lex", no_argument, 0, 'l'},
        { 0, 0, 0, 0}
    };

    while (1) {
        int option_index = 0, c = 0;
        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch(c) {
            case 'h':
                return 0;
                break;
            case 'l':
                assert(optind < argc);

                for (int i = optind; i < argc; i++) {
                    filenames.push_back(std::string(argv[i]));
                }

                driver.trace_scanning(filenames);

                break;
            default:
                std::cerr << "Option unknown." << std::endl;
        }

    }
}
