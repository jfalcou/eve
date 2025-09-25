//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/predef.hpp>
#include <eve/as.hpp>

#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

namespace eve
{
  namespace detail
  {
    template<typename T>
    using wrap = T;
  }

  template<typename T, typename N>
  consteval auto find_register_type(as<T>, N, eve::ppc_)
  {
    using detail::wrap;

    constexpr auto size_check = [](std::size_t t, std::size_t n)
    {
      return (sizeof(T) == t) && (N::value <= n);
    };

    if constexpr (std::same_as<T, float> && (N::value <= 4))
    {
      return as<wrap<__vector float>>{};
    }
    else if constexpr (std::same_as<T, double> && (N::value <= 2))
    {
      if constexpr (spy::simd_instruction_set >= spy::vsx_) return as<wrap<__vector double>>{};
      else                                                  static_assert(false, "unreachable");
    }
    else if constexpr (std::signed_integral<T>)
    {
      if      constexpr (size_check(1, 16)) return as<wrap<__vector signed char>>{};
      else if constexpr (size_check(2,  8)) return as<wrap<__vector signed short>>{};
      else if constexpr (size_check(4,  4)) return as<wrap<__vector signed int>>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8, 2))     return as<wrap<__vector signed long>>{};
      }
      else                                  static_assert(false, "unreachable");
    }
    else if constexpr (std::unsigned_integral<T>)
    {
      if      constexpr (size_check(1, 16)) return as<wrap<__vector unsigned char>>{};
      else if constexpr (size_check(2,  8)) return as<wrap<__vector unsigned short>>{};
      else if constexpr (size_check(4,  4)) return as<wrap<__vector unsigned int>>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8, 2))     return as<wrap<__vector unsigned long>>{};
      }
      else                                  static_assert(false, "unreachable");
    }
  }

  template<typename T, typename N>
  consteval auto find_logical_register_type(as<T>, N, eve::ppc_)
  {
    using detail::wrap;

    constexpr auto size_check = [](std::size_t t, std::size_t n)
    {
      return (sizeof(T) == t) && (N::value <= n);
    };

    if constexpr (std::is_same_v<T, float> && (N::value <= 4))
    {
      return as<wrap<__vector __bool int>>{};
    }
    else if constexpr (std::is_same_v<T, double> && (N::value <= 2))
    {
      if constexpr (spy::simd_instruction_set >= spy::vsx_) return as<wrap<__vector __bool long>>{};
      else                                                  static_assert(false, "unreachable");
    }
    else if constexpr (std::integral<T>)
    {
      if      constexpr (size_check(1, 16))  return as<wrap<__vector __bool char>>{};
      else if constexpr (size_check(2, 8 ))  return as<wrap<__vector __bool short>>{};
      else if constexpr (size_check(4, 4 ))  return as<wrap<__vector __bool int>>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8,2))  return as<wrap<__vector __bool long>>{};
      }
      else
      {
        if constexpr (size_check(8, 2)) static_assert(false, "unreachable");
      }
    }
  }
}
