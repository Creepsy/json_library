#include "json_reader.h"

#include <iostream>

#include "json_builder.h"

void json::json_reader::remove_whitespaces(std::istream& stream) {
    char curr = stream.get();
    while(std::iswspace(curr) && stream.good()) {
        curr = stream.get();
    }

    if(stream.good()) stream.seekg(-1, std::ios::cur);
}

std::string json::json_reader::next_string_from_stream(std::istream& stream) {
    remove_whitespaces(stream);
    char curr = stream.get();

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing string!");
    if(curr != '"') throw std::runtime_error("Missing \" at the start of the string!");

    std::string str;

    do {
        curr = stream.get();

        if(curr == '\\') {
            str += curr;
            str += stream.get();
        } else if(curr != '"') {
            str += curr;
        }
    } while(curr != '"' && stream.good());

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing string!");

    return str;
}

std::string json::json_reader::next_number_from_stream(std::istream& stream, bool& is_double) {
    remove_whitespaces(stream);
    char curr = stream.get();

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing number!");

    std::string num;
    is_double = false;

    while((std::isdigit(curr) || curr == '.' || curr == '+' || curr == '-' || curr == 'e' || curr == 'E') && stream.good()) {
        if(curr == '.' || curr == 'e' || curr == 'E') {
            if(is_double) throw std::runtime_error("Invalid number format!");
            is_double = true;

        }
        num += curr;
        curr = stream.get();
    }

    if(stream.good()) stream.seekg(-1, std::ios::cur);

    return num;
}

json::json_object json::json_reader::next_object_from_stream(std::istream& stream) {
    remove_whitespaces(stream);
    char first = stream.get();

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing json object!");
    stream.seekg(-1, std::ios::cur);

    if(first == '.' || first == '+' || first == '-' || std::isdigit(first)) {
        bool is_double = false;
        std::string num = next_number_from_stream(stream, is_double);

        if(is_double) {
            json_object obj = json_object{value_type::FP_NUM};
            obj.get_double() = std::stod(num);

            return obj;
        } else {
            json_object obj = json_object{value_type::INT_NUM};
            obj.get_int() = std::stoll(num);

            return obj;
        }
    } else if(first == '"') {
        std::string str = next_string_from_stream(stream);
        json_object obj = json_object{value_type::STR};
        obj.get_string() = str;
        return obj;
    } else if(first == '[') {
        stream.get();
        json_builder::array_builder builder{};

        char next = stream.get();
        stream.seekg(-1, std::ios::cur);

        if(next == ']') {
            stream.get();
            return builder.build();
        }

        while(true) {
            try {
                json_object member = next_object_from_stream(stream);
                builder.with_object(member);
            } catch(std::exception& e) {
                break;
            }

            remove_whitespaces(stream);
            if(stream.get() != ',') {
                stream.seekg(-1, std::ios::cur);
                break;
            }
        }

        //remove_whitespaces(stream);
        next = stream.get();
      //  std::cout << next << std::endl;
        if(next != ']') throw std::runtime_error("Expected ] while parsing array!");

        return builder.build();
    } else if(first == '{') {
        stream.get();
        json_builder::map_builder builder{};

        char next = stream.get();
        stream.seekg(-1, std::ios::cur);

        if(next == '}') {
            stream.get();
            return builder.build();
        }

        while(true) {
            json_object key, value;
            try {
                key = next_object_from_stream(stream);
            } catch(std::exception& e) {
                break;
            }   
            remove_whitespaces(stream);
            if(stream.get() != ':') throw std::runtime_error("Expected : while parsing map pair!");
            try {
                value = next_object_from_stream(stream);
            } catch(std::exception& e) {
                break;
            }
            builder.with_object(key.get_string(), value);

            remove_whitespaces(stream);
            if(stream.get() != ',') {
                stream.seekg(-1, std::ios::cur);
                break;
            }
        }
        
       // remove_whitespaces(stream);
        next = stream.get();
        if(next != '}') throw std::runtime_error("Expected } while parsing map!");

        return builder.build();
    } else if(std::isalpha(first)) {
        std::string identifier;
        for(int i = 0; i < 4; i++) {
            identifier += stream.get();
        }

        if(stream.fail()) throw std::runtime_error("EOF while parsing identifier!");

        if(identifier == "null") {
            return json_object{value_type::NONE};
        } else {    
            if(identifier == "true") {
                json_object obj{value_type::BOOL};
                obj.get_bool() = true;
                return obj;
            } else if(identifier == "fals" && stream.get() == 'e') {
                json_object obj{value_type::BOOL};
                obj.get_bool() = false;
                return obj;
            }
        }
    }

    throw std::runtime_error("No valid json object!");
}