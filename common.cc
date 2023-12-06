#include <text_processing/common.hpp>

#include <gtest/gtest.h>

TEST(Common, SanitizeIndex)
{
    int index = -1;
    EXPECT_EQ(23, Text::sanitize_index(index, 24));
}

TEST(Common, SanitizeRValueIndex)
{
    EXPECT_EQ(0, Text::sanitize_index(-24, 24));
    EXPECT_EQ(23, Text::sanitize_index(-1, 24));
    EXPECT_EQ(1, Text::sanitize_index(1, 24));
    EXPECT_EQ(23, Text::sanitize_index(23, 24));
    EXPECT_EQ(24, Text::sanitize_index(24, 24));
    EXPECT_EQ(Text::End, Text::sanitize_index(25, 24));
}

TEST(Common, IntViewToVector)
{
    std::basic_string<int> data{1, 2, 3, 1, 1, 2, 3, 1, 4, 1};
    std::basic_string_view data_view(data.cbegin(), data.cend());
    auto transformed = Text::to_vector(data_view);
    ASSERT_EQ(data_view.size(), transformed.size());
    for (size_t idx = 0; idx < data.size(); ++idx)
        EXPECT_EQ(data[idx], transformed[idx]);
}

TEST(Common, StringViewVectorToStringVector)
{
    std::string sample{"sample string with words"};
    std::vector<std::string_view> chunks{
        {sample.data(), 6}, {sample.data() + 7, 6}, {sample.data() + 14, 4}, {sample.data() + 19, 5}
    };
    auto str_chunks = Text::to_string_vector(chunks);
    ASSERT_EQ(chunks.size(), str_chunks.size());
    for (size_t idx = 0; idx < chunks.size(); ++idx)
        EXPECT_EQ(chunks[idx], str_chunks[idx]);
}

TEST(Common, VectorIntViewToVectorOfVectors)
{
    std::basic_string<int> data{1, 2, 3, 1, 1, 2, 3, 1, 4, 1};
    std::vector<std::basic_string_view<int>> data_view{
        {data.cbegin(), data.cbegin()}, {data.cbegin(), data.cbegin() + 4}, {data.cbegin() + 4, data.cend()}};
    auto transformed = Text::to_vector(data_view);
    ASSERT_EQ(data_view.size(), transformed.size());
    for (size_t idx = 0; idx < data_view.size(); ++idx)
        for (size_t item_idx = 0; item_idx < data_view[idx].size(); ++item_idx)
            EXPECT_EQ(data_view[idx][item_idx], transformed[idx][item_idx]);
}

TEST(Common, TextFromString)
{
    using namespace std::literals;
    auto view = "simple text"s;
    Text::Text txt(view);
    ASSERT_EQ(txt.length, view.length());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], view[idx]);
}

TEST(Common, TextFromView)
{
    using namespace std::literals;
    auto view = "simple text"sv;
    Text::Text txt(view);
    ASSERT_EQ(txt.length, view.length());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], view[idx]);
}

TEST(Common, TextFromVector)
{
    using namespace std::literals;
    auto view = "simple text"sv;
    std::vector<char> vec(view.cbegin(), view.cend());
    Text::Text txt(vec);
    ASSERT_EQ(txt.length, vec.size());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], vec[idx]);
}

TEST(Common, TextFromArray)
{
    std::array<char, 12> arr{"simple text"};
    Text::Text txt(arr);
    ASSERT_EQ(txt.length, arr.size());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], arr[idx]);
}

TEST(Common, TextFromCArray)
{
    char arr[] = "simple text";
    Text::Text txt(arr);
    ASSERT_EQ(txt.length, sizeof(arr) - 1); // '\0' should not count in this case
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], arr[idx]);
}

TEST(Common, DelimiterFromString)
{
    using namespace std::literals;
    auto view = "simple text"s;
    Text::Delimiter txt(view);
    ASSERT_EQ(txt.length, view.length());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], view[idx]);
}

TEST(Common, DelimiterFromView)
{
    using namespace std::literals;
    auto view = "simple text"sv;
    Text::Delimiter txt(view);
    ASSERT_EQ(txt.length, view.length());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], view[idx]);
}

TEST(Common, DelimiterFromVector)
{
    using namespace std::literals;
    auto view = "simple text"sv;
    std::vector<char> vec(view.cbegin(), view.cend());
    Text::Delimiter txt(vec);
    ASSERT_EQ(txt.length, vec.size());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], vec[idx]);
}

TEST(Common, DelimiterFromArray)
{
    std::array<char, 12> arr{"simple text"};
    Text::Delimiter txt(arr);
    ASSERT_EQ(txt.length, arr.size());
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], arr[idx]);
}

TEST(Common, DelimiterFromCArray)
{
    char arr[] = "simple text";
    Text::Delimiter txt(arr);
    ASSERT_EQ(txt.length, sizeof(arr) - 1); // '\0' should not count in this case
    for (size_t idx = 0; idx < txt.length; ++idx)
        ASSERT_EQ(txt.ptr[idx], arr[idx]);
}

TEST(Common, DelimiterFromElement)
{
    char ch = 's';
    Text::Delimiter txt(ch);
    ASSERT_EQ(txt.length, 1);
    ASSERT_EQ(*txt.ptr, ch);
}
