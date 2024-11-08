#pragma once
// 17.4.1.2 Headers

// clang-format off
#include <Windows.h>
#include <winternl.h>
// clang-format on
#include "propvarutil.h"
#include <execution>
#include <map>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mutex>
#include <set>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <fstream>

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11.h>
#include <dxgi.h>

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )

#include <ShlObj.h>
#include <filesystem>
#include <variant>

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <csetjmp>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>

#if __cplusplus >= 201103L
#include <cstdint>
#endif

// C++
// #include <bitset>
// #include <complex>
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <numeric>
#include <typeinfo>
#include <utility>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <initializer_list>
#include <ratio>
#include <scoped_allocator>
#include <tuple>
#include <type_traits>
#include <typeindex>
#endif

#if __cplusplus >= 201402L
#endif

#if __cplusplus >= 201703L
#include <any>
// #include <execution>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if __cplusplus >= 202002L
#include <bit>
#include <compare>
#include <concepts>
#include <numbers>
#include <ranges>
#include <source_location>
#include <span>
#include <version>
#endif

#if __cplusplus > 202002L
#include <expected>
#include <stdatomic.h>
#if __cpp_impl_coroutine
#include <coroutine>
#endif
#endif