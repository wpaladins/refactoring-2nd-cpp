#ifndef REFACTORING_2ND_CHAPTER4_PROVINCE_H
#define REFACTORING_2ND_CHAPTER4_PROVINCE_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

struct ProducerData {
    std::string name;
    int cost;
    int production;
};

struct ProvinceData {
   std::string name;
   std::vector<ProducerData> producers;
   int demand;
   int price;
};

class Province;

class Producer {
public:
    Producer(Province* aProvince, const ProducerData& data)
            : _province(aProvince),
              _cost(data.cost),
              _name(move(data.name)),
              _production(data.production) {}

    void production(int newProduction);
    int cost() const { return _cost; }
    int production() const { return _production; }

private:
    Province* _province;
    int _cost;
    std::string _name;
    int _production;
};

class Province {
public:
    Province(const ProvinceData& doc) {
        _name = doc.name;
        _totalProduction = 0;
        _demand = doc.demand;
        _price = doc.price;
        for_each(doc.producers.begin(), doc.producers.end(), [this](const ProducerData& d) {
            addProducer(std::make_unique<Producer>(this, d));
        });
    }

    void addProducer(std::unique_ptr<Producer> arg) {
        _totalProduction += arg->production();
        _producers.push_back(move(arg));
    }
    const std::vector<std::unique_ptr<Producer>>& producers() { return _producers; }
    int totalProduction() { return _totalProduction; }
    void totalProduction(int arg) { _totalProduction = arg; }
    int shortfall() {
        return _demand - _totalProduction;
    }
    int profit() {
        return demandValue() - demandCost();
    }
    int demandCost() {
        int remainingDemand = _demand;
        int result = 0;
        sort(_producers.begin(), _producers.end(), [](const auto& a, const auto& b) {
            return a->cost() < b->cost();
        });
        for_each(_producers.begin(), _producers.end(), [&](const auto& p) {
            int contribution = std::min(remainingDemand, p->production());
            remainingDemand -= contribution;
            result += contribution * p->cost();
        });
        return result;
    }
    int demandValue() {
        return satisfiedDemand() * _price;
    }
    int satisfiedDemand() {
        return std::min(_demand, _totalProduction);
    }

private:
    std::string _name;
    std::vector<std::unique_ptr<Producer>> _producers;
    int _totalProduction;
    int _demand;
    int _price;
};

inline void Producer::production(int newProduction) {
    _province->totalProduction(_province->totalProduction() + newProduction - _production);
    _production = newProduction;
}

#endif  // REFACTORING_2ND_CHAPTER4_PROVINCE_H
