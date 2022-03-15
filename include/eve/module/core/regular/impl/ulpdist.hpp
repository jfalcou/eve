//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/numeric/is_equal.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/numeric/is_equal.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto ulpdist_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(ulpdist, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T ulpdist_(EVE_SUPPORTS(cpu_)
                         , T const &a
                         , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(integral_value<T>)
    {
      return dist(a, b);
    }
    else if constexpr(scalar_value<T>)
    {
      if (numeric(is_equal)(a, b)) return T(0);
      if (is_unordered(a, b)) return nan(eve::as<T>());
      return nb_values(a , b )*half(eve::as(a));
    }
    else if constexpr(simd_value<T>)
    {
      auto aa = eve::detail::bitinteger(a);
      auto bb = eve::detail::bitinteger(b);
      return if_else(numeric(is_equal)(a, b), eve::zero
                    , if_else (is_unordered(a, b)
                              , eve::allbits
                              , to_<T>(dist(bb, aa))
                              )*half(eve::as(a))
                    );
    }
  }
}
