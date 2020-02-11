#include <getopt.h>
#include <cstdio>
#include <iostream>


int main(int argc, char **argv)
{
    int c, digit_optind = 0;

    struct option long_options[] = {
        { "help", no_argument, 0, 0 },
        { "lex", no_argument, 0, 0},
        { 0, 0, 0, 0}
    };

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;

        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch(c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg) {
                    printf(" with arg %s\n", optarg);
                }
                puts("");
                break;
            default:
                std::cerr << "Option unknown." << std::endl;
        }

    }
}
