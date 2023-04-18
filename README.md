# text_processing

## Motivation
I wanted to have simple and lightweight library for text operations that will be able to operate both on char and wchar_t containers. Moreover it should be able to operate on STL (string-like) containers and C-Strings as well. As a result it is able to operate on STL string/string_view/vector and C-Strings. In case of string/string_view/vector type is irrelevant as long as it is comparable.

## Functionality

Simple library for text processing (developed for text, but any type of comparable data can be used)
Supported data types (T have to be comparable in most cases, for multiple delimiters also less than operator have to be defined):
* Any STL-container like type that specifies `T::data()`, `T::size()` and `T::value_type` (vector, array, string, string_view)
* `const T*`
* `T[N]`
* `T` - for delimiters/needle only (find/split/join/remove/replace)

Operations:
* find/find_if/find_any and reverse versions - rfind/rfind_if/rfind_any
* join
* remove/remove_if/remove_any and reverse versions
* replace/replace_if/replace_any
* split/split_if/split_any

Most of them have optional parameters start/stop/step (for ones that it make sense). There are special values for marking default text boundaries and step - `Text::Start`, `Text::End`, `Text::Step`. If algorithm should iterate from or to index counted from the end of container, just provide a negative value. This concept is similar to array slicing in Python). There is sanitization of indices, so in case of out of bounds access it will return empty value/container. If step is equal to zero empty result will be returned. If absolute value of step is larger than zero, algorithms will perform their actions only on those elements. In case a negative step value is provided, a symmetric version of algorithm will be called (`find` -> `rfind`) if it exists. This might be more convenient in some cases. In case of symmetric versions of algorithms, a range (start, end values), is exactly the same.

Sub-containers/Views:
* left/left_view, righ/right_view, mid/mid_view

When it comes to start index, behavior is the same as it is in case of operations - negative value is treated as an index from the other side of text (See explanation in Operations paragraph). Functions mid/mid_view by default have length until end of text so they are equivalent to right/right_view with negative index. However if length is negative it is end index of the view (counted from the end of container). Views does not support step, as this will require a wrapper instead of `std::string_view`, because this might not be continuous. In case of a sub-container it is possible but not yet available.

## Why left/right/mid?
To make this library complete. I am aware that there is a `std::string::substr()`, but if you want to use convenient call syntax with negative indices for 'from the end', this will always require something like `std::max(0UL, size - index)`, and you will always have to think at least a second before writing this down. There is no bounds check (performace), and making a view from string is not so clean (it is my opinion, but again no bounds check for calls like `std::string_view(s.data() + 1, s.size() - 3)`).
Once again there is no bounds check, but rather exception throw, and I am aware how a C++ community is divided when it comes to the exceptions handling. If you prefer to use them, stick with the STL.
As the library is more generic, all of the above can be done on any iterable data structure with any type of data inside. Again you could use `std::basic_string<T>` for that, your call.

## Further work
Fix std::vector based operations:
* [X] Allow to use any type as delimiter without wrapping it inside std::vector
* [X] Use more generic formula to limit available types for Text and Delimiter construction. Any type that provides `data()`, `size()` and `T::value_type` can be passed. Ass well as any type of pointer to data buffer.
* [X] Add case_sensitive/insensitive_flag
* [X] Add fuzzing
* [X] Add example usage in README.md
* [ ] Allow for user defined specialization to be used instead of a type wrapper in case of a custom data type (`data()`, `size()`, etc)
* [ ] Distinguish between element iterator(index) and boundary iterator (between two elements)
* [ ] Run benchmarks and compare (at least) with hand written solution, and (if available) with ones from STL.
* [ ] Limit project_options/project_warnings and content fetch to developer build (do not spoil client project)

## Tutorial

Find any character from a string in other string. Constraint search area to specific indices (from/to). Make same operation but only for even indices. At the end perform the same search but case insensitive

```c++
std::string long_text("...");
std::string search_letters("abc");
// Use find_any not find. Latter one will look for whole word match
auto idx = Text::find_any(long_text, search_letters);
idx = Text::find_any(long_text, search_letters, 10, -12);
// The same can be obtained using mid view, but index have to be shifted
idx = Text::find_any(Text::mid_view(long_text, 10, -12), search_letters);
// Only for specific interval. View can not be used like that
idx = Text::find_any(long_text, search_letters, 10, -12, 2);
// Case is ignored
idx = Text::find_any(long_text, search_letters, 10, -12, 2, Text::Case::Insensitive);
// Check if index is valid
if (idx != Text::End)
  ...
```

Make same search as before but from the right side of a string and then do that for a specific range

```c++
idx = Text::rfind_any(long_text, search_letters);
// Use negative step to achieve the same result with find_any
idx = Text::find_any(long_text, search_letters, Text::Start, Text::End, -1);
// Only for specific range and interval. Step is positive in this case
idx = Text::rfind_any(long_text, search_letters, 10, -12, 2);
```

Find first value that is valid for a predicate (function/lambda)

```c++
auto predicate = [](char c){...}; // or const T&
idx = Text::find_if(long_text, predicate);
// For a range
idx = Text::find_if(long_text, predicate, 10, -12);
```

Count all occurences of letter a in a string

```c++
auto count = Text::count(long_text, 'a');
```

Split sentence to words and then join them using '_'. Limit split to part of a string.

```c++
// Rest of string (unsplitted) will be part of first/last fragment
auto splitted = Text::split(long_text, ' ', 10, -12);
auto joined = Text::join(splitted, '_')
```

Remove all occurences of a "what" word. Replace it by "whoa". Do it for const objects (return modified version instead of changing original)

```c++
Text::remove(long_text, "what");
Text::replace(long_text, "what", "whoa");
// For const objects
auto rem = Text::removed(long_text, "what");
auto rep = Text::replaced(long_text, "what", "whoa");
```

Create a new string or a view from left/right/mid portion of the string

```c++
// Length 13
auto lft = Text::left(long_text, 13);
// View without last character.
// Source object have to exist for the lifetime of this
auto lft_view = Text::left_view(long_text, -1);
// Last 13 characters (or less if source is shorter)
auto rght = Text::right(long_text, 13);
// View with portion that starts at 10th character from the end
auto rght_view = Text::right_view(long_text, -10);
// String that starts at 13th character and is as long as it can be
// Equivalent of Text::right(long_text, size - 13)
auto mid = Text::mid(long_text, 13);
// View that starts at 13th character and ends at 10th from the end
auto mid_view = Text::mid_view(long_text, 13, -10);
```

## Tests

By default tests are build, but without extensive sanitization or checks. Fuzzing is also not built in if `DEVELOPER_BUILD` is not turned on. This greatly reduce build time.

## License
Licensed under BSD license.
