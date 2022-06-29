#include <iostream>
#include <cwctype>
#include <algorithm>
#include <string>
#include <vector>

template<typename T>
T __cropp(const T& to_crop){
    auto begin = std::begin(to_crop);
    auto end = std::end(to_crop) -1;
    while(std::iswspace(*begin)) begin++;
    while(std::iswspace(*end)) end--;
    return T(begin, end+1);
}

template<typename T>
void cropp(T& text){
   text = __cropp<T>(text);
}

template<typename T>
T cropp(const T& text){
    return __cropp<T>(text);
}

std::string cropp(const char* text){
    std::string r(text);
    return __cropp<std::string>(r);
}


