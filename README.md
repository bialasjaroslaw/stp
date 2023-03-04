# text_processing

## Motivation
I wanted to have simple and lightweight library for text operations that will be able to operate both on char and wchar_t containers. Moreover it should be able to operate on STL (string-like) containers and C-Strings as well. As a result it is able to operate on STL string/string_view/vector and C-Strings. In case of string/string_view/vector type is irrelevant as long as it is comparable. Unfortunatelly (for now) for custom there is only one acceptable delimiter type - std::vector<T>. This is not easy to use, but it was never intended to work that way, and probably will be fixed - see further work

## Functionality

Simple library for text processing
Supported data types:
* std::basic_string<T>
* std::basic_string_view<T>
* const T*
* T - for delimiters/needle only (find/split/join/remove/replace)

Operations:
* find/find_if/find_any and reverse versions - rfind/rfind_if/rfind_any
* join
* remove/remove_if/remove_any and reverse versions - rremove/rremove_if/rremove_any (only for convenience)
* replace/replace_if/replace_any
* split/split_if/split_any

Most of them have optional parameters start/stop. In case of reverse functions these are index from end of the text (-1 is 1st element from end -> 0 index, counting backwards. This concept is similar to array slicing in Python). Operations suports negative indices to point out that index should be reversed - treated as it is pointing reverse side of text. There is sanitization of indices, so in case of out of bounds access it will return empty value. 

Views:
* left/left_view, righ/right_view, mid/mid_view

When it comes to start index, behavior is the same as it is in case of operations - negative value is not treated as length but rather index from the other side of text (See explanation in Operations paragraph). Functions mid/mid_view by default have length until end of text so they are equivalent to right/right_view with negative index.

## Further work
Fix std::vector based operations:
* [X] Allow to use any type as delimiter without wrapping it inside std::vector
* [ ] Use more generic formula to limit available types for Text and Delimiter construction (right now only std::basic_string, std::basic_string_view, char_t* and wchar_t* are allowed)
* [ ] Add case_sensitive/insensitive_flag
* [ ] Distinguish between element iterator(index) and boundary iterator (between two elements)
* [X] Add fuzzing
* [ ] Add example usage in README.md

I have not done any benchmarks yet, so feel free to do so. 

## Tutorial
Tutorial is available in the test files. 

## License
Licensed under BSD license. 
