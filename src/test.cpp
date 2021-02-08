#include <iostream>

#include "lib/json_object.h"

int main() {
    json::objects::json_object object{json::objects::value_type::VEC};

    object.get_array().push_back(json::objects::json_object{json::objects::value_type::INT_NUM});
    object.get_array().at(0).get_int() = 10;

    std::cout << object.get_array().at(0).get_int() << std::endl;

    return 0;
}