#include <catch.hpp>
#include <string_builder.hpp>

SCENARIO("building strings")
{
    GIVEN("an empty string_builder")
    {
        bosswestfalen::string_builder sb;

        WHEN("its result is requested")
        {
            THEN("it is an empty string")
            {
                REQUIRE(std::string{""} == sb.build());
            }
        }

        WHEN("a string is added")
        {
            const std::string cat{"cat"};
            sb.add(cat);
            
            THEN("the result is the entered string")
            {
                REQUIRE(cat == sb.build());
            }
        }

        WHEN("two strings are added")
        {
            const std::string cat{"cat"};
            sb.add(cat);
            const std::string dog{"dog"};
            sb.add(dog);

            THEN("the result is the concatenation of both strings")
            {
                REQUIRE(cat + dog == sb.build());
            }
        }
    }
}

