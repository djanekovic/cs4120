#pragma once

struct Position {
    unsigned int idx;
    unsigned int cols;
    unsigned int line;

    Position(): idx{0}, cols{1}, line{1} {}
    void newline() { idx++; line++; cols = 1; }
    void advance() { idx++; cols++; }
};
