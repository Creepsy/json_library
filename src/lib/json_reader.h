#pragma once

#include <istream>

#include "json.h"

namespace json {
    namespace json_reader {
        json::json_object construct_json_from_stream(std::istream& stream);
        void remove_whitespaces(std::istream& stream);
        std::string next_string_from_stream(std::istream& stream);
        std::string next_number_from_stream(std::istream& stream, bool& is_double);

        std::istream& operator>>(std::istream& stream, json::json_object& obj);
    }
}