#pragma once
#include <string>

struct Tag{
    std::string name;
    Tag(const std::string _name) : name(_name){}
    Tag() = default;
    Tag(const Tag&) = default;
}
