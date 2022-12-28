#pragma once

#include "common.hpp"

namespace Text {
template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find(const TextSrc& t, const NeedleSrc& n, int start = 0, int step = 1);

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rfind(const TextSrc& t, const NeedleSrc& n, int start = 0, int step = 1);

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int find_if(const TextSrc& t, Predicate pred, int start = 0, int step = 1);

template <typename TextSrc, typename Predicate, typename TextT = container_type_t<TextSrc>>
int rfind_if(const TextSrc& t, Predicate pred, int start = 0, int step = 1);

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int find_any(const TextSrc& t, const NeedleSrc& d, int start = 0, int step = 1);

template <typename TextSrc, typename NeedleSrc, typename TextT = container_type_t<TextSrc>,
          typename NeedleT = container_type_t<NeedleSrc>, std::enable_if_t<std::is_same_v<TextT, NeedleT>, int> = 0>
int rfind_any(const TextSrc& t, const NeedleSrc& d, int start = 0, int step = 1);

} // namespace Text