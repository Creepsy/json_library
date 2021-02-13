#pragma once

#include <cstdint>

#include "json.h"

namespace json {
    namespace json_builder {
        class map_builder {
            private:
                json_object obj;
            public:
                map_builder();

                map_builder& with_object(const std::string& key, const json_object& obj);
                map_builder& with_int(const std::string& key, const int64_t value);
                map_builder& with_string(const std::string& key, const std::string& str);
                map_builder& with_bool(const std::string& key, const bool value);
                map_builder& with_double(const std::string& key, const double value);
                map_builder& with_null(const std::string& key);
                
                const json_object& build();

                ~map_builder() = default;
        };

        class array_builder {
            private:
                json_object obj;
            public:
                array_builder();

                array_builder& with_object(const json_object& obj);
                array_builder& with_int(const int64_t value);
                array_builder& with_string(const std::string& str);
                array_builder& with_bool(const bool value);
                array_builder& with_double(const double value);
                array_builder& with_null();

                const json_object& build();

                ~array_builder() = default;
        };
    }
}