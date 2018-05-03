#include <catch.hpp>
#include <utility>
#include <ostream>
#include <string>
#include <string_builder.hpp>
#include "helper_types.hpp"


TEST_CASE("conversion")
{
    SECTION("strings")
    {
        std::string cat{"cat"};
        CHECK(cat == bosswestfalen::make_string(cat));
        CHECK(cat == bosswestfalen::make_string(std::as_const(cat)));
        CHECK(cat == bosswestfalen::make_string("cat"));
        CHECK(std::string{"cat"} == bosswestfalen::make_string(std::move(cat)));

        test_type::has_operator_string x;
        CHECK(std::string{"operator_to_string"} == bosswestfalen::make_string(x));

        test_type::has_external_to_string y;
        CHECK(std::string{"external_to_string"} == bosswestfalen::make_string(y));

        test_type::has_explicit_operator_string z;
        CHECK(std::string{"explicit_operator_string"} == bosswestfalen::make_string(z));
    }

    SECTION("c-style char pointer")
    {
        std::string dog{"dog"};
        char const* ptr{dog.c_str()};
        CHECK(dog == bosswestfalen::make_string(ptr));
        CHECK(dog == bosswestfalen::make_string(std::string{"dog"}.c_str()));
    }

    SECTION("c-style char array")
    {
        CHECK("fish" == bosswestfalen::make_string("fish"));
    }

    SECTION("integral types")
    {
        int i{10};
        auto const result_i{std::to_string(i)};
        CHECK(result_i == bosswestfalen::make_string(i));
        CHECK(result_i == bosswestfalen::make_string(std::as_const(i)));
        CHECK(result_i == bosswestfalen::make_string(10));

        double d{10.0};
        auto const result_d{std::to_string(d)};
        CHECK(result_d == bosswestfalen::make_string(d));
        CHECK(result_d == bosswestfalen::make_string(std::as_const(d)));
        CHECK(result_d == bosswestfalen::make_string(10.0));

        bool b{true};
        auto const result_b{std::to_string(b)};
        CHECK(result_b == bosswestfalen::make_string(b));
        CHECK(result_b == bosswestfalen::make_string(std::as_const(b)));
        CHECK(result_b == bosswestfalen::make_string(true));

        test_type::convertible_to_int x;
        CHECK(std::string{"1234"} == bosswestfalen::make_string(x));
    }

    SECTION("operator<<")
    {
        test_type::has_operator_ll x;
        CHECK(std::string{"stream"} == bosswestfalen::make_string(x));
        //Temp x;
        //CHECK(true == bosswestfalen::type_traits::to_string_available_v<Temp>);
        //CHECK(x.as_string() == bosswestfalen::make_string(x));
    }
}

