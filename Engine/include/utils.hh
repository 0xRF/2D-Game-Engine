#pragma once

#include "common.hh"

namespace utils {
bool string_is_safe(const std::string &string);
bool char_is_safe(const char &ch);
template <typename T, typename X>
std::pair<T, T> find_min_max(std::vector<X> v, std::function<T(X x)> handler) {
  T min = std::numeric_limits<T>::max();
  T max = -std::numeric_limits<T>::max();

  for (auto x : v) {
    T inst = handler(x);
    max = std::max(max, inst);
    min = std::min(min, inst);
  }
  return {min, max};
}
} // namespace utils
