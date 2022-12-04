//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/horner_impl.hpp>

namespace eve::detail
{
//================================================================================================
//== Horner with iterators
//================================================================================================
template<value T0, std::input_iterator IT>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 xx, IT const& first, IT const& last) noexcept
-> decltype(detail::horner_impl(numeric_type(), xx, first, last))
{
  return detail::horner_impl(numeric_type(), xx, first, last);
}

//================================================================================================
//== Horner with iterators and leading unitary coefficient
//================================================================================================

template<value T0, std::input_iterator IT>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_),
        numeric_type const&,
        T0 xx,
        callable_one_ const&,
        IT const& first,
        IT const& last) noexcept
-> decltype(detail::horner_impl(numeric_type(), xx, one, first, last))
{
  return detail::horner_impl(numeric_type(), xx, one, first, last);
}

//================================================================================================
//== Horner with ranges
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 xx, R const& r) noexcept
-> decltype(detail::horner_impl(numeric_type(), xx, r))
{
  return detail::horner_impl(numeric_type(), xx, r);
}

//================================================================================================
//== Horner with ranges and leading unitary coefficient
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 xx, callable_one_ const&, R const& r) noexcept
-> decltype(detail::horner_impl(numeric_type(), xx, one, r))
{
  return detail::horner_impl(numeric_type(), xx, one, r);
}

//================================================================================================
//== Horner variadic N parameters (((..(a*x+b)*x+c)*x + ..)..)
//================================================================================================
template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 x, Ts... args) noexcept
{
  return horner_impl(numeric_type(), x, args...);
}

//================================================================================================
//== N parameters with unitary first coefficient (((..(a*x+b)*x+c)*x + ..)..)
//================================================================================================

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 x, callable_one_ const&, Ts... args) noexcept
{
  return horner_impl(numeric_type(), x, one, args...);
}

template<value T0, kumi::product_type Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 x, Ts tup) noexcept
{
  return kumi::apply( [&](auto... m) { return numeric(horner)(x, m...); }, tup);
}
}
