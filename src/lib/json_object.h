#pragma once

#include <map>
#include <vector>
#include <string>

enum value_type {
    STR,
    MAP,
    VEC,
    NUM,
    BOOL,
    NONE
};

union json_value {
    std::string str;
    std::map<std::string, json_value> map;
    std::vector<json_value> vec;
    double num;
    bool boolean;
};

struct json_object {
    value_type object_type;
    json_value val;
};