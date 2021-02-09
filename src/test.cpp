#include <iostream>

#include "lib/json.h"

int main() {
    json::json_object object{json::value_type::MAP};

    object.get_map().insert(std::make_pair("outer", json::json_object{json::value_type::VEC}));
    for(int v = 0; v < 3; v++) {
        object.get_map().at("outer").get_array().push_back(json::json_object{json::value_type::VEC});
        for(int i = 0; i < 10; i++) {
            object.get_map().at("outer").get_array().at(v).get_array().push_back(json::json_object{json::value_type::INT_NUM});
            object.get_map().at("outer").get_array().at(v).get_array().at(i).get_int() = i;
        }
    }
    object.get_map().insert(std::make_pair("is_true", json::json_object{json::value_type::BOOL}));

    std::cout << object << std::endl;

    return 0;
}