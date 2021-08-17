//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/minmag.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/two_add.hpp>
#include <eve/function/two_prod.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  fma_(EVE_SUPPORTS(cpu_), numeric_type const &
      , T const &a, U const &b, V const &c) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(numeric(fma), a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE T fma_(EVE_SUPPORTS(cpu_), numeric_type const &
                        , T const &a, T const &b, T const &c) noexcept
  requires has_native_abi_v<T>
  {
    using elt_t = element_type_t<T>;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      return float32(float64(a)*float64(b)+float64(c));
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      auto amax    = maxmag(a, b);
      auto amin    = minmag(a, b);
      auto e0      = -(exponent(amax) >> 1);
      amax         = pedantic(ldexp)(amax, e0);
      auto c0      = pedantic(ldexp)(c, e0);
      auto [p, rp] = two_prod(amax, amin);
      auto [s, rs] = two_add(p, c0);
      return pedantic(ldexp)(s + (rp + rs), -e0);
    }
    else if constexpr( std::is_integral_v<elt_t> )
    {
      // correct fma has to ensure "no intermediate overflow".
      // This is done in the case of signed integers by transtyping to unsigned type
      // to perform the computations in a guaranted 2-complement environment
      // since signed integer overflows in C++ produce "undefined results"
      using u_t = as_integer_t<T, unsigned>;
      return bit_cast(fma(bit_cast(a, as<u_t>())
                         , bit_cast(b, as<u_t>())
                         , bit_cast(c, as<u_t>())),
                      as<T>());
    }
  }
}
