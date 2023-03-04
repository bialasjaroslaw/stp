#include <cstring>

#include "count.hpp"
#include "find.hpp"
#include "join.hpp"
#include "remove.hpp"
#include "replace.hpp"
#include "split.hpp"
#include "sub.hpp"

void count_needle(const uint8_t* Data, size_t Size)
{
    auto pred = [delim = *Data](auto ch) { return ch > delim; };
    ++Data;
    --Size;
    for (auto text_size = 1; text_size < Size - 1; ++text_size)
    {
        const std::basic_string_view<uint8_t> data(Data, text_size);
        const std::basic_string_view<uint8_t> needle(Data + text_size, Size - text_size);

        for (auto start_idx = -text_size; start_idx <= text_size; ++start_idx)
        {
            for (int end_idx = -text_size; end_idx <= text_size; ++end_idx)
            {
                Text::count(data, needle, start_idx, end_idx);
                Text::count_any(data, needle, start_idx, end_idx);
                Text::count_if(data, pred, start_idx, end_idx);
            }
        }
    }
}

void find_needle(const uint8_t* Data, size_t Size)
{
    auto pred = [delim = *Data](auto ch) { return ch > delim; };
    ++Data;
    --Size;
    for (int text_size = 1; text_size < Size - 1; ++text_size)
    {
        const std::basic_string_view<uint8_t> data(Data, text_size);
        const std::basic_string_view<uint8_t> needle(Data + text_size, Size - text_size);
        for (int start_idx = -text_size; start_idx <= text_size; ++start_idx)
        {
            for (int step = -text_size; step <= text_size; ++step)
            {
                Text::find(data, needle, start_idx, step);
                Text::find_any(data, needle, start_idx, step);
                Text::find_if(data, pred, start_idx, step);
                Text::rfind(data, needle, start_idx, step);
                Text::rfind_any(data, needle, start_idx, step);
                Text::rfind_if(data, pred, start_idx, step);
            }
        }
    }
}

void join_needle(const uint8_t* Data, size_t Size)
{
    std::vector<std::basic_string_view<uint8_t>> input;
    auto view_size = 2;
    for (int idx = view_size; idx < Size; idx += view_size)
        input.emplace_back(Data + idx - view_size, view_size);
    std::basic_string_view<uint8_t> needle(Data + Size - (Size % 2), Size % 2);

    Text::join(input, needle);
}

void remove_needle(const uint8_t* Data, size_t Size)
{
    auto pred = [delim = *Data](auto ch) { return ch > delim; };
    ++Data;
    --Size;
    for (int text_size = 1; text_size < Size - 1; ++text_size)
    {
        const std::basic_string_view<uint8_t> needle(Data + text_size, Size - text_size);
        std::basic_string<uint8_t> data(Data, text_size);
        auto reset = [&data, Data, text_size]() {
            data.resize(text_size);
            std::memcpy(data.data(), Data, text_size);
            *(data.data() + text_size) = 0;
        };
        for (int start_idx = -text_size; start_idx <= text_size; ++start_idx)
        {
            Text::remove(data, needle, start_idx);
            Text::removed(data, needle, start_idx);
            reset();
            Text::remove_any(data, needle, start_idx);
            Text::removed_any(data, needle, start_idx);
            reset();
            Text::remove_if(data, pred, start_idx);
            Text::removed_if(data, pred, start_idx);
            reset();
            Text::rremove(data, needle, start_idx);
            Text::rremoved(data, needle, start_idx);
            reset();
            Text::rremove_any(data, needle, start_idx);
            Text::rremoved_any(data, needle, start_idx);
            reset();
            Text::rremove_if(data, pred, start_idx);
            Text::rremoved_if(data, pred, start_idx);
            reset();
        }
    }
}

void replace_needle(const uint8_t* Data, size_t Size)
{
    auto pred = [](auto ch) { return ch > 'p'; };
    for (int text_size = 1; text_size < Size - 1; ++text_size)
    {
        for (int needle_size = 0; needle_size < Size - text_size - 1; ++needle_size)
        {
            const std::basic_string_view<uint8_t> needle(Data + text_size, needle_size);
            const std::basic_string_view<uint8_t> replace(Data + text_size + needle_size,
                                                          Size - text_size - needle_size);
            std::basic_string<uint8_t> data(Data, text_size);
            auto reset = [&data, Data, text_size]() {
                data.resize(text_size);
                memcpy(data.data(), Data, text_size);
                *(data.data() + text_size) = 0;
            };
            for (int start_idx = -text_size; start_idx <= text_size; ++start_idx)
            {
                for (int end_idx = -text_size; end_idx <= text_size; ++end_idx)
                {
                    Text::replace(data, needle, replace, start_idx, end_idx);
                    Text::replaced(data, needle, replace, start_idx, end_idx);
                    reset();
                    Text::replace_any(data, needle, replace, start_idx, end_idx);
                    Text::replaced_any(data, needle, replace, start_idx, end_idx);
                    reset();
                    Text::replace_if(data, pred, replace, start_idx, end_idx);
                    Text::replaced_if(data, pred, replace, start_idx, end_idx);
                    reset();
                }
            }
        }
    }
}

void split_needle(const uint8_t* Data, size_t Size)
{
    auto pred = [delim = *Data](auto ch) { return ch > delim; };
    ++Data;
    --Size;
    for (int text_size = 1; text_size < Size - 1; ++text_size)
    {
        const std::basic_string_view<uint8_t> data(Data, text_size);
        const std::basic_string_view<uint8_t> needle(Data + text_size, Size - text_size);

        for (int start_idx = -text_size; start_idx <= text_size; ++start_idx)
        {
            for (int end_idx = -text_size; end_idx <= text_size; ++end_idx)
            {
                Text::split(data, needle, Text::SplitBehavior::KeepEmpty, start_idx, end_idx);
                Text::split_any(data, needle, Text::SplitBehavior::KeepEmpty, start_idx, end_idx);
                Text::split_if(data, pred, Text::SplitBehavior::KeepEmpty, start_idx, end_idx);
                Text::split(data, needle, Text::SplitBehavior::DropEmpty, start_idx, end_idx);
                Text::split_any(data, needle, Text::SplitBehavior::DropEmpty, start_idx, end_idx);
                Text::split_if(data, pred, Text::SplitBehavior::DropEmpty, start_idx, end_idx);
            }
        }
    }
}

void sub_fuzzing(const uint8_t* Data, size_t Size)
{
    const std::basic_string_view<uint8_t> data(Data, Size);
    for (int text_size = -Size; text_size < Size + 2; ++text_size)
    {
        Text::left_view(data, text_size);
        Text::right_view(data, text_size);
        for (int text_length = -Size; text_length < Size + 2; ++text_length)
            Text::mid_view(data, text_size, text_length);
    }
}

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size)
{
    if (Size < 2)
        return 0;
    count_needle(Data, Size);
    find_needle(Data, Size);
    join_needle(Data, Size);
    remove_needle(Data, Size);
    replace_needle(Data, Size);
    split_needle(Data, Size);
    sub_fuzzing(Data, Size);
    return 0;
}
