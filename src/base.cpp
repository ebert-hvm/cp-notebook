#include "cp-notebook/base.h"

string trim(const string& str) {
    auto end = find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                   return !isspace(ch);
               }).base();
    return string(str.begin(), end);
}