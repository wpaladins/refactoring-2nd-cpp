#ifndef REFACTORING_2ND_CHAPTER1_STATEMENT04_CREATE_STATEMENT_DATA_H
#define REFACTORING_2ND_CHAPTER1_STATEMENT04_CREATE_STATEMENT_DATA_H

#include "plays.h"
#include "invoices.h"

#include <string>
#include <vector>

struct enriched_performance_t : public performance_t {
    const play_t& play;
    int amount;
    int volumeCredits;
    enriched_performance_t(const performance_t& parent,
                           const play_t& play)
                           : performance_t(parent),
                             play(play) {}
};

using enriched_performances_t = std::vector<enriched_performance_t>;

struct statement_data_t {
    const std::string& customer;
    enriched_performances_t performances;
    int totalAmount;
    int totalVolumeCredits;
};

statement_data_t createStatementData(const invoice_t& invoce, const plays_t& plays);

#endif  // REFACTORING_2ND_CHAPTER1_STATEMENT04_CREATE_STATEMENT_DATA_H
