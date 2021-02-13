#include <iostream>

#include "lib/json.h"
#include "lib/json_builder.h"

int main() {
    json::json_object object = json::json_builder::array_builder{}.with_null().with_null().with_null().with_bool(true).with_object(json::json_builder::map_builder{}.with_double("first", 2.0).with_string("second", "test").build()).build();
   
    std::cout << object << std::endl;

    return 0;
}