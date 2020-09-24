#pragma once

struct Position final{
    unsigned int idx {0};
    unsigned int cols {1};
    unsigned int line {1};

    void newline() { idx++; line++; cols = 1; }
    void advance() { idx++; cols++; }
};
