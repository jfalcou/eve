//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, integral_scalar_value U>
  [[nodiscard]] EVE_FORCEINLINE auto rotl_(EVE_SUPPORTS(cpu_), T a0, U nn) noexcept
  {
    if( nn == 0 )  return a0;
    constexpr U width = sizeof(T) * 8 - 1;
    int n = nn & width;
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

  template<unsigned_simd_value T, integral_scalar_value U>
  [[nodiscard]] EVE_FORCEINLINE auto rotl_(EVE_SUPPORTS(cpu_), T a0, U nn) noexcept
  {
    if( nn == 0 ) return a0;
    if constexpr( has_native_abi_v<T>)
    {
      using elt_t       = element_type_t<T>;
      constexpr U width = sizeof(elt_t) * 8 - 1;
      int n = nn & width;
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
    else
    {
      return apply_over(rotl, a0, nn);
    }
  }

  template<unsigned_scalar_value T, integral_simd_value U>
  EVE_FORCEINLINE auto rotl_(EVE_SUPPORTS(cpu_), T a0, U n) noexcept
  {
    if constexpr( has_native_abi_v<U> )
    {
      using r_t = wide<T, cardinal_t<U>>;
      return rotl(r_t(a0), n);
    }
   else
    {
      return apply_over(rotl, a0, n);
    }
  }

  template<unsigned_simd_value T, integral_simd_value U>
  [[nodiscard]] EVE_FORCEINLINE auto rotl_(EVE_SUPPORTS(cpu_), T a0, U n) noexcept
  {
    if constexpr( has_emulated_abi_v<T> || has_emulated_abi_v<U> )
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
    else //if constexpr( has_native_abi_v<T> && has_native_abi_v<U> )
    {
      return map(eve::rotl, a0, n);
    }
  }

  template<conditional_expr C, unsigned_value T0, integral_real_value T1>
  auto rotl_(EVE_SUPPORTS(cpu_), C const &cond, T0 a0, T1 a1)
  {
   return mask_op(  cond, eve::rotl, a0, a1);
  }
}
