#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>

// fill(token, n) returns a array of length n filled with the token
template<typename T>
std::vector<T> fill(T value, int count)
{
    std::vector<T> arr(count);

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = value;
    }

    return arr;
}

// join returns string
std::string join(const std::vector<std::string>& tokens, std::string del);
// split returns vector
std::vector<std::string> split(std::string str, char delimiter);

#endif