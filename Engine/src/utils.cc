#include "../include/utils.hh"
#include <algorithm>
std::vector<const char*> banned_expressions{

};

std::vector<char> safe_characters {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','z',
    '0','1','2','3','4','5','6','7','8','9'
};

bool utils::string_is_safe(const std::string &string) {

    for(char ch : string){

        if(!char_is_safe(ch))
            return false;
    }

    return true;
}
//TODO use ascii indexes instead of slow checking inside a vector
bool utils::char_is_safe(const char &ch) {
    auto it = std::find(safe_characters.begin(), safe_characters.end(), ch);

    if(it == safe_characters.end())
        return false;

    return true;
}
