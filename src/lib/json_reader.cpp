#include "json_reader.h"

#include <iostream>

json::json_object json::json_reader::construct_json_from_stream(std::istream& stream) {
    return json_object{value_type::NONE};
}

void json::json_reader::remove_whitespaces(std::istream& stream) {
    char curr = stream.get();
    while(std::iswspace(curr) && stream.good()) {
        curr = stream.get();
    }

    if(stream.good()) stream.seekg(-1, std::ios::cur);
}

std::string json::json_reader::next_string_from_stream(std::istream& stream) {
    char curr;
    std::string str;

    remove_whitespaces(stream);
    curr = stream.get();

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing string!");
    if(curr != '"') throw std::runtime_error("Missing \" at the start of the string!");

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

//TODO: support for 4.2E+1
std::string json::json_reader::next_number_from_stream(std::istream& stream, bool& is_double) {
    char curr;
    std::string num;
    is_double = false;

    remove_whitespaces(stream);
    curr = stream.get();

    if(stream.fail()) throw std::runtime_error("Reached EOF while parsing number!");

    while((std::isdigit(curr) || curr == '.') && stream.good()) {
        if(curr == '.') {
            if(is_double) throw std::runtime_error("Invalid number format!");
            is_double = true;

        }
        num += curr;
        curr = stream.get();
    }

    if(stream.good()) stream.seekg(-1, std::ios::cur);

    return num;
}


std::istream& json::json_reader::operator>>(std::istream& stream, json::json_object& obj) {
    obj = construct_json_from_stream(stream);
    return stream;
}