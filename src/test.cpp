#include <iostream>
#include <sstream>

#include "lib/json.h"
#include "lib/json_builder.h"
#include "lib/json_reader.h"

int main() {
    json::json_object object = json::json_builder::array_builder{}.with_null().with_null().with_null().with_bool(true).with_object(json::json_builder::map_builder{}.with_double("first", 2.0).with_string("second", "test").build()).build();
   
    std::cout << object << std::endl;

    std::stringstream stream{"  6  \n  \t \"test}\""};
    bool b = false;
    std::cout << json::json_reader::next_number_from_stream(stream, b) << ", " << json::json_reader::next_string_from_stream(stream) << std::endl;
    std::cout << "is_double: " << b << std::endl;

    return 0;
}