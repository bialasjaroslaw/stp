#include "split.hpp"

#include <gtest/gtest.h>

TEST(Split, SimpleWithView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, " "sv);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, WideView)
{
    using namespace std::literals;
    std::wstring simple(L"simple string with words");
    std::wstring_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, L" "sv);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, SimpleWithEmptyView)
{
    using namespace std::literals;
    std::string_view simple_sv;
    auto result = Text::split(simple_sv, " "sv);
    EXPECT_EQ(result.size(), 0);
}

TEST(Split, SimpleWithEmptyDelimiter)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, ""sv);
    EXPECT_EQ(result.size(), 24);
}

TEST(Split, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, " "sv, Text::SplitBehavior::KeepEmpty, 100);
    EXPECT_EQ(result.size(), 1);
}

TEST(Split, SimpleWithString)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, " "s);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, SimpleWithCharLiteral)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, " ");
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, SimpleWithChar)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split(simple_sv, ' ');
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, FromString)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result = Text::split(simple, " "sv);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, FromStringView)
{
    using namespace std::literals;
    std::string_view simple("simple string with words");
    auto result = Text::split(simple, " "sv);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, FromCharLiteral)
{
    using namespace std::literals;
    const char* simple = "simple string with words";
    auto result = Text::split(simple, " "sv);
    EXPECT_EQ(result.size(), 4);
}

TEST(Split, EndsWithDelimiter)
{
    using namespace std::literals;
    std::string simple("simple string with words ");
    auto result_keep = Text::split(simple, " "sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split(simple, " "sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 5);
    EXPECT_EQ(result_drop.size(), 4);
}

TEST(Split, StartsWithDelimiter)
{
    using namespace std::literals;
    std::string simple(" simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split(simple_sv, " "sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split(simple_sv, " "sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 5);
    EXPECT_EQ(result_drop.size(), 4);
}

TEST(Split, MultipleDelimiters)
{
    using namespace std::literals;
    std::string simple(" simple  string  with  words ");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split(simple_sv, " "sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split(simple_sv, " "sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 4 + 5);
    EXPECT_EQ(result_drop.size(), 4);
}

TEST(Split, ComplexDelimiter)
{
    using namespace std::literals;
    std::string simple("simple [] string [] with [] words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split(simple_sv, " [] "sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split(simple_sv, " [] "sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 4);
    EXPECT_EQ(result_drop.size(), 4);
}

TEST(Split, LongDelimiter)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split(simple_sv, "string "sv);
    auto expected = std::vector<std::string_view>{"simple "sv, "with words"sv};
    EXPECT_EQ(result_keep, expected);
}

TEST(Split, Blocks)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result_keep = Text::split(simple, "", Text::SplitBehavior::KeepEmpty, Text::Start, Text::End, 5);
    auto expected = std::vector<std::string_view>{"simpl"sv, "e str"sv, "ing w"sv, "ith w"sv, "ords"sv};
    EXPECT_EQ(result_keep, expected);
}

TEST(Split, CaseSensitivity)
{
    using namespace std::literals;
    std::string simple("simple String with words");
    auto result_keep = Text::split(simple, "s", Text::SplitBehavior::KeepEmpty, Text::Start, Text::End, Text::Step,
                                   Text::Case::Insensitive);
    auto result_drop = Text::split(simple, "s", Text::SplitBehavior::DropEmpty, Text::Start, Text::End, Text::Step,
                                   Text::Case::Insensitive);
    auto expected_keep = std::vector<std::string_view>{""sv, "imple "sv, "tring with word"sv, ""sv};
    auto expected_drop = std::vector<std::string_view>{"imple "sv, "tring with word"sv};
    EXPECT_EQ(result_keep, expected_keep);
    EXPECT_EQ(result_drop, expected_drop);
}

TEST(Split, WithSteps)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result_keep = Text::split(simple, "s", Text::SplitBehavior::KeepEmpty, 1, Text::End, 2);
    auto result_drop = Text::split(simple, "s", Text::SplitBehavior::DropEmpty, 1, Text::End, 2);
    auto expected_keep = std::vector<std::string_view>{"simple "sv, "tring with word"sv, ""sv};
    auto expected_drop = std::vector<std::string_view>{"simple "sv, "tring with word"sv};
    EXPECT_EQ(result_keep, expected_keep);
    EXPECT_EQ(result_drop, expected_drop);
}

TEST(Split, IntVector)
{
    std::vector<int> data{1, 2, 3, 1, 1, 2, 3, 1, 4, 1};
    auto result_keep = Text::split(data, 1, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split(data, 1, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 3 + 3);
    EXPECT_EQ(result_drop.size(), 3);
}

TEST(SplitIf, ValueLargerThan)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split_if(simple_sv, [](auto ch) { return ch > 'u'; });
    auto expected = std::vector<std::string_view>{"simple string "sv, "ith "sv, "ords"sv};
    EXPECT_EQ(result_keep, expected);
}

TEST(SplitIf, SimpleWithEmptyView)
{
    using namespace std::literals;
    std::string_view simple_sv;
    auto result = Text::split_if(simple_sv, [](auto ch) { return ch > 'u'; });
    EXPECT_EQ(result.size(), 0);
}

TEST(SplitIf, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split_if(
        simple_sv, [](auto ch) { return ch > 'u'; }, Text::SplitBehavior::KeepEmpty, 100);
    EXPECT_EQ(result.size(), 1);
}

TEST(SplitIf, WithSteps)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result_keep = Text::split_if(
        simple, [](auto ch) { return ch > 'u'; }, Text::SplitBehavior::KeepEmpty, 1, Text::End, 2);
    auto expected = std::vector<std::string_view>{"simple string with "sv, "ords"sv};
    EXPECT_EQ(result_keep, expected);
}

TEST(SplitAny, SimpleWithView)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split_any(simple_sv, " i"sv);
    EXPECT_EQ(result.size(), 7);
}

TEST(SplitAny, SimpleWithEmptyView)
{
    using namespace std::literals;
    std::string_view simple_sv;
    auto result = Text::split_any(simple_sv, "tg"sv);
    EXPECT_EQ(result.size(), 0);
}

TEST(SplitAny, OutOfBoundsStart)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split_any(simple_sv, "tg"sv, Text::SplitBehavior::KeepEmpty, 100);
    EXPECT_EQ(result.size(), 1);
}

TEST(SplitAny, SimpleWithString)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split_any(simple_sv, " i"s);
    EXPECT_EQ(result.size(), 7);
}

TEST(SplitAny, SimpleWithCharLiteral)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result = Text::split_any(simple_sv, " i");
    EXPECT_EQ(result.size(), 7);
}

TEST(SplitAny, EndsWithDelimiter)
{
    using namespace std::literals;
    std::string simple("simple string with words ");
    auto result_keep = Text::split_any(simple, " i"sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split_any(simple, " i"sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 7 + 1);
    EXPECT_EQ(result_drop.size(), 7);
}

TEST(SplitAny, StartsWithDelimiter)
{
    using namespace std::literals;
    std::string simple(" simple string with words");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split_any(simple_sv, " i"sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split_any(simple_sv, " i"sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 7 + 1);
    EXPECT_EQ(result_drop.size(), 7);
}

TEST(SplitAny, MultipleDelimiters)
{
    using namespace std::literals;
    std::string simple(" simple  string  with  words ");
    std::string_view simple_sv(simple.data(), simple.length());
    auto result_keep = Text::split_any(simple_sv, " i"sv, Text::SplitBehavior::KeepEmpty);
    auto result_drop = Text::split_any(simple_sv, " i"sv, Text::SplitBehavior::DropEmpty);
    EXPECT_EQ(result_keep.size(), 7 + 5);
    EXPECT_EQ(result_drop.size(), 7);
}

TEST(SplitAny, CaseSensitivity)
{
    using namespace std::literals;
    std::string simple("simple String with words");
    auto result_keep = Text::split_any(simple, "Sw", Text::SplitBehavior::KeepEmpty, Text::Start, Text::End, Text::Step,
                                       Text::Case::Insensitive);
    auto result_drop = Text::split_any(simple, "Sw", Text::SplitBehavior::DropEmpty, Text::Start, Text::End, Text::Step,
                                       Text::Case::Insensitive);
    auto expected_keep = std::vector<std::string_view>{""sv, "imple "sv, "tring "sv, "ith "sv, "ord"sv, ""sv};
    auto expected_drop = std::vector<std::string_view>{"imple "sv, "tring "sv, "ith "sv, "ord"sv};
    EXPECT_EQ(result_keep, expected_keep);
    EXPECT_EQ(result_drop, expected_drop);
}

TEST(SplitAny, WithSteps)
{
    using namespace std::literals;
    std::string simple("simple string with words");
    auto result_keep = Text::split_any(simple, "s", Text::SplitBehavior::KeepEmpty, 1, Text::End, 2);
    auto result_drop = Text::split_any(simple, "s", Text::SplitBehavior::DropEmpty, 1, Text::End, 2);
    auto expected_keep = std::vector<std::string_view>{"simple "sv, "tring with word"sv, ""sv};
    auto expected_drop = std::vector<std::string_view>{"simple "sv, "tring with word"sv};
    EXPECT_EQ(result_keep, expected_keep);
    EXPECT_EQ(result_drop, expected_drop);
}
