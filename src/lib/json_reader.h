#pragma once

#include <istream>

#include "json.h"

namespace json {
    namespace json_reader {
        void remove_whitespaces(std::istream& stream);
        std::string next_string_from_stream(std::istream& stream);
        std::string next_number_from_stream(std::istream& stream, bool& is_double);
        json_object next_object_from_stream(std::istream& stream);
    }
}