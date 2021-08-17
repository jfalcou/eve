//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/converter.hpp>

#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T, integral_value U>
  [[nodiscard]] EVE_FORCEINLINE auto rotl_(EVE_SUPPORTS(cpu_), T a0, U n) noexcept
  {
    if constexpr( has_native_abi_v<T> && scalar_value<U> )
    {
      if( n == 0 )
        return a0;
      using elt_t       = element_type_t<T>;
      constexpr U width = sizeof(elt_t) * 8 - 1;
      n &= width;
      if( n > 0 )
      {
        a0 = (a0 << n) | (a0 >> (-n & width));
      }
      else
      {
        n  = -n; // this is to allow the compiler to produce a ror instruction
        a0 = (a0 >> n) | (a0 << (-n & width));
      }
      return a0;
    }
    else if constexpr( scalar_value<T> && has_native_abi_v<U> )
    {
      using r_t = wide<T, cardinal_t<U>>;
      return rotl(r_t(a0), n);
    }
    // now none is scalar
    else if constexpr( has_emulated_abi_v<T> || has_emulated_abi_v<U> )
    {
      return map(rotl, a0, n);
    }
    else if constexpr( has_aggregated_abi_v<T> || has_aggregated_abi_v<U> )
    {
      if constexpr( std::is_same_v<T, U> )
      {
        return aggregate(rotl, a0, n);
      }
      else
      {
        using elt_t = element_type_t<T>;
        using elt_u = element_type_t<U>;
        using i_t = std::conditional_t<std::is_signed_v<elt_u>, as_integer_t<elt_t, signed>, elt_t>;
        return aggregate(rotl, a0, to_<i_t>(n));
      }
    }
    else if constexpr( has_native_abi_v<T> && has_native_abi_v<U> )
    {
      return map(eve::rotl, a0, n);
    }
  }

}
