#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstdint>

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

        struct json_object;

        union json_value {
            std::string str;
            std::map<std::string, json_object> o_map;
            std::vector<json_object> vec;
            double fp_number;
            int64_t i_number;
            bool boolean;
        };

        struct json_object {
            value_type object_type;
            json_value val;

            std::string& get_string();
            std::map<std::string, json_object>& get_map();
            std::vector<json_object>& get_array();
            double get_double();
            int64_t get_int();
            bool get_bool();

            bool is_string();
            bool is_map();
            bool is_array();
            bool is_double();
            bool is_int();
            bool is_bool();
            bool is_null();
        };
    }
}