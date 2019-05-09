#ifndef WORD_PREDICTION_HPP_
#define WORD_PREDICTION_HPP_

#include <string>
#include <vector>

typedef std::vector<std::string> NGram;

// WordPrediction abstract class for word prediction
class WordPrediction {
    public:
        WordPrediction() {}
        ~WordPrediction() {}
        virtual void Add(const NGram& seq) = 0;
        virtual std::string Generate(const NGram& seq) = 0;
};

#endif