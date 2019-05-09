#ifndef WORD_PREDICTION_HPP_
#define WORD_PREDICTION_HPP_

#include <string>
#include <vector>

#include "chain.hpp"

class WordPrediction {
    virtual void Add(const std::string& chainName, const NGram& seq) = 0;
    virtual std::vector<std::string> Predict(const std::string& chainName, const NGram& seq) = 0;
    virtual std::string Generate(const std::string& chainName, const NGram& seq) = 0;
};

#endif