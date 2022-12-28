#include "join.hpp"

#include <gtest/gtest.h>

TEST(Join, SimpleWithView)
{
    using namespace std::literals;
    std::vector<std::string> simple{"simple", "string", "with", "words"};
    auto result = Text::join(simple, " ");
    EXPECT_EQ(result, "simple string with words"s);
}

TEST(Join, SimpleWithEmptyView)
{
    using namespace std::literals;
    std::vector<std::string> simple;
    auto result = Text::join(simple, " ");
    EXPECT_EQ(result, "");
}

TEST(Join, SimpleWithString)
{
    using namespace std::literals;
    std::vector<std::string> simple{"simple", "string", "with", "words"};
    auto result = Text::join(simple, " "s);
    EXPECT_EQ(result, "simple string with words"s);
}

TEST(Join, SimpleWithCharLiteral)
{
    using namespace std::literals;
    std::vector<std::string> simple{"simple", "string", "with", "words"};
    auto result = Text::join(simple, " ");
    EXPECT_EQ(result, "simple string with words"s);
}

TEST(Join, WideView)
{
    using namespace std::literals;
    std::vector<std::wstring> simple{L"simple", L"string", L"with", L"words"};
    auto result = Text::join(simple, L" ");
    EXPECT_EQ(result, L"simple string with words"s);
}
