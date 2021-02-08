#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

#define DATA_SIZE std::max({sizeof(std::string), sizeof(int64_t), sizeof(std::map<std::string, json_object>), sizeof(std::vector<json_object>), sizeof(double), sizeof(bool)})

namespace json {
    namespace objects {
        enum value_type {
            STR,
            MAP,
            VEC,
            INT_NUM,
            FP_NUM,
            BOOL,
            NONE
        };

        struct json_object {
            const value_type object_type;
            char data[DATA_SIZE];

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

            json_object(value_type object_type);
        };
    }
}