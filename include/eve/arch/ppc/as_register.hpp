//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/predef.hpp>
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
      return wrap<__vector float>{}; 
    }
    else if constexpr (std::same_as<T, double> && (N::value <= 2))
    {
      if constexpr (spy::simd_instruction_set >= spy::vsx_) return wrap<__vector double>{};
      else                                                  return emulated_{};
    }
    else if constexpr (std::signed_integral<T>)
    {
      if      constexpr (size_check(1, 16)) return wrap<__vector signed char>{};
      else if constexpr (size_check(2,  8)) return wrap<__vector signed short>{};
      else if constexpr (size_check(4,  4)) return wrap<__vector signed int>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8, 2)) return wrap<__vector signed long>{};
      }
      else
      {
        if constexpr (size_check(8, 1)) return emulated_{};
      }
    }
    else if constexpr (std::unsigned_integral<T>)
    {
      if      constexpr (size_check(1, 16)) return wrap<__vector unsigned char>{};
      else if constexpr (size_check(2,  8)) return wrap<__vector unsigned short>{};
      else if constexpr (size_check(4,  4)) return wrap<__vector unsigned int>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8, 2)) return wrap<__vector unsigned long>{};
      }
      else
      {
        if constexpr (size_check(8, 1)) return emulated_{};
      }
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

    if constexpr (std::is_same_v<T,float> && N::value <= 4)
    {
      return wrap<__vector __bool int>{};
    }
    else if constexpr (std::is_same_v<T,double> && N::value <= 2 )
    {
      if constexpr (spy::simd_instruction_set >= spy::vsx_) return wrap<__vector __bool long>{};
      else                                                  return emulated_{};
    }
    else if constexpr (std::is_integral_v<T> )
    {
      if      constexpr (size_check(1, 16))  return wrap<__vector __bool char>{};
      else if constexpr (size_check(2, 8 ))  return wrap<__vector __bool short>{};
      else if constexpr (size_check(4, 4 ))  return wrap<__vector __bool int>{};
      else if constexpr (spy::simd_instruction_set >= spy::vsx_)
      {
        if constexpr (size_check(8,2))  return wrap<__vector __bool long>{};
      }
      else
      {
        if constexpr (size_check(8, 2)) return emulated_{};
      }
    }
  }
}
