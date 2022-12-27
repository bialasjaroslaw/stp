#include "sub.hpp"

#include <gtest/gtest.h>

TEST(Sub, ViewLeftPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::left(simple_sv, 6);
    EXPECT_EQ(result, "simple"s);
}

TEST(Sub, WideViewLeft)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    std::wstring_view simple_sv(simple.data(), simple.length());
    auto result = Text::left(simple_sv, 6);
    EXPECT_EQ(result, L"simple"s);
}

TEST(Sub, ViewLeftNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::left(simple_sv, -6);
    EXPECT_EQ(result, "simple string with");
}

TEST(Sub, StringLeftPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::left(simple, 6);
    EXPECT_EQ(result, "simple"s);
}

TEST(Sub, ConstCharLeftPositive)
{
    using namespace std::literals;
    const char* simple = "simple string with words";
    auto result = Text::left(simple, 6);
    EXPECT_EQ(result, "simple"s);
}

TEST(Sub, ViewLeftView)
{
    using namespace std::literals;
    const char* simple = "simple string with words";
    auto result = Text::left_view(simple, 6);
    EXPECT_EQ(result, "simple"sv);
}

TEST(Sub, ViewRightPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::right(simple_sv, 6);
    EXPECT_EQ(result, " words"s);
}

TEST(Sub, ViewRightNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::right(simple_sv, -6);
    EXPECT_EQ(result, " string with words");
}

TEST(Sub, ViewRightBigNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::right(simple_sv, -100);
    EXPECT_EQ(result, "");
}

TEST(Sub, StringRightPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::right(simple, 6);
    EXPECT_EQ(result, " words"s);
}

TEST(Sub, ConstCharRightPositive)
{
    using namespace std::literals;
    const char* simple = "simple string with words";
    auto result = Text::right(simple, 6);
    EXPECT_EQ(result, " words"s);
}

TEST(Sub, ViewMidPositiveAndDefault)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, 6);
    EXPECT_EQ(result, " string with words"s);
}

TEST(Sub, ViewMidNegativeAndDefault)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, -6);
    EXPECT_EQ(result, " words"s);
}

TEST(Sub, ViewMidPositiveAndLargerThanText)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, 6, 100);
    EXPECT_EQ(result, " string with words"s);
}

TEST(Sub, ViewMidNegativeAndLargerThanText)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, -6, 100);
    EXPECT_EQ(result, " words"s);
}

TEST(Sub, ViewMidPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, 6, 4);
    EXPECT_EQ(result, " str"s);
}

TEST(Sub, ViewMidNegativeAndPositive)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, -6, 4);
    EXPECT_EQ(result, " wor"s);
}

TEST(Sub, ViewMidPositiveAndNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, 6, -6);
    EXPECT_EQ(result, " string with"s);
}

TEST(Sub, ViewMidStartAndNegative)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::mid(simple_sv, 0, -6);
    EXPECT_EQ(result, "simple string with"s);
}

TEST(Sub, RightEquiMid)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result1 = Text::mid(simple_sv, 6);
    auto result2 = Text::right(simple_sv, -6);
    EXPECT_EQ(result1, result2);
}

TEST(Sub, LeftEquiMid)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result1 = Text::mid(simple_sv, 0, -6);
    auto result2 = Text::left(simple_sv, -6);
    EXPECT_EQ(result1, result2);
}
