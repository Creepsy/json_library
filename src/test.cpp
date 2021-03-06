#include <iostream>
#include <fstream>

#include "lib/json.h"
#include "lib/json_builder.h"
#include "lib/json_reader.h"

int main() {
   // json::json_object object = json::json_builder::array_builder{}.with_null().with_null().with_null().with_bool(true).with_object(json::json_builder::map_builder{}.with_double("first", 2.0).with_string("second", "test").build()).build();
   
  //  std::cout << object << std::endl;

    std::ifstream file;
    file.open("../example.json");

    if(!file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }

    json::json_object obj = json::json_reader::next_object_from_stream(file);

   /* json::json_builder::map_builder builder{};

    for(int i = 0; i < 10; i++) {
        builder = json::json_builder::map_builder{}.with_object("Turtle", builder.build());
    }*/

    /*for(int t = 0; t < obj.get_array().size(); t++) {
        if(t != 0) std::cout << "==========================" << std::endl;
        std::cout << "Name:   " << obj.get_array()[t].get_map()["name"] << std::endl; 
        std::cout << "Age:    " << obj.get_array()[t].get_map()["age"] << std::endl; 
        std::cout << "Height: " << obj.get_array()[t].get_map()["height"] << std::endl; 
    }*/
    std::cout << obj << std::endl;


    file.close();
    
    return 0;
}