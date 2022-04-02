//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/constant/maxexponent.hpp>
#include <eve/module/core/constant/nbmantissabits.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <string>

namespace eve::detail
{
  template<int N, real_value T, value U>
  EVE_FORCEINLINE auto
  ldexp_(EVE_SUPPORTS(cpu_), diff_type<N> const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(diff_type<N>()(ldexp), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T , T y ) noexcept
  {
    return ldexp(T(1), int_(trunc(y)));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T  ) noexcept
  {

    return one(as(x));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<int N, conditional_expr C, floating_real_value T, real_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
                               , T const &t, U const & u ) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::ldexp), t, u);
  }
}
