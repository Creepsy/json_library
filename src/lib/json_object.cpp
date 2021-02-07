#include "json_object.h"

#include <system_error>

json::objects::json_value::~json_value() {

}

std::string& json::objects::json_object::get_string() {
    if(this->object_type != value_type::STR) throw std::runtime_error("JSON object isn't a string!");
    return this->val.str;
}

std::map<std::string, json::objects::json_object>& json::objects::json_object::get_map() {
    if(this->object_type != value_type::MAP) throw std::runtime_error("JSON object isn't a map!");
    return this->val.o_map;
}

std::vector<json::objects::json_object>& json::objects::json_object::get_array() {
    if(this->object_type != value_type::VEC) throw std::runtime_error("JSON object isn't an array!");
    return this->val.vec;
}

double json::objects::json_object::get_double() {
    if(this->object_type != value_type::FP_NUM) throw std::runtime_error("JSON object isn't a double!");
    return this->val.fp_number;
}

int64_t json::objects::json_object::get_int() {
    if(this->object_type != value_type::INT_NUM) throw std::runtime_error("JSON object isn't an int!");
    return this->val.i_number;
}

bool json::objects::json_object::get_bool() {
    if(this->object_type != value_type::BOOL) throw std::runtime_error("JSON object isn't a boolean!");
    return this->val.boolean;
}

bool json::objects::json_object::is_string() {
    return this->object_type == value_type::STR;
}

bool json::objects::json_object::is_map() {
    return this->object_type == value_type::MAP;
}

bool json::objects::json_object::is_array() {
    return this->object_type == value_type::VEC;
}

bool json::objects::json_object::is_double() {
    return this->object_type == value_type::FP_NUM;
}

bool json::objects::json_object::is_int() {
    return this->object_type == value_type::INT_NUM;
}

bool json::objects::json_object::is_bool() {
    return this->object_type == value_type::BOOL;
}

bool json::objects::json_object::is_null() {
    return this->object_type == value_type::NONE;
}

json::objects::json_object::~json_object() {
    switch (this->object_type) {
        case value_type::MAP:
            this->val.o_map.~map();
            break;
        case value_type::STR:
            this->val.str.~basic_string();
            break;
        case value_type::VEC:
            this->val.vec.~vector();
            break;
        default:
            break;
    }
    
}