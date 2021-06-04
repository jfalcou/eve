//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/real/math/detail/generic/atan_kernel.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto atan2_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
    -> decltype(arithmetic_call(atan2, a, b)) 
  {
    return arithmetic_call(atan2, a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                             , T const &a0
                             , T const &a1
                             ) noexcept

  requires  has_native_abi_v<T>
  {
    auto q = eve::abs(a0/a1);
    auto z = detail::atan_kernel(q, eve::rec(q));
    return if_else(is_positive(a1), z, (pi(eve::as(a0))-z))*signnz(a0);
  }
}
