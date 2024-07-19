//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/maxexponent.hpp>
#include <eve/module/core/constant/minexponent.hpp>
#include <eve/module/core/constant/nbmantissabits.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <type_traits>

namespace eve::detail
{
template<typename T, floating_value U, callable_options O>
constexpr auto ldexp_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b)
requires(std::same_as<element_type_t<T>, element_type_t<U>>)
{
  return ldexp[o](a, convert(trunc(b), as_element<as_integer_t<T>>{}));
}

template<typename T, integral_value U, callable_options O>
constexpr auto ldexp_(EVE_REQUIRES(cpu_), O const& o, T a, U b)
{
  if constexpr(O::contains(pedantic2))
  {
    // No denormal supported at platform level means pedantic is no-op
    if constexpr( !eve::platform::supports_denormals ) return ldexp(a,b);
    else
    {
      using i_t  = as_integer_t<element_type_t<T>>;
      if constexpr(scalar_value<T> != scalar_value<U>)
      {
        using w_t  = as_wide_as_t<T,U>;
        using wi_t = std::conditional_t<simd_value<U>, U, wide<i_t,cardinal_t<T>>>;

        return ldexp[o]( w_t(a), wi_t(b) );
      }
      else
      {
        auto v = convert(b, as<i_t>{});
        auto denormal = v < i_t(minexponent(eve::as_element<T>{}));

        if( eve::any(denormal) )
        {
          v         = sub[denormal](v, i_t(minexponent(as_element<T>{})));
          auto test = v == i_t(maxexponentp1(as_element<T>()));
          v  = dec[test](v);
          v += convert(maxexponent(as_element<T>{}),as<i_t>{});
          v <<= nbmantissabits(as_element<T>{});

          auto f    = if_else(denormal, smallestposval(as_element<T>()), eve::one);
          f  = inc[test](f);

          return a * bit_cast(v, as<T>{}) * f;
        }
        else return ldexp(a, b);
      }
    }
  }
  else
  {
    using elt_t = element_type_t<T>;
    using i_t   = as_integer_t<T>;
    using shf_t = std::conditional_t<simd_value<T>, T, elt_t>;

    auto  bb   = convert(b, as<element_type_t<i_t>>{});
    auto  ik   = bb + maxexponent(as<shf_t>());
          ik <<= nbmantissabits(as<shf_t>());
    return a * bit_cast(ik, as<as_wide_as_t<T,U>>());
  }
}
}
