#include <iostream>

#include "lib/json.h"

int main() {
    json::json_object object{json::value_type::VEC};

    object.get_array().push_back(json::json_object{json::value_type::INT_NUM});
    object.get_array().at(0).get_int() = 10;

  //  std::cout << object << std::endl;

    return 0;
}