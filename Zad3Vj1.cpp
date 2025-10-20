#include <iostream>
#include <string>
#include <cctype>

int main(){
    std::string s;
    std::getline(std::cin,s);
    for(char &c:s){
        unsigned char nesto = static_cast<unsigned char>(c);
        if(std::isalpha(nesto)){
            c = static_cast<char>(std::toupper(nesto));
        }
        else if(std::isdigit(nesto)){
            c = '*';
        }
        else if (c == ' ' || c == '\t'){
            c = '_';
        }
    }
    std::cout << s << '\n';
    return 0;
}