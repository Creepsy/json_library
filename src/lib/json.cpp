#include "json.h"

#include <system_error>

//private helper functions

std::ostream& write_intendations(std::ostream& stream, const size_t intendation_count, const size_t intendation_size) {
    for(size_t i = 0; i < intendation_count * intendation_size; i++) {
        stream << ' ';
    }
    return stream;
}

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

std::ostream& json::json_object::pretty_print(std::ostream& stream, const size_t intendation_size, const bool whitespace, size_t intendation_count) {
    switch(this->object_type) {
        case json::value_type::STR:
            return stream << '"' << this->get_string() << '"';
        case json::value_type::BOOL:
            return stream << (this->get_bool() ? "true" : "false");
        case json::value_type::FP_NUM:
            return stream << this->get_double();
        case json::value_type::INT_NUM:
            return stream << this->get_int();
        case json::value_type::MAP:
            stream << "{";
            if(whitespace) stream << std::endl;
            {
                size_t pos = 0;
                for(std::pair<const std::string, json::json_object>& sub_obj : this->get_map()) {
                    if(pos != 0) {
                        stream << ", ";
                        if(whitespace) stream << std::endl;
                    }

                    if(whitespace) write_intendations(stream, intendation_count + 1, intendation_size);
                    stream << '"' << sub_obj.first << '"' << ": ";
                    sub_obj.second.pretty_print(stream, intendation_size, whitespace, intendation_count + 1);
                    pos++;
                }    
            }
            if(whitespace) {
                stream << std::endl;
                write_intendations(stream, intendation_count, intendation_size);
            } 
            return stream << "}";
        case json::value_type::VEC:
            stream << "[";
            if(whitespace) stream << std::endl;
            for(size_t i = 0; i < this->get_array().size(); i++) {
                if(i != 0) {
                    stream << ", ";
                    if(whitespace) stream << std::endl;
                }
                if(whitespace) write_intendations(stream, intendation_count + 1, intendation_size);
                this->get_array().at(i).pretty_print(stream, intendation_size, whitespace, intendation_count + 1);
            }
            if(whitespace) {
                stream << std::endl;
                write_intendations(stream, intendation_count, intendation_size);
            }
            return stream << "]";
        case json::value_type::NONE:
            return stream << "null";
    }

    return stream;
}

json::json_object::json_object() : data{}, object_type{value_type::NONE} {

}

json::json_object::json_object(value_type object_type) : data{}, object_type{object_type} {
    switch(object_type) {
        case value_type::STR:
            new(this->data) std::string;
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
            //*(std::map<std::string, json_object>*)this->data = std::map<std::string, json_object>();
            new(this->data)std::map<std::string, json_object>;
            break;
        case value_type::VEC:
            //*(std::vector<json_object>*)this->data = std::vector<json_object>();
            new(this->data)std::vector<json_object>;
            break;
        default:
            break;
    }
}

json::json_object::json_object(const json_object& other) : data{}, object_type{other.object_type} {
    switch(object_type) {
        case value_type::STR:
            new(this->data)std::string((*(std::string*)other.data));
            break;
        case value_type::BOOL:
            *(bool*)this->data = *(bool*)other.data;
            break;
        case value_type::FP_NUM:
            *(double*)this->data = *(double*)other.data;
            break;
        case value_type::INT_NUM:
            *(int64_t*)this->data = *(int64_t*)other.data;
            break;
        case value_type::MAP:
            //*(std::map<std::string, json_object>*)this->data = *(std::map<std::string, json_object>*)other.data;
            new(this->data)std::map<std::string, json_object>(*(std::map<std::string, json_object>*)other.data);
            break;
        case value_type::VEC:
           // *(std::vector<json_object>*)this->data = *(std::vector<json_object>*)other.data;
            new(this->data)std::vector<json_object>(*(std::vector<json_object>*)other.data);
            break;
        default:
            break;
    }
}

json::json_object::json_object(json_object&& other) {
    this->object_type = other.object_type;
    switch(object_type) {
        case value_type::STR:
            new(this->data)std::string((*(std::string*)other.data));
            new(other.data)std::string();
            break;
        case value_type::BOOL:
            *(bool*)this->data = *(bool*)other.data;
            break;
        case value_type::FP_NUM:
            *(double*)this->data = *(double*)other.data;
            break;
        case value_type::INT_NUM:
            *(int64_t*)this->data = *(int64_t*)other.data;
            break;
        case value_type::MAP:
            new(this->data)std::map<std::string, json_object>(*(std::map<std::string, json_object>*)other.data);
            new(other.data)std::map<std::string, json_object>();
            break;
        case value_type::VEC:
            new(this->data)std::vector<json_object>(*(std::vector<json_object>*)other.data);
            new(other.data)std::vector<json_object>();
            break;
        default:
            break;
    }
}

json::json_object::~json_object() {
    switch(object_type) {
        case value_type::STR:
            (*(std::string*)this->data).~basic_string();
            break;
        case value_type::MAP:
            (*(std::map<std::string, json_object>*)this->data).~map();
            break;
        case value_type::VEC:
            (*(std::vector<json_object>*)this->data).~vector();
            break;
        default:
            break;
    }
}

void json::json_object::operator=(const json_object& other) {
    this->object_type = other.object_type;
    switch(object_type) {
        case value_type::STR:
            new(this->data)std::string((*(std::string*)other.data));
            break;
        case value_type::BOOL:
            *(bool*)this->data = *(bool*)other.data;
            break;
        case value_type::FP_NUM:
            *(double*)this->data = *(double*)other.data;
            break;
        case value_type::INT_NUM:
            *(int64_t*)this->data = *(int64_t*)other.data;
            break;
        case value_type::MAP:
            new(this->data)std::map<std::string, json_object>(*(std::map<std::string, json_object>*)other.data);
            break;
        case value_type::VEC:
            new(this->data)std::vector<json_object>(*(std::vector<json_object>*)other.data);
            break;
        default:
            break;
    }
}

std::ostream& json::operator<<(std::ostream& stream, json_object& obj) {
    return obj.pretty_print(stream);
}