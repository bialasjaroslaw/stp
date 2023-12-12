#include <text_processing/convert.hpp>

#include <gtest/gtest.h>
#include <gtest/gtest-matchers.h>
#include <gmock/gmock-more-matchers.h>

using namespace ::testing;

TEST(Convert, VectorOfStringsToVectorOfInts)
{
    using namespace std::literals;
    std::vector<std::string> data{"12"s, "-3"s, "2147483647"s, "-2147483648"s};
    auto result = Text::convert<int>(data);
    ASSERT_THAT(result, ElementsAre(12, -3, 2147483647, -2147483648));
}

TEST(Convert, VectorOfStringViewsToVectorOfInts)
{
    using namespace std::literals;
    std::vector<std::string_view> data{"12"sv, "-3"sv, "2147483647"sv, "-2147483648"sv};
    auto result = Text::convert<int>(data);
    ASSERT_THAT(result, ElementsAre(12, -3, 2147483647, -2147483648));
}

TEST(Convert, VectorOfStringsOutOfRange)
{
    using namespace std::literals;
    std::vector<std::string_view> data{"2147483648"s};
    EXPECT_THAT([&data](){ 
    	Text::convert<int>(data); },
    Throws<std::runtime_error>(Property(&std::runtime_error::what,
         HasSubstr("Invalid value passed to convert"))));

}
