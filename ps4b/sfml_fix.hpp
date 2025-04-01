#pragma once
#include <string>

// Specialization for SFML's Uint32
namespace std {
    template<>
    struct char_traits<unsigned int> : public char_traits<wchar_t> {
        typedef unsigned int char_type;
    };
}
