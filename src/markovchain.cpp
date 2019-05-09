#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

#include "markovchain.hpp"
#include "utils.hpp"

using namespace std;

// AddState add state to chain
int MarkovChain::AddState(string str)
{
    int index;

    if (this->stateMap.find(str) != this->stateMap.end()) {
        return this->stateMap[str];
    }

    index = this->stateMap.size();
    this->stateMap.insert(make_pair(str, index));
    this->intMap.insert(make_pair(index, str));

    return index;
}

// Add create a map spool
void MarkovChain::Add(const vector<string>& seq)
{
    for (int k = Order; k > 0; --k) {
        vector<string> tokens;
        vector<string> startTokens = fill<string>(StartToken, k);
        vector<string> endTokens = fill<string>(EndToken, k);
        tokens.insert(tokens.end(), startTokens.begin(), startTokens.end());
        tokens.insert(tokens.end(), seq.begin(), seq.end());
        tokens.insert(tokens.end(), endTokens.begin(), endTokens.end());
        vector<Pair> pairs = MakePairs(tokens, k);
        for (int i = 0; i < pairs.size(); i++) {
            Pair pair = pairs[i];
            int currentIndex = this->AddState(join(pair.CurrentState, "_"));
            int nextIndex = this->AddState(pair.NextState);
            if (this->freqMat.find(currentIndex) == this->freqMat.end()) {
                SparseArray temp;
                temp.insert(make_pair(nextIndex, 0));
                this->freqMat.insert(make_pair(currentIndex, temp));
            }
            this->freqMat[currentIndex][nextIndex]++;
        }
    }
}

// Generate returns predicted word
string MarkovChain::Generate(const NGram& current)
{
    if (this->stateMap.find(join(current, "_")) == this->stateMap.end()) {
        return "";
    }
    int currentIndex = this->stateMap[join(current, "_")];

    if (this->freqMat.find(currentIndex) == this->freqMat.end()) {
        return "";
    }

    SparseArray arr = this->freqMat[currentIndex];

    auto it = arr.begin();
    advance(it, rand() % arr.size());
    for (; it != arr.end(); ++it) {
        return this->intMap[it->first];
    }

    return "";
}

// MakePairs returns a vector of Pair consisting of CurrentState and a NextState
vector<Pair> MakePairs(const vector<string>& tokens, const size_t order)
{
    vector<Pair> pairs;

    // Determine NGram size
    size_t size = 0;
    if (order < tokens.size()) {
        size = -order + tokens.size();
    }

    for (int i = 0; i < size; ++i) {

        // create temporary vector to store current state
        vector<string> currentState(order);
        for (int j = 0; j < order; ++j) {
            currentState[j] = tokens[i+j];
        }

        string nextState = tokens[i+order];

        Pair pair{
            currentState,
            nextState
        };

        pairs.push_back(pair);
    }

    return pairs;
}

// Read read file and add chain
void MarkovChain::Read(const string& filepath) {
    string line;
    vector<string> tokens;
    ifstream fs(filepath);

    if (fs.fail()) {
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        tokens = split(line, ' ');
        Add(tokens);
    }
    fs.close();
}