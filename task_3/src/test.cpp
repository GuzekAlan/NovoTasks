#include "Cropping.hpp"

int main(){
    const std::string txt = "  \t  \n  Some Text.   \n \t  ";
    std::vector<char> text_vector = {'\t', ' ', ' ', '\t', 't', 'x', 't', '.', '\t', '\a'};
    auto txt2 = "  \n \t     Some Text. \t  \n \n";
    auto text_const = cropp(txt);
    cropp(text_vector);
    for(auto el: text_vector){
        std::cout << el;
    } std::cout << std::endl;
    std::cout << text_const << std::endl;
    std::cout << cropp(txt2) << std::endl;
}