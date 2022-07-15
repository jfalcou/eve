//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/reverse_horner_impl.hpp>

namespace eve::detail
{
//================================================================================================
//== reverse Horner with ranges
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), T0 xx, R const& r) noexcept
    requires(compatible_values<T0, typename R::value_type> && (!simd_value<R>))
{
  return detail::reverse_horner_impl(regular_type(), xx, r);
}

//================================================================================================
//== variadic
//================================================================================================

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
{
  return reverse_horner_impl(regular_type(), x, args...);
}
}
