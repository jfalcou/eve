//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto abs_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) { return bit_andnot(a, Mzero(as(a))); }
    else if constexpr(std::is_unsigned_v<T>)
    {
      return a;
    }
    else
    {
      return a < T(0) ? -a : a;
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  abs_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a) noexcept Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) return a < T(0) ? -a : a;
    if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>) return a;

    if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
      return (a == Valmin(as(a))) ? Valmax(as(a)) : eve::abs(a);
  }
}

#endif
