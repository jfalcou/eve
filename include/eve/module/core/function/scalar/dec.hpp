//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_DEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_DEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto dec_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept Requires(T, Vectorizable<T>)
  {
    return static_cast<T>(a - One<T>());
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr auto
  dec_(EVE_SUPPORTS(cpu_), U const &cond, T const &a) noexcept Requires(T,
                                                                        Vectorizable<T>,
                                                                        Vectorizable<U>)
  {
    if(std::is_integral_v<T>)
      return static_cast<T>(a + bit_mask(T(cond)));
    else
      return cond ? dec(a) : a;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  dec_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a) noexcept Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return dec(a);
    else
      return (a != Valmin(as(a))) ? dec(a) : a;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated Masked case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  dec_(EVE_SUPPORTS(cpu_),
       U const &cond,
       saturated_type const &,
       T const &a) noexcept Requires(T, Vectorizable<T>, Vectorizable<U>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return cond ? dec(a) : a;
    else
      return ((Valmin(as(a)) != a) && cond) ? dec(a) : a;
  }
}

#endif
