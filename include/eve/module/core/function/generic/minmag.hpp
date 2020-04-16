//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_MINMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_MINMAG_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/min.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/saturated.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U,  typename D>
  EVE_FORCEINLINE  auto minmag_(EVE_SUPPORTS(cpu_)
                               , D const &
                               , T const &a
                               , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(D()(minmag), a, b);
  }

  template<real_value T,  typename D>
  EVE_FORCEINLINE  auto minmag_(EVE_SUPPORTS(cpu_)
                               , D const &
                               , T const &a
                               , T const &b) noexcept
  {
    if constexpr (std::is_same_v<D, numeric_type>)
    {
      auto aa = if_else(is_nan(a), b, a);
      auto bb = if_else(is_nan(b), a, b);
      auto z =  minmag(aa, bb);
      return z;
    }
    else
    {
      using D1 = std::conditional_t<std::is_same_v<D, pedantic_type>, saturated_type, regular_type>;
      auto aa = D1()(eve::abs)(a);
      auto bb = D1()(eve::abs)(b);
      if constexpr(simd_value<T>)
      {
        auto tmp = if_else(is_not_greater_equal(bb, aa), b, D()(eve::min)(a, b));
        return if_else(is_not_greater_equal(aa, bb),a, tmp);
      }
      else
      {
        return aa < bb ? a : bb < aa ? b : D()(eve::min)(a, b);
      }
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto minmag_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(regular_type()(minmag), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto minmag_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return minmag(regular_type(), a, b);
  }
}

#endif
