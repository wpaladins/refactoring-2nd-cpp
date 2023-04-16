#ifndef REFACTORING_2ND_CHAPTER1_INCLUDE_PLAYS_H
#define REFACTORING_2ND_CHAPTER1_INCLUDE_PLAYS_H

#include <string>
#include <unordered_map>

enum {
    TRAGEDY_TYPE = 1,
    COMEDY_TYPE = 2
};

struct play_t
{
    std::string name;
    int type;
};

using plays_t = std::unordered_map<std::string, play_t>;

#endif  // REFACTORING_2ND_CHAPTER1_INCLUDE_PLAYS_H
