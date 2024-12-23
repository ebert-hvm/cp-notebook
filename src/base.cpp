#include "cp-notebook/base.h"

string trim(const string& str) {
    auto start = find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
    });
    auto end = find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                   return !isspace(ch);
               }).base();
    return (start < end ? string(start, end) : string());
}

string normalizeLineEndings(const string& str) {
    string normalized = str;
    normalized.erase(remove(normalized.begin(), normalized.end(), '\r'), normalized.end());
    return normalized;
}