#include <text_processing/find.hpp>

#include <gtest/gtest.h>

TEST(Find, SimpleWithView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv);
    EXPECT_EQ(result, 6);
}

TEST(Find, SimpleWithViewEmptyNeedle)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, ""sv);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, SimpleWithOutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, ZeroStep)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv, Text::Start, Text::End, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, SimpleWithUint8String)
{
    using namespace std::literals;
    std::basic_string<uint8_t> simple{{'b', 'a'}};
    auto result = Text::find(simple, std::basic_string<uint8_t>(1, 'a'));
    EXPECT_EQ(result, 1);
}

TEST(Find, SimpleWithUint16String)
{
    using namespace std::literals;
    std::basic_string<uint16_t> simple{{'b', 'a'}};
    auto result = Text::find(simple, std::basic_string<uint16_t>(1, 'a'));
    EXPECT_EQ(result, 1);
}

TEST(Find, SimpleWithUint16Vector)
{
    using namespace std::literals;
    std::vector<uint16_t> simple{0, 1337};
    auto result = Text::find(simple, std::vector<uint16_t>{1337});
    EXPECT_EQ(result, 1);
}

TEST(Find, CustomType)
{
    struct MyType
    {
        int val;
        bool operator==(const MyType&) const = default;
    };

    std::vector<MyType> simple{{0}, {1337}};
    auto result = Text::find(simple, std::vector<MyType>{{1337}});
    EXPECT_EQ(result, 1);
}

TEST(Find, SimpleWithWideView)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    auto result = Text::find(simple, L" "sv);
    EXPECT_EQ(result, 6);
}

TEST(Find, SimpleWithString)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "s);
    EXPECT_EQ(result, 6);
}

TEST(Find, SimpleWithChar)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, ' ');
    EXPECT_EQ(result, 6);
}

TEST(Find, SimpleWithConstChar)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " ");
    EXPECT_EQ(result, 6);
}

TEST(Find, SimpleNotFoundWithView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, "x"sv);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, SimpleWithViewAndStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv, 7);
    EXPECT_EQ(result, 13);
}

TEST(Find, MultipleWithView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto start = 0;
    auto result = 0;
    std::vector<int> expected{6, 13, 18};
    auto needle = " "sv;
    for (const auto exp : expected)
    {
        result = Text::find(simple, needle, start);
        EXPECT_EQ(result, exp);
        start = result + 1;
    }
    result = Text::find(simple, needle, start);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, SimpleWithLongerView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, "with"sv);
    EXPECT_EQ(result, 14);
}

TEST(Find, ViewLongerThanContainer)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, "simple string with words "sv);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, ViewWithNegativeStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv, -8);
    EXPECT_EQ(result, 18);
}

TEST(Find, ViewWithStep)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, " "sv, 1, Text::End, 2);
    EXPECT_EQ(result, 13);
}

TEST(Find, ViewNotFound)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::find(simple, "strings"sv);
    EXPECT_EQ(result, Text::End);
}

TEST(Find, CaseInsensitive)
{
    using namespace std::literals;
    auto simple_sv = "simple String with words"sv;
    auto result = Text::find(simple_sv, "S", Text::Start, Text::End, Text::Step, Text::Case::Insensitive);
    EXPECT_EQ(result, 0);
}

TEST(Find, WithSteps)
{
    using namespace std::literals;
    auto simple_sv = "simple string with words"sv;
    auto result = Text::find(simple_sv, "s", 1, Text::End, 2);
    EXPECT_EQ(result, 7);
}

TEST(FindIf, View)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(simple, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result, 14);
}

TEST(FindIf, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(
        simple, [](auto ch) { return ch > 'u'; }, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(FindIf, ZeroStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(
        simple, [](auto ch) { return ch > 'u'; }, Text::Start, Text::End, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(FindIf, WideView)
{
    using namespace std::literals;
    std::wstring_view simple(L"simple string with words");
    auto result = Text::find_if(simple, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result, 14);
}

TEST(FindIf, ViewWithStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(
        simple, [](auto ch) { return ch > 'u'; }, 15);
    EXPECT_EQ(result, 19);
}

TEST(FindIf, WithSteps)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(
        simple, [](auto ch) { return ch > 'u'; }, 1, Text::End, 2);
    EXPECT_EQ(result, 19);
}

TEST(RFind, SimpleWithView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv);
    EXPECT_EQ(result, 18);
}

TEST(RFind, SimpleWithOutOfBoundsStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(RFind, ZeroStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, 0, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(RFind, WithSteps)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, Text::Start, Text::End, 2);
    EXPECT_EQ(result, 13);
}

TEST(RFind, ViewWithNegativeEnd)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, Text::Start, -8);
    EXPECT_EQ(result, 13);
}

TEST(RFind, ViewWithStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, Text::Start, Text::End, 2);
    EXPECT_EQ(result, 13);
}

TEST(RFind, SimpleWithViewAndStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind(simple, " "sv, 7);
    EXPECT_EQ(result, 18);
}

TEST(RFindIf, View)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_if(simple, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result, 19);
}

TEST(RFindIf, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_if(
        simple, [](auto ch) { return ch > 'u'; }, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(RFindIf, ViewWithStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_if(
        simple, [](auto ch) { return ch > 'u'; }, 5);
    EXPECT_EQ(result, 14);
}

TEST(RFindIf, ZeroStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_if(
        simple, [](auto ch) { return ch > 'u'; }, 0, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(RFindIf, WithSteps)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_if(
        simple, [](auto ch) { return ch > 'u'; }, Text::Start, -1, 2);
    EXPECT_EQ(result, 14);
}

TEST(FindAny, SimpleWithView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg"sv);
    EXPECT_EQ(result, 8);
}

TEST(FindAny, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg"sv, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(FindAny, ZeroStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg"sv, Text::Start, Text::End, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(FindAny, SimpleWithString)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg"s);
    EXPECT_EQ(result, 8);
}

TEST(FindAny, SimpleWithConstChar)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg");
    EXPECT_EQ(result, 8);
}

TEST(FindAny, MultipleWithView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto start = 0;
    auto result = 0;
    std::vector<int> expected{8, 12, 16};
    auto needle = "tg"sv;
    for (const auto exp : expected)
    {
        result = Text::find_any(simple, needle, start);
        EXPECT_EQ(result, exp);
        start = result + 1;
    }
    result = Text::find_any(simple, needle, start);
    EXPECT_EQ(result, Text::End);
}

TEST(FindAny, ViewWithNegativeStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "tg"sv, -8);
    EXPECT_EQ(result, 16);
}

TEST(FindAny, WideView)
{
    using namespace std::literals;
    std::wstring_view simple(L"simple string with words");
    auto result = Text::find_any(simple, L"tg"sv, -8);
    EXPECT_EQ(result, 16);
}

TEST(FindAny, WithSteps)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::find_any(simple, "sw"sv, 1, Text::End, 2);
    EXPECT_EQ(result, 7);
}

TEST(RFindAny, SimpleWithView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg"sv);
    EXPECT_EQ(result, 16);
}

TEST(RFindAny, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg"sv, 100);
    EXPECT_EQ(result, Text::End);
}

TEST(RFindAny, ZeroStep)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg"sv, 0, 0);
    EXPECT_EQ(result, Text::End);
}

TEST(RFindAny, SimpleWithString)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg"s);
    EXPECT_EQ(result, 16);
}

TEST(RFindAny, SimpleWithConstChar)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg");
    EXPECT_EQ(result, 16);
}

TEST(RFindAny, MultipleWithView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto end = static_cast<int>(simple.length());
    auto result = 0;
    std::vector<int> expected{16, 12, 8};
    auto needle = "tg"sv;
    for (const auto exp : expected)
    {
        result = Text::rfind_any(simple, needle, Text::Start, end);
        EXPECT_EQ(result, exp);
        end = result - 1;
    }
    result = Text::rfind_any(simple, needle, Text::Start, end);
    EXPECT_EQ(result, Text::End);
}

TEST(RFindAny, ViewWithNegativeStart)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "tg"sv, -12);
    EXPECT_EQ(result, 16);
}

TEST(RFindAny, WithSteps)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::rfind_any(simple, "sw"sv, Text::Start, -1, 2);
    EXPECT_EQ(result, 14);
}
