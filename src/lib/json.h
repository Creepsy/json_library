#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <ostream>

#define DATA_SIZE std::max({sizeof(std::string), sizeof(int64_t), sizeof(std::map<std::string, json_object>), sizeof(std::vector<json_object>), sizeof(double), sizeof(bool)})

namespace json {
    enum value_type {
        STR,
        MAP,
        VEC,
        INT_NUM,
        FP_NUM,
        BOOL,
        NONE
    };

    class json_object {
        private:
            value_type object_type;
            char data[DATA_SIZE];
        
        public:
            std::string& get_string();
            std::map<std::string, json_object>& get_map();
            std::vector<json_object>& get_array();
            double& get_double();
            int64_t& get_int();
            bool& get_bool();

            bool is_string();
            bool is_map();
            bool is_array();
            bool is_double();
            bool is_int();
            bool is_bool();
            bool is_null();

            std::ostream& pretty_print(std::ostream& stream, const size_t intendation_size = 4, const bool whitespace = true, size_t intendation_count = 0);

            json_object();
            json_object(value_type object_type);
            json_object(const json_object& other);
            ~json_object();
    };

    std::ostream& operator<<(std::ostream& stream, json_object& obj);
}