//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/horner_impl.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
//================================================================================================
//== Horner with iterators
//================================================================================================

template<value T0, std::input_iterator IT>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 xx, IT const& first, IT const& last) noexcept
-> common_value_t<T0, typename std::iterator_traits<IT>::value_type>
{
  return detail::horner_impl(pedantic_type(), xx, first, last);
}

//================================================================================================
//== Horner with iterators and leading unitary coefficient
//================================================================================================

template<value T0, std::input_iterator IT>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_),
        pedantic_type const&,
        T0 xx,
        callable_one_ const&,
        IT const& first,
        IT const& last) noexcept
-> common_value_t<T0, typename std::iterator_traits<IT>::value_type>
{
  return detail::horner_impl(pedantic_type(), xx, one, first, last);
}

//================================================================================================
//== Horner with ranges
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 xx, R const& r) noexcept
-> common_value_t<T0, typename R::value_type>
{
  return detail::horner_impl(pedantic_type(), xx, r);
}

//================================================================================================
//== Horner with ranges and leading unitary coefficient
//================================================================================================
template<value T0, range R>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 xx, callable_one_ const&, R const& r) noexcept
-> common_value_t<T0, typename R::value_type>
{
  return detail::horner_impl(pedantic_type(), xx, one, r);
}

//================================================================================================
//== N parameters (((..(a*x+b)*x+c)*x + ..)..)
//================================================================================================

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 x, Ts... args) noexcept
-> decltype(horner_impl(pedantic_type(), x, args...))
{
  return horner_impl(pedantic_type(), x, args...);
}

//================================================================================================
//== N parameters with unitary leader coefficient (((..(x+b)*x+c)*x + ..)..)
//================================================================================================

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 x, callable_one_ const&, Ts... args) noexcept
-> decltype(horner_impl(pedantic_type(), x, one, args...))
{
  return horner_impl(pedantic_type(), x, one, args...);
}

template<value T0, kumi::product_type Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 x, Ts tup) noexcept
{
  return kumi::apply( [&](auto... m) { return pedantic(horner)(x, m...); }, tup);
}

}
