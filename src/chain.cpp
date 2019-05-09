#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include "chain.hpp"
#include "utils.hpp"

using namespace std;

int Chain::AddState(string str)
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
void Chain::Add(const vector<string>& seq)
{
    vector<Pair> pairs = MakePairs(seq, this->Order);
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

string Chain::Generate(NGram current)
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

void Chain::print() {
    map<string, int>::iterator it;
    for (it = stateMap.begin(); it != stateMap.end(); ++it) {
        cout << it->first << endl;
    }
}