#include <iostream>
#include "markov.hpp"

using namespace std;

void MarkovChain::Add(const std::string& chainName, const NGram& seq) {
    Chain chain(order);
    if (chains.find(chainName) == chains.end()) {
        chains.insert(pair<string, Chain>(chainName, chain));
    }
    chain.Add(seq);
    chains.at("t").print();
}

string MarkovChain::Generate(const string& chainName, const NGram& seq) {
    map<string, Chain>::iterator it;
    for (it = chains.begin(); it != chains.end(); ++it) {
        cout << "Key: " << it->first << " " << chainName << endl;
        it->second.print();
    }
    /*auto chain = chains["t"];
    chain.print();
    if (chains.find(chainName) == chains.end()) {
        return "";
    }
    chain = chains.at(chainName);
    chain.print();
    return chain.Generate(seq);*/
    return "test";
}

vector<string> MarkovChain::Predict(const string& chainName, const NGram& seq) {
    vector<string> vec;
    return vec;
}