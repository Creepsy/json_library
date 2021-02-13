#include "json_builder.h"

json::json_builder::map_builder::map_builder() : obj{value_type::MAP} {
}

json::json_builder::map_builder& json::json_builder::map_builder::with_object(const std::string& key, const json_object& obj) {
    this->obj.get_map()[key] = obj;
    return *this;
}

json::json_builder::map_builder& json::json_builder::map_builder::with_int(const std::string& key, const int64_t value) {
    this->obj.get_map()[key] = json_object{value_type::INT_NUM};
    this->obj.get_map()[key].get_int() = value;
    return *this;
}

json::json_builder::map_builder& json::json_builder::map_builder::with_string(const std::string& key, const std::string& str) {
    this->obj.get_map()[key] = json_object{value_type::STR};
    new(&this->obj.get_map()[key].get_string()) std::string(str);
    return *this;
}

json::json_builder::map_builder& json::json_builder::map_builder::with_bool(const std::string& key, const bool value) {
    this->obj.get_map()[key] = json_object{value_type::BOOL};
    this->obj.get_map()[key].get_bool() = value;
    return *this;
}

json::json_builder::map_builder& json::json_builder::map_builder::with_double(const std::string& key, const double value) {
    this->obj.get_map()[key] = json_object{value_type::FP_NUM};
    this->obj.get_map()[key].get_double() = value;
    return *this;
}

json::json_builder::map_builder& json::json_builder::map_builder::with_null(const std::string& key) {
    this->obj.get_map()[key] = json_object{value_type::NONE};
    return *this;
}

const json::json_object& json::json_builder::map_builder::build() {
    return this->obj;
}


json::json_builder::array_builder::array_builder() : obj{value_type::VEC} {
}

json::json_builder::array_builder& json::json_builder::array_builder::with_object(const json_object& obj) {
    this->obj.get_array().push_back(obj);
    return *this;
}


json::json_builder::array_builder& json::json_builder::array_builder::with_int(const int64_t value) {
    this->obj.get_array().push_back(json_object{value_type::INT_NUM});
    this->obj.get_array().back().get_int() = value;
    return *this;
}

json::json_builder::array_builder& json::json_builder::array_builder::with_string(const std::string& str) {
    this->obj.get_array().push_back(json_object{value_type::STR});
    this->obj.get_array().back().get_string() = str;
    return *this;
}

json::json_builder::array_builder& json::json_builder::array_builder::with_bool(const bool value) {
    this->obj.get_array().push_back(json_object{value_type::BOOL});
    this->obj.get_array().back().get_bool() = value;
    return *this;
}

json::json_builder::array_builder& json::json_builder::array_builder::with_double(const double value) {
    this->obj.get_array().push_back(json_object{value_type::FP_NUM});
    this->obj.get_array().back().get_double() = value;
    return *this;
}

json::json_builder::array_builder& json::json_builder::array_builder::with_null() {
    this->obj.get_array().push_back(json_object{value_type::NONE});
    return *this;
}

const json::json_object& json::json_builder::array_builder::build() {
    return this->obj;
}