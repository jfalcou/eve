//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/gcd.hpp>
#include <eve/function/if_else.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<integral_real_value T, integral_real_value U>
  EVE_FORCEINLINE auto lcm_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(lcm, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T lcm_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( !b || !a ) return T(0);
        return b / gcd(a, b) * a;
      }
      else
      {
        return a* (b / gcd(a, if_else(b, b, eve::mone)));
      }
    }
    else
      return apply_over(lcm, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // raw case
  template<integral_real_value T, integral_real_value U, decorator D>
  EVE_FORCEINLINE auto lcm_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(D()(lcm), a, b);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE T lcm_(EVE_SUPPORTS(cpu_), D const &, T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( !b || !a ) return T(0);
        return b / gcd(a, b) * a;
      }
      else
      {
        return a*(b / D()(gcd)(a, if_else(b, b, eve::mone)));
      }
    }
    else
      return apply_over(lcm, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // decorated case
  template<value T, value U, typename D>
  EVE_FORCEINLINE auto lcm_(EVE_SUPPORTS(cpu_), const D &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(lcm, a, b);
  }

  template<value T, decorator D>
  EVE_FORCEINLINE T lcm_(EVE_SUPPORTS(cpu_), D const &, T a, T b) noexcept
  {
    if constexpr(floating_value<T>)
      return lcm(D()(round)(a), D()(round)(b));
    else
      return lcm(a, b);
  }

  template<value T>
  EVE_FORCEINLINE auto lcm_(EVE_SUPPORTS(cpu_), upgrade_converter const &, T a, T b) noexcept
  {
    using elt_t =  element_type_t<T>;
    using up_t = upgrade_t<T>;
    using fup_t = upgrade_t<as_floating_point_t<T>>;
    if constexpr(integral_value<T>)
    {
      auto r = raw(lcm)(to_<fup_t>(a),to_<fup_t>(b));
      return convert(r, as<element_type_t<up_t>>());
    }
    else if constexpr(std::is_same_v<elt_t, float>)
    {
      auto r = lcm(to_<fup_t>(a),to_<fup_t>(b));
      return convert(r, as<element_type_t<up_t>>());
    }
    else // double element
    {
      return lcm(a, b);
    }
  }

}
