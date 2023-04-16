#include "statement02.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

string statement02(const invoice_t& invoce, const plays_t& plays) {
    // 以查询取代临时变量(178)
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& { // 注意返回值类型
        return plays.at(aPerformance.playID); // 使用 at(), 因为 plays 是 const 的
    };

    // 提炼函数(106)
    auto amountFor = [&](const performance_t& aPerformance, const play_t& play) {
        float result = 0;

        switch (play.type)
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

    float total_amount = 0;
    int volume_credits = 0;

    ostringstream result;
    result.precision(2);
    result << fixed << "Statement for " << invoce.customer << endl;

    for (auto& perf : invoce.performances) {
        auto& play = playFor(perf);
        float this_amount = amountFor(perf, play);

        volume_credits += max(perf.audience - 30, 0);
        if (COMEDY_TYPE == play.type) {
            volume_credits += floor(perf.audience / 5);
        }

        result << "  " << play.name + ": $"
               << (this_amount / 100) << " ("
               << to_string(perf.audience) << " seats)" << endl;
        total_amount += this_amount;
    }
    result << "Amount owed is $" << (total_amount/100) << endl;
    result << "You earned " << to_string(volume_credits) << " credits" << endl;
    return move(result).str();
}
