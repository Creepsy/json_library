#include "json.h"

#include <system_error>

std::string& json::json_object::get_string() {
    if(!this->is_string()) throw std::runtime_error("JSON object isn't a string!");
    return *(std::string*)this->data;
}

std::map<std::string, json::json_object>& json::json_object::get_map() {
    if(!this->is_map()) throw std::runtime_error("JSON object isn't a map!");
    return *(std::map<std::string, json::json_object>*)this->data;
}

std::vector<json::json_object>& json::json_object::get_array() {
    if(!this->is_array()) throw std::runtime_error("JSON object isn't an array!");
    return *(std::vector<json::json_object>*)this->data;
}

double& json::json_object::get_double() {
    if(!this->is_double()) throw std::runtime_error("JSON object isn't a double!");
    return *(double*)this->data;
}

int64_t& json::json_object::get_int() {
    if(!this->is_int()) throw std::runtime_error("JSON object isn't an int!");
    return *(int64_t*)this->data;
}

bool& json::json_object::get_bool() {
    if(!this->is_bool()) throw std::runtime_error("JSON object isn't a boolean!");
    return *(bool*)this->data;
}

bool json::json_object::is_string() {
    return this->object_type == value_type::STR;
}

bool json::json_object::is_map() {
    return this->object_type == value_type::MAP;
}

bool json::json_object::is_array() {
    return this->object_type == value_type::VEC;
}

bool json::json_object::is_double() {
    return this->object_type == value_type::FP_NUM;
}

bool json::json_object::is_int() {
    return this->object_type == value_type::INT_NUM;
}

bool json::json_object::is_bool() {
    return this->object_type == value_type::BOOL;
}

bool json::json_object::is_null() {
    return this->object_type == value_type::NONE;
}

json::json_object::json_object(value_type object_type) : data{}, object_type{object_type} {
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

std::ostream& json::operator<<(std::ostream& stream, json_object& obj) {
    switch(obj.object_type) {
        case value_type::STR:
            return stream << '"' << obj.get_string() << '"';
        case value_type::BOOL:
            return stream << (obj.get_bool() ? "true" : "false");
        case value_type::FP_NUM:
            return stream << obj.get_double();
        case value_type::INT_NUM:
            return stream << obj.get_int();
        case value_type::MAP:
            stream << "{";
            {
                size_t pos = 0;
                for(std::pair<const std::string, json_object>& sub_obj : obj.get_map()) {
                    if(pos != 0) stream << ", ";
                    stream << '"' << sub_obj.first << '"' << " : " << sub_obj.second;
                   pos++;
                }    
            }
            return stream << "}";
        case value_type::VEC:
            stream << "[";
            for(size_t i = 0; i < obj.get_array().size(); i++) {
                if(i != 0) stream << ", ";
                stream << obj.get_array().at(i);
            }
            return stream << "]";
        case value_type::NONE:
            return stream << "null";
    }

    return stream;
}