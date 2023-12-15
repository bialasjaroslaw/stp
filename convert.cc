#include <text_processing/convert.hpp>

#include <gtest/gtest.h>
#include <gtest/gtest-matchers.h>
#include <gmock/gmock-more-matchers.h>

using namespace ::testing;

TEST(Convert, StringToInt)
{
    using namespace std::literals;
    auto result = Text::convert<int32_t>("12"s);
    EXPECT_THAT(result, Eq(12));
}

TEST(Convert, StringViewToInt)
{
    using namespace std::literals;
    auto result = Text::convert<int32_t>("12"sv);
    EXPECT_THAT(result, Eq(12));
}

TEST(Convert, CharArrayToInt)
{
    using namespace std::literals;
    auto result = Text::convert<int32_t>("12");
    EXPECT_THAT(result, Eq(12));
}

TEST(Convert, StringToIntOverflow)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<int32_t>("2147483648"s); },
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, StringToLong)
{
    using namespace std::literals;
    auto result = Text::convert<int64_t>("9223372036854775807"s);
    EXPECT_THAT(result, Eq(9223372036854775807));
}

TEST(Convert, StringToLongOverflow)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<int64_t>("9223372036854775808"s); },
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, StringToFloat)
{
    using namespace std::literals;
    auto result = Text::convert<float>("12.34");
    EXPECT_THAT(result, FloatEq(12.34f));
}

TEST(Convert, StringToFloatOverflow)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<float>("4e+38"s); },
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, StringToDouble)
{
    using namespace std::literals;
    auto result = Text::convert<double>("12.34");
    EXPECT_THAT(result, DoubleEq(12.34));
}

TEST(Convert, StringToDoubleOverflow)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<double>("2e+308"s); },
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, VectorOfStringsToVectorOfInts)
{
    using namespace std::literals;
    std::vector<std::string> data{"12"s, "-3"s, "2147483647"s, "-2147483648"s};
    auto result = Text::convert<int32_t>(data);
    EXPECT_THAT(result, ElementsAre(12, -3, 2147483647, -2147483648));
}

TEST(Convert, VectorOfStringViewsToVectorOfInts)
{
    using namespace std::literals;
    std::vector<std::string_view> data{"12"sv, "-3"sv, "2147483647"sv, "-2147483648"sv};
    auto result = Text::convert<int32_t>(data);
    EXPECT_THAT(result, ElementsAre(12, -3, 2147483647, -2147483648));
}

TEST(Convert, VectorOfStringsIntOutOfRange)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<int32_t>(std::vector<std::string>{"12", "2147483648"s});},
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, VectorOfStringsToVectorOfLongs)
{
    using namespace std::literals;
    std::vector<std::string> data{"12"s, "-3"s, "9223372036854775807"s, "-9223372036854775808"s};
    auto result = Text::convert<int64_t>(data);
    EXPECT_THAT(result, ElementsAre(12, -3, 9223372036854775807, -9223372036854775807-1));
}

TEST(Convert, VectorOfStringViewsToVectorOfLongs)
{
    using namespace std::literals;
    std::vector<std::string_view> data{"12"sv, "-3"sv, "9223372036854775807"sv, "-9223372036854775808"sv};
    auto result = Text::convert<int64_t>(data);
    EXPECT_THAT(result, ElementsAre(12, -3, 9223372036854775807, -9223372036854775807-1));
}

TEST(Convert, VectorOfStringsLongsOutOfRange)
{
    using namespace std::literals;
    EXPECT_THAT([](){
        Text::convert<int64_t>(std::vector<std::string>{"12"s, "9223372036854775808"s});},
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, VectorOfStringsToVectorOfFloats)
{
    using namespace std::literals;
    std::vector<std::string> data{"NAN"s, "INF"s, "3.402823466e+38"s, "-3.402823466e+38"s, "1.4013e-45"};
    auto result = Text::convert<float>(data);
    EXPECT_THAT(result, ElementsAre(
        IsNan(), std::numeric_limits<float>::infinity(), 3.402823466e38f, -3.402823466e38f, 1.4013e-45f));
}

TEST(Convert, VectorOfStringsToVectorOfFloatsOutOfRange)
{
    using namespace std::literals;
    
    EXPECT_THAT([](){
        Text::convert<float>(std::vector<std::string_view>{"12.34"sv, "4e+38"sv});},
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

TEST(Convert, VectorOfStringsToVectorOfDoubles)
{
    using namespace std::literals;
    std::vector<std::string> data{"NAN"s, "INF"s, "1.79769e+308"s, "-1.79769e+308"s, "4.94066e-324"};
    auto result = Text::convert<double>(data);
    EXPECT_THAT(result, ElementsAre(
        IsNan(), std::numeric_limits<double>::infinity(), 1.79769e308, -1.79769e+308, 4.94066e-324));
}

TEST(Convert, VectorOfStringsToVectorOfDoublesOutOfRange)
{
    using namespace std::literals;

    EXPECT_THAT([](){
        Text::convert<double>(std::vector<std::string_view>{"12.34"sv, "2e+308"sv});},
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
            HasSubstr("Invalid value passed to convert"))
        )
    );
}

