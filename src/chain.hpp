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

class MarkovChain
{
private:
    uint8_t Order;
    std::map<std::string, int> stateMap;
    std::map<int, SparseArray> freqMat;
    std::map<int, std::string> intMap;
public:
    MarkovChain(uint8_t ord) : Order(ord) {}
    ~MarkovChain() {}
    void Add(const std::vector<std::string>& seq);
    void PrintState();
    void PrintFreq();
    void PrintIntMap();
    std::string Generate(NGram current);
protected:
    int AddState(std::string str);
};

MarkovChain* NewChain(uint8_t order);

std::vector<Pair> MakePairs(const std::vector<std::string>& tokens, const size_t order);

#endif