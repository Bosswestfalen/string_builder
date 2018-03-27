#include <catch.hpp>
#include <string_builder.hpp>

TEST_CASE("building")
{
    bosswestfalen::string_builder sb;

    SECTION("empty string_builder")
    {
        const std::string empty{""};
        REQUIRE(empty == sb.build());
    }
}

