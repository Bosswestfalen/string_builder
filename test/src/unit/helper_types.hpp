#ifndef BOSSWESTFALEN_UNIT_TEST_HELPER_TYPES_HPP
#define BOSSWESTFALEN_UNIT_TEST_HELPER_TYPES_HPP

#include <ostream>

namespace test_type
{
struct has_operator_string final
{
    operator std::string() const
    {
        return "operator_to_string";
    }
};


struct has_external_to_string final
{
};

std::string to_string(has_external_to_string const&)
{
    return "external_to_string";
}


struct has_operator_ll final
{
};

std::ostream& operator<<(std::ostream& o, has_operator_ll const&)
{
    o << "stream";
    return o;
}


struct convertible_to_int final
{
    operator int() const
    {
        return 1234;
    }
};


struct has_explicit_operator_string final
{
    explicit operator std::string() const
    {
        return "explicit_operator_string";
    }
};

}

#endif

