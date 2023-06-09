#include "create_statement_data.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <numeric>

using namespace std;

class PerformanceCalculator {
public:
    PerformanceCalculator(const performance_t& aPerformance, const play_t& aPlay) : performance(aPerformance), play(aPlay) {}
    virtual ~PerformanceCalculator() {}

    virtual int amount() const {
        exit(-1);
    }

    virtual int volumeCredits() const {
        return max(performance.audience - 30, 0);
    };

public:
    const play_t& play;

protected:
    const performance_t& performance;
};

class TragedyCalculator final : public PerformanceCalculator {
public:
    TragedyCalculator(const performance_t& aPerformance, const play_t& aPlay) : PerformanceCalculator(aPerformance, aPlay) {}

    int amount() const override {
        int result = 40000;
        if (performance.audience > 30) {
            result += 1000 * (performance.audience - 30);
        }
        return result;
    }
};

class ComedyCalculator final : public PerformanceCalculator {
public:
    ComedyCalculator(const performance_t& aPerformance, const play_t& aPlay) : PerformanceCalculator(aPerformance, aPlay) {}

    int amount() const override {
        int result = 30000;
        if (performance.audience > 20) {
            result += 10000 + 500 * (performance.audience - 20);
        }
        result += 300 * performance.audience;
        return result;
    }

    int volumeCredits() const override {
        return PerformanceCalculator::volumeCredits() + floor(performance.audience / 5);
    }
};

unique_ptr<PerformanceCalculator> createPerformanceCalculator(const performance_t& aPerformance, const play_t& aPlay) {
    switch (aPlay.type)
    {
    case TRAGEDY_TYPE:
        return make_unique<TragedyCalculator>(aPerformance, aPlay);
        break;

    case COMEDY_TYPE:
        return make_unique<ComedyCalculator>(aPerformance, aPlay);
        break;

    default:
        exit(-1);
    }
    return make_unique<PerformanceCalculator>(aPerformance, aPlay);
}

statement_data_t createStatementData(const invoice_t& invoce, const plays_t& plays) {
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& {
        return plays.at(aPerformance.playID);
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
        auto calculator = createPerformanceCalculator(aPerformance, playFor(aPerformance));
        enriched_performances.emplace_back(aPerformance, calculator->play);
        enriched_performances.back().amount = calculator->amount();
        enriched_performances.back().volumeCredits = calculator->volumeCredits();
    });

    statement_data_t result{
        invoce.customer,
        move(enriched_performances)
    };
    result.totalAmount = totalAmount(result);
    result.totalVolumeCredits = totalVolumeCredits(result);

    return result;
}
