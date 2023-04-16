#ifndef REFACTORING_2ND_CHAPTER1_INCLUDE_INVOICES_H
#define REFACTORING_2ND_CHAPTER1_INCLUDE_INVOICES_H

#include <vector>
#include <string>

struct performance_t
{
    std::string playID;
    int audience;
};

using performances_t = std::vector<performance_t>;

struct invoice_t
{
    std::string customer;
    performances_t performances;
};

using invoices_t = std::vector<invoice_t>;

#endif  // REFACTORING_2ND_CHAPTER1_INCLUDE_INVOICES_H
