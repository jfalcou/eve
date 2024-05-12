//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fms.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
fsm_(EVE_SUPPORTS(cpu_),
     T const& a,
     U const& b,
     V const& c) noexcept
-> common_value_t<U, V, T>
{
  using r_t = common_value_t<T, U, V>;
  return arithmetic_call(fsm, r_t(a), r_t(b), r_t(c));
}

template<ordered_value T>
EVE_FORCEINLINE T
fsm_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& c) noexcept requires has_native_abi_v<T>
{
  return fms(b, c, a);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
fsm_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& c) noexcept
-> common_value_t<U, V, T>{
  using r_t = common_value_t<T, U, V>;
  return mask_op(cond, eve::fsm, r_t(a), r_t(b), r_t(c));
}

}
