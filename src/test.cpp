#include <iostream>
#include <sstream>

#include "lib/json.h"
#include "lib/json_builder.h"
#include "lib/json_reader.h"

int main() {
   // json::json_object object = json::json_builder::array_builder{}.with_null().with_null().with_null().with_bool(true).with_object(json::json_builder::map_builder{}.with_double("first", 2.0).with_string("second", "test").build()).build();
   
  //  std::cout << object << std::endl;

    std::stringstream stream{"[2, 3.5, 23, \" test sdfkjhsdfk 2.41\"]"};

   // std::cout << json::json_reader::construct_json_from_stream(stream) << std::endl; //TODO: add print support for const types!!!
    json::json_object obj = json::json_reader::next_object_from_stream(stream);
    std::cout << obj << std::endl;

    return 0;
}