#include "statement02.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

static float amount_for(const performance_t& perf, const play_t& play) {
    float this_amount = 0;

    switch (play.type)
    {
    case TRAGEDY_TYPE:
        this_amount = 40000;
        if (perf.audience > 30) {
            this_amount += 1000 * (perf.audience - 30);
        }
        break;

    case COMEDY_TYPE:
        this_amount = 30000;
        if (perf.audience > 20) {
            this_amount += 10000 + 500 * (perf.audience - 20);
        }
        this_amount += 300 * perf.audience;
        break;

    default:
        exit(-1);
    }
    return this_amount;
}

string statement02(const invoice_t& invoce, plays_t& plays) {
    float total_amount = 0;
    int volume_credits = 0;

    ostringstream result;
    result.precision(2);
    result << fixed << "Statement for " << invoce.customer << endl;

    for (const auto& perf : invoce.performances) {
        auto& play = plays[perf.playID];
        float this_amount = amount_for(perf, play);

        // 增加观众量积分
        volume_credits += max(perf.audience - 30, 0);
        // 为每十位参加喜剧的观众增加额外积分
        if (COMEDY_TYPE == play.type) {
            volume_credits += floor(perf.audience / 5);
        }

        // 将该账单输出为一行
        result << "  " << play.name + ": $"
               << (this_amount / 100) << " ("
               << to_string(perf.audience) << " seats)" << endl;
        total_amount += this_amount;
    }
    result << "Amount owed is $" << (total_amount/100) << endl;
    result << "You earned " << to_string(volume_credits) << " credits" << endl;
    return move(result).str();
}
