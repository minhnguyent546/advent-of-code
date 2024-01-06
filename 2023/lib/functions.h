#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> str_split(const string &str, string delimiter = " ", bool remove_empty = false) {
    vector<string> subs;
    string::size_type s{0}, e{0};
    string::size_type delim_length = delimiter.length();
    while ((e = str.find(delimiter, s)) != string::npos) {
        if (e > s || remove_empty == false) {
            subs.emplace_back(str.substr(s, e - s));
        }
        s = e + delim_length;
    }
    subs.emplace_back(str.substr(s));
    return subs;
}

template<typename T = int>
vector<T> exact_numbers(const vector<string> &nums) {
    vector<T> res;
    bool use_ll = is_same<T, long long>::value;
    for (int i = 0; i < (int) nums.size(); ++i) {
        const string& str = nums[i];
        int ptr = 0;
        while (ptr < (int) str.length() && str[ptr] == ' ') ++ptr;
        if (ptr < (int) str.length() &&
            (isdigit(str[ptr]) || str[ptr] == '-')
        ) {
            res.push_back(use_ll ?
                    stoll(str.substr(ptr)) :
                    stoi(str.substr(ptr))
            );
        }
    }   
    return res;
}

string str_trim_left(const string &str) {
    int n = (int) str.length();
    int ptr = 0;
    while (ptr < n && str[ptr] == ' ') ++ptr;
    return (ptr < n ? str.substr(ptr) : "");
}

string str_trim_right(const string &str) {
   int n = (int) str.length();
   int ptr = n - 1;
   while (ptr >= 0 && str[ptr] == ' ') --ptr;
   return (ptr >= 0 ? str.substr(0, ptr + 1) : "");
}

string str_trim(const string &str) {
    return str_trim_left(str_trim_right(str));
}

template<typename InputIterator>
string join(InputIterator begin, InputIterator end, string delimiter = ",") {
    if (begin == end) {
        return string{};
    }
    ostringstream oss{};
    oss << *begin++;
    for (; begin != end; ++begin) {
        oss << delimiter << *begin;
    }
    return oss.str();
}
