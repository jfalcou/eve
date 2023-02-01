//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/dd/regular/traits.hpp>
#include <eve/module/dd/detail/utilities.hpp>


namespace eve::detail
{

  //trivial but needed
  template<typename Tag, typename ...Zs>
  EVE_FORCEINLINE constexpr auto
  trivial_dd_converter(Tag const &, Zs const& ...zs) noexcept
  {
    detail::callable_object<Tag> func;
    return func(eve::as_dd_t<Zs>(zs) ...);
   }

  //rec
  template<value T>
  EVE_FORCEINLINE constexpr auto
  rec_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    return trivial_dd_converter(eve::tag::rec_{}, z);
  }

  //frexp
  template<value T>
  EVE_FORCEINLINE constexpr auto
  frexp_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    if  constexpr(is_dd_v<T>)
      return frexp(z);
    else
    {
      auto [h, n] = frexp(z);
      return kumi::tuple{Z(h), n};
    }
  }

  //next
  template<value T>
  EVE_FORCEINLINE constexpr auto
  next_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    return trivial_dd_converter(eve::tag::next_{}, z);
  }

  //prev
  template<value T>
  EVE_FORCEINLINE constexpr auto
  prev_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    return trivial_dd_converter(eve::tag::prev_{}, z);
  }

  //sqr
  template<value T>
  EVE_FORCEINLINE constexpr auto
  sqr_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    if constexpr(is_dd_v<T>)
      return sqr(z);
    else if(floating_ordered_value<T>)
      return make_dd(two_sqr(z));
  }

  template<value T>
  EVE_FORCEINLINE constexpr auto
  sqrt_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    return trivial_dd_converter(eve::tag::sqrt_{}, z);
  }

//   //================================================================================================
//   //  Binary functions
//   //================================================================================================

  template<value T>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return add(a, b);
    else if(floating_ordered_value<T>)
      return make_dd(a, b);
  }

  template<value T>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return sub(a, b);
    else if(floating_ordered_value<T>)
      return make_dd(a, -b);
  }

  template<value T>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return sub(a, b);
    else if(floating_ordered_value<T>)
      return make_dd(two_prod(a, b));
  }

  template<value T>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return div(a, b);
    else if(floating_ordered_value<T>)
      return a*domain::dd(rec)(b);
  }

  template<value T>
  EVE_FORCEINLINE auto
  negate_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return negate(a, b);
    else if(floating_ordered_value<T>)
      return domain::dd(mul)(a, sign(b));
  }

  template<value T>
  EVE_FORCEINLINE auto
  negatenz_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, T const & b) noexcept
  {
    if constexpr(is_dd_v<T>)
      return negatenz(a, b);
    else if(floating_ordered_value<T>)
      return domain::dd(mul)(a, signnz(b));
  }

  template<value T, integral_value N>
  EVE_FORCEINLINE auto
  ldexp_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& a, N const & n) noexcept
  {
    if constexpr(is_dd_v<T>)
      return ldexp(a, n);
    else if(floating_ordered_value<T>)
      return as_dd_t<T>(ldexp(a, n));
  }

}
