#include "create_statement_data.h"

#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

statement_data_t createStatementData(const invoice_t& invoce, const plays_t& plays) {
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& {
        return plays.at(aPerformance.playID);
    };

    auto amountFor = [&](const enriched_performance_t& aPerformance) {
        int result = 0;

        switch (aPerformance.play.type)
        {
        case TRAGEDY_TYPE:
            result = 40000;
            if (aPerformance.audience > 30) {
                result += 1000 * (aPerformance.audience - 30);
            }
            break;

        case COMEDY_TYPE:
            result = 30000;
            if (aPerformance.audience > 20) {
                result += 10000 + 500 * (aPerformance.audience - 20);
            }
            result += 300 * aPerformance.audience;
            break;

        default:
            exit(-1);
        }
        return result;
    };

    auto volumeCreditsFor = [&](const enriched_performance_t& aPerformance) {
        int result = 0;
        result += max(aPerformance.audience - 30, 0);
        if (COMEDY_TYPE == aPerformance.play.type) {
            result += floor(aPerformance.audience / 5);
        }
        return result;
    };

    auto totalVolumeCredits = [&](const statement_data_t& data) {
        return accumulate(data.performances.begin(), data.performances.end(), 0, [](int result, const enriched_performance_t& aPerformance) {
            return result + aPerformance.volumeCredits;
        });
    };

    auto totalAmount = [&](const statement_data_t& data) {
        return accumulate(data.performances.begin(), data.performances.end(), 0, [](int result, const enriched_performance_t& aPerformance) {
            return result + aPerformance.amount;
        });
    };

    enriched_performances_t enriched_performances;
    for_each(invoce.performances.begin(), invoce.performances.end(), [&](auto& aPerformance) {
        enriched_performances.emplace_back(aPerformance, playFor(aPerformance));
        enriched_performances.back().amount = amountFor(enriched_performances.back());
        enriched_performances.back().volumeCredits = volumeCreditsFor(enriched_performances.back());
    });

    statement_data_t result{
        invoce.customer,
        move(enriched_performances)
    };
    result.totalAmount = totalAmount(result);
    result.totalVolumeCredits = totalVolumeCredits(result);

    return result;
}
