#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <utility>

using Byte  = uint8_t;
using Word  = uint16_t;
using Dword = uint32_t;
using Qword = uint64_t;

using RuntimeError = std::runtime_error;
using String = std::string;
template <typename T>
using Vec = std::vector<T>;
template <typename M, typename N>
using Map = std::map<M, N>;
template <typename M, typename N>
using UMap = std::unordered_map<M, N>;
template <typename M, typename N>
using Pair = std::pair<M, N>;
template <typename S, int N>
using Array = std::array<S, N>;
using SizeT = size_t;
template <typename T>
using UPtr = std::unique_ptr<T>;
