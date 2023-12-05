#include <text_processing/count.hpp>

#include <gtest/gtest.h>

TEST(Count, SimpleWithViewAndShortNeedle)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, " ");
    EXPECT_EQ(result, 3);
}

TEST(Count, SimpleWithViewAndCharNeedle)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, ' ');
    EXPECT_EQ(result, 3);
}

TEST(Count, SimpleWithViewAndLongerNeedle)
{
    using namespace std::literals;
    auto simple_sv = " simple string with words"sv;
    auto result = Text::count(simple_sv, " s");
    EXPECT_EQ(result, 2);
}

TEST(Count, SimpleWithCustomTypeWord)
{
    struct MyType
    {
        int val;
        bool operator==(const MyType&) const = default;
    };

    std::vector<MyType> simple{{0}, {1337}, {12}};
    auto result = Text::count(simple, std::vector<MyType>{{1337}, {12}});
    EXPECT_EQ(result, 1);
}

TEST(Count, SimpleWithCustomTypeChar)
{
    struct MyType
    {
        int val;
        bool operator==(const MyType&) const = default;
    };

    std::vector<MyType> simple{{0}, {1337}};
    auto result = Text::count(simple, MyType{1337});
    EXPECT_EQ(result, 1);
}

TEST(Count, SimpleTestBoundsImplicit)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, "s");
    EXPECT_EQ(result, 3);
}

TEST(Count, SimpleTestBoundsExplicit)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, "s", Text::Start, Text::End);
    EXPECT_EQ(result, 3);
}

TEST(Count, CaseInsensitive)
{
    using namespace std::literals;
    auto simple_sv = "simple String with words"sv;
    auto result = Text::count(simple_sv, "S", Text::Start, Text::End, Text::Step, Text::Case::Insensitive);
    EXPECT_EQ(result, 3);
}

TEST(Count, WithSteps)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count(simple_sv, "s", Text::Start, Text::End, 2);
    EXPECT_EQ(result, 1);
}

TEST(CountIf, LargerThanValue)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_if(simple_sv, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result, 2);
}

TEST(CountIf, WithSteps)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_if(
        simple_sv, [](auto ch) { return ch > 'u'; }, Text::Start, Text::End, 2);
    EXPECT_EQ(result, 1);
}

TEST(CountAny, SimpleWithView)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_any(simple_sv, "tg");
    EXPECT_EQ(result, 3);
}

TEST(CountAny, SimpleWithCustomType)
{
    struct MyType
    {
        int val;
        auto operator<=>(const MyType&) const = default;
    };

    std::vector<MyType> simple{{0}, {1}, {2}, {1337}};
    std::vector<MyType> delimiters{{0}, {1}, {3}, {1337}};
    auto result = Text::count_any(simple, delimiters);
    EXPECT_EQ(result, 3);
}

TEST(CountAny, CaseInsensitive)
{
    using namespace std::literals;
    auto simple_sv = "simple String With words"sv;
    auto result = Text::count_any(simple_sv, "Sw", Text::Start, Text::End, Text::Step, Text::Case::Insensitive);
    EXPECT_EQ(result, 5);
}

TEST(CountAny, WithSteps)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::count_any(simple_sv, "sw", Text::Start, Text::End, 2);
    EXPECT_EQ(result, 2);
}
