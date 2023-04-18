#include "create_statement_data.h"

#include <sstream>

using namespace std;

string usd(int aNumber) {
    string number_str = to_string(float(aNumber)/100);
    return "$" + number_str.substr(0, number_str.find(".") + 3);
};

string renderPlainText(const statement_data_t& data, const plays_t& plays) {
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

string renderHtml(const statement_data_t& data, const plays_t& plays) {
    ostringstream result;
    result << "<h1>Statement for " << data.customer << "</h1>\n";

    result << "<table>\n";
    result << "    <tr><th>play</th><th>seats</th><th>cost</th></tr>\n";
    for (auto& perf : data.performances) {
        result << "    <tr>\n"
               << "        <td>" << perf.play.name + "</td>\n"
               << "        <td>" << to_string(perf.audience) + "</td>\n"
               << "        <td>" << usd(perf.amount) + "</td>\n"
               << "    </tr>\n";
    }
    result << "</table>\n";

    result << "<p>Amount owed is <em>" << usd(data.totalAmount) << "</em></p>\n";
    result << "<p>You earned <em>" << to_string(data.totalVolumeCredits) << "</em> credits</p>\n";
    return move(result).str();
}

string statement04(const invoice_t& invoice, const plays_t& plays) {
    return renderPlainText(createStatementData(invoice, plays), plays);
}

string htmlStatement04(const invoice_t& invoice, const plays_t& plays) {
    return renderHtml(createStatementData(invoice, plays), plays);
}
