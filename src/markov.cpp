#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "chain.hpp"
#include "utils.hpp"

using namespace std;

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
    for (int k = this->Order; k > 0; --k) {
        vector<Pair> pairs = MakePairs(seq, k);
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
    //vector<Pair> pairs = MakePairs(seq, this->Order);
    //for (int i = 0; i < pairs.size(); i++) {
    //    Pair pair = pairs[i];
    //    int currentIndex = this->AddState(join(pair.CurrentState, "_"));
    //    int nextIndex = this->AddState(pair.NextState);
    //    if (this->freqMat.find(currentIndex) == this->freqMat.end()) {
    //        SparseArray temp;
    //        temp.insert(make_pair(nextIndex, 0));
    //        this->freqMat.insert(make_pair(currentIndex, temp));
    //    }
    //    this->freqMat[currentIndex][nextIndex]++;
    //}
}

string MarkovChain::Generate(NGram current)
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

void MarkovChain::PrintState()
{
    map<string, int>::iterator it;
    for (it = this->stateMap.begin(); it != this->stateMap.end(); ++it) {
        cout << it->first << ":" << it->second << endl;
    }
}

void MarkovChain::PrintIntMap()
{
    map<int, string>::iterator it;
    for (it = this->intMap.begin(); it != this->intMap.end(); ++it) {
        cout << it->first << ":" << it->second << endl;
    }
}

void MarkovChain::PrintFreq()
{
    map<int, SparseArray>::iterator it;
    map<int, int>::iterator ik;
    for (it = this->freqMat.begin(); it != this->freqMat.end(); ++it) {
        cout << it->first << " ";
        for (ik = it->second.begin(); ik != it->second.end(); ++ik) {
            cout << ik->first << ":" << ik->second << " ";
        }
        cout << endl;
    }
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

MarkovChain* NewChain(uint8_t order)
{
    return new MarkovChain(order);
}

// Experiment
void ngram(int n, vector<string>& vec)
{
    uint16_t size = vec.size();

    for (int i = 0; i < size - n + 1; ++i) {
        for (int j = i; j < i+n; ++j) {
            cout << vec[j];
        }
        cout << endl;
    }
}