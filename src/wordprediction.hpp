#ifndef WORD_PREDICTION_HPP_
#define WORD_PREDICTION_HPP_

#include <string>
#include <vector>

class WordPrediction {
    virtual void Add(const std::vector<std::string>& seq) = 0;
    virtual std::vector<std::string> Predict(std::vector<std::string> words) = 0;
    virtual std::string Generate(std::vector<std::string> words) = 0;
    virtual bool Load() = 0;
};

#endif