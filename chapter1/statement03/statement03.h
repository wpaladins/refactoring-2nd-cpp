#ifndef REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H
#define REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H

#include "plays.h"
#include "invoices.h"

#include <string>
#include <vector>

// 复制 performance_t 中的信息, 而其他信息仅引用
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
    const std::string& customer; // 使用 const &
    enriched_performances_t performances; // pay attention
    int totalAmount;
    int totalVolumeCredits;
};

statement_data_t createStatementData(const invoice_t& invoce, const plays_t& plays);
std::string statement03(const invoice_t& invoce, const plays_t& plays);

#endif  // REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H
