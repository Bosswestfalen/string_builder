#include <catch.hpp>

#include <string_builder.hpp>

template <typename T>
class mock_container final
{
  public:
    void emplace_back(T&&)
    {
    }
    
    void pop_back()
    {
    }

    class too_big final
    {
        bool called{false};
      public:
        std::string::size_type size()
        {
            if (called)
            {
                std::string x;
                return x.max_size();
            }

            called = true;
            return 1;
        }

        auto max_size() const
        {
            return 1u;
        }
    };

    auto back() const
    {
        return too_big{};
    }
};

SCENARIO("exception")
{
    GIVEN("a string_builder")
    {
        bosswestfalen::basic_string_builder<mock_container> sb;
        sb.add("cat");

        WHEN("a string is added that exceeds the maximal size of a string")
        {
            THEN("std::length_error is thrown")
            {
                CHECK_THROWS_AS(sb.add("cat"), std::length_error);
            }
        }
    }
}

