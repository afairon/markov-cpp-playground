#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <string>
#include <map>
#include <vector>

typedef std::map<int, int> SparseArray;
typedef std::vector<std::string> NGram;

const std::string StartToken = "^";
const std::string EndToken = "$";

// Pair is a current state and next state structure
struct Pair
{
    NGram CurrentState;
    std::string NextState;
};

class Chain
{
private:
    uint8_t Order;
    std::map<std::string, int> stateMap;
    std::map<int, SparseArray> freqMat;
    std::map<int, std::string> intMap;
public:
    Chain(uint8_t ord) : Order(ord) {}
    ~Chain() {}
    void Add(const std::vector<std::string>& seq);
    std::string Generate(NGram current);
    void print();
protected:
    int AddState(std::string str);
};

std::vector<Pair> MakePairs(const std::vector<std::string>& tokens, const size_t order);

#endif