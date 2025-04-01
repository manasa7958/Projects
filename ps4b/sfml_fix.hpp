// Copyright Manasa Praveen 2025
#pragma once
#include <string>

namespace std {
template<>
struct char_traits<unsigned int> : public char_traits<wchar_t> {
    typedef unsigned int char_type;
};
}
