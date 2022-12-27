#include "count.hpp"

#include <gtest/gtest.h>

TEST(Count, SimpleWithViewAndShortNeedle)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, " ");
    EXPECT_EQ(result, 3);
}

TEST(Count, SimpleWithViewAndLongerNeedle)
{
    using namespace std::literals;
    auto simple_sv = " simple string with words"sv;
    auto result = Text::count(simple_sv, " s");
    EXPECT_EQ(result, 2);
}

TEST(CountIf, LargerThanValue)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_if(simple_sv, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result, 2);
}

TEST(CountAny, SimpleWithView)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_any(simple_sv, "tg");
    EXPECT_EQ(result, 3);
}
