#include <string>
#include <sstream>
#include <vector>
#include "utils.hpp"

using namespace std;

// join joins vector of string and seperate with delimiter
string join(const vector<string>& tokens, string del)
{
    string res;
    for (int i = 0; i < tokens.size(); ++i) {
        if (i > 0) {
            res += del;
        }
        res += tokens[i];
    }

    return res;
}

// split returns vector of string seperate with delimiter
vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}