#include "create_statement_data.h"

#include <sstream>

using namespace std;

// 保持数据不可变(不修改传给函数的参数)
string renderPlainText(const statement_data_t& data, const plays_t& plays) {
    auto usd = [](int aNumber) {
        string number_str = to_string(float(aNumber)/100);
        return "$" + number_str.substr(0, number_str.find(".") + 3);
    };

    ostringstream result;
    result << "Statement for " << data.customer << endl;

    for (auto& perf : data.performances) {
        result << "  " << perf.play.name + ": "
            << usd(perf.amount) << " ("
            << to_string(perf.audience) << " seats)" << endl;
    }

    result << "Amount owed is " << usd(data.totalAmount) << endl;
    result << "You earned " << to_string(data.totalVolumeCredits) << " credits" << endl;
    return move(result).str();
}

string statement03(const invoice_t& invoice, const plays_t& plays) {
    return renderPlainText(createStatementData(invoice, plays), plays);
}
