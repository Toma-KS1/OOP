#include <iostream>
#include <string>
#include <cctype>

std::string word_to_pig_latin(const std::string& word) {
    if (word.empty()) {
        return "";
    }
    
    char prvi_znak = std::tolower(word[0]);
    bool pocinje_sa_samoglasnikom = (prvi_znak == 'a' || prvi_znak == 'e' || 
                              prvi_znak == 'i' || prvi_znak == 'o' || 
                              prvi_znak == 'u');

    if (pocinje_sa_samoglasnikom) {
        return word + "hay";
    } else {
        if (word.length() == 1) {
            return word + "ay";
        }
        return word.substr(1) + word[0] + "ay";
    }
}

int main() {
    std::cout << "apple -> " << word_to_pig_latin("apple") << std::endl;
    std::cout << "hello -> " << word_to_pig_latin("hello") << std::endl;
    
    return 0;
}