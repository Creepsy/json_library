#include "json_object.h"

#include <system_error>

std::string& json::objects::json_object::get_string() {
    if(!this->is_string()) throw std::runtime_error("JSON object isn't a string!");
    return *(std::string*)this->data;
}

std::map<std::string, json::objects::json_object>& json::objects::json_object::get_map() {
    if(!this->is_map()) throw std::runtime_error("JSON object isn't a map!");
    return *(std::map<std::string, json::objects::json_object>*)this->data;
}

std::vector<json::objects::json_object>& json::objects::json_object::get_array() {
    if(!this->is_array()) throw std::runtime_error("JSON object isn't an array!");
    return *(std::vector<json::objects::json_object>*)this->data;
}

double& json::objects::json_object::get_double() {
    if(!this->is_double()) throw std::runtime_error("JSON object isn't a double!");
    return *(double*)this->data;
}

int64_t& json::objects::json_object::get_int() {
    if(!this->is_int()) throw std::runtime_error("JSON object isn't an int!");
    return *(int64_t*)this->data;
}

bool& json::objects::json_object::get_bool() {
    if(!this->is_bool()) throw std::runtime_error("JSON object isn't a boolean!");
    return *(bool*)this->data;
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

json::objects::json_object::json_object(value_type object_type) : data{}, object_type{object_type} {
    switch(object_type) {
        case value_type::STR:
            *(std::string*)this->data = std::string();
            break;
        case value_type::BOOL:
            *(bool*)this->data = false;
            break;
        case value_type::FP_NUM:
            *(double*)this->data = 0.0;
            break;
        case value_type::INT_NUM:
            *(int64_t*)this->data = 0;
            break;
        case value_type::MAP:
            *(std::map<std::string, json_object>*)this->data = std::map<std::string, json_object>();
            break;
        case value_type::VEC:
            *(std::vector<json_object>*)this->data = std::vector<json_object>();
            break;
        default:
            break;
    }
}