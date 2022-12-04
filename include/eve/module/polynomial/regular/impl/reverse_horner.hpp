//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/reverse_horner_impl.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
//================================================================================================
//== reverse Horner with ranges
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), T0 xx, R const& r) noexcept
-> common_value_t<T0, typename R::value_type>
{
  return detail::reverse_horner_impl(regular_type(), xx, r);
}

//================================================================================================
//== variadic
//================================================================================================

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
-> decltype(reverse_horner_impl(regular_type(), x, args...))
{
  return reverse_horner_impl(regular_type(), x, args...);
}

//================================================================================================
//== tuples
//================================================================================================

template<value T0, kumi::product_type Ts>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), T0 x, Ts args) noexcept
{
  return horner(x, kumi::reverse(args));
}

template<decorator D, value T0, kumi::product_type Ts>
EVE_FORCEINLINE constexpr auto
reverse_horner_(EVE_SUPPORTS(cpu_), D const & d, T0 x, Ts args) noexcept
{
  return d(horner)(x, kumi::reverse(args));
}

}
