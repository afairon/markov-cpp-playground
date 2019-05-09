#ifndef MARKOV_HPP_
#define MARKOV_HPP_

#include <string>
#include <map>
#include <vector>

#include "wordprediction.hpp"
#include "chain.hpp"

class MarkovChain : public WordPrediction {
    private:
        uint8_t order;
        std::map<std::string, Chain> chains;
    public:
        MarkovChain(uint8_t ord) : order(ord) {}
        ~MarkovChain() {}

        void Add(const std::string& chainName, const NGram& seq) override;
        std::vector<std::string> Predict(const std::string& chainName, const NGram& seq) override;
        std::string Generate(const std::string& chainName, const NGram& seq) override;
};

#endif