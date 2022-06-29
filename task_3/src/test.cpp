#include "Cropping.hpp"

int main(){
    const std::string txt = "        Some Text     ";
    std::vector<char> text_vector = {'\t', ' ', ' ', '\t', 't', 'x', 't', '\t', '\a'};
    auto txt2 = "           Some Text     ";
    auto text_const = cropp(txt);
    cropp(text_vector);
    for(auto el: text_vector){
        std::cout << el;
    } std::cout << std::endl;
    std::cout << text_const << std::endl;
    std::cout << cropp(txt2) << std::endl;
}