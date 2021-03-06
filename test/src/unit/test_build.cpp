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
                CHECK(std::string{""} == sb.build());
            }
        }

        WHEN("a string is added")
        {
            const std::string cat{"cat"};
            sb.add(cat);
            
            THEN("the result is the entered string")
            {
                CHECK(cat == sb.build());
            }
        }

        WHEN("two strings are added")
        {
            const std::string cat{"cat"};
            const std::string dog{"dog"};
            sb.add(cat);
            sb.add(dog);

            THEN("the result is the concatenation of both strings")
            {
                CHECK(cat + dog == sb.build());
            }
        }
    }

    GIVEN("two empty string_builder")
    {
        bosswestfalen::string_builder a;
        bosswestfalen::string_builder b;

        WHEN("Rvalue and Lvalues are added")
        {
            a.add("cat");
            const std::string cat{"cat"};
            b.add(cat);

            THEN("both builders produce the same result")
            {
                CHECK(a.build() == b.build());
            }
        }
    }
}

