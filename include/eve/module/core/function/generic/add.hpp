//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ADD_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/shr.hpp>

#include <limits>

namespace eve::detail
{
  //================================================================================================
  // saturated case
  //================================================================================================
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated_(add), a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( floating_value<T> )
    {
      return a + b;
    }
    else if constexpr( signed_integral_value<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        // large signed integral case
        using u_t = std::make_unsigned_t<T>;
        enum sizee
        {
          value = sizeof(T) * 8 - 1
        };

        u_t ux = a, uy = b;
        u_t res = ux + uy;

        ux = (ux >> sizee::value) + std::numeric_limits<T>::max();

        if( T((ux ^ uy) | ~(uy ^ res)) >= T(0) )
          return static_cast<T>(ux);
        return static_cast<T>(res);
      }
      else
      {
        // small signed integral case
        auto r = a + b;
        return static_cast<T>(saturate(r, as_<T>()));
      }
    }
    else // if constexpr( std::is_unsigned_v<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        // large unsigned integral case
        T r = a + b;
        return r | -(r < a);
      }
      else
      {
        // small unsigned integral case - use C promotion then clamp
        auto        r  = a + b;
        decltype(r) mx = std::numeric_limits<T>::max();
        return static_cast<T>(std::min(mx, r));
      }
    }
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr( floating_value<T> )
    {
      return a + b;
    }
    else if constexpr( integral_value<T> )
    {
      if constexpr( signed_integral_value<T> )
      {
        using vt_t = value_type_t<T>;
        if constexpr( sizeof(vt_t) >= 4 )
        {
          using su_t = std::conditional_t<sizeof(vt_t) == 4, uint32_t, uint64_t>;
          using u_t  = wide<su_t, cardinal_t<T>, abi_type_t<T>>;
          auto ux    = bit_cast(a, as_<u_t>());
          auto uy    = bit_cast(b, as(ux));
          u_t  res   = ux + uy;

          ux = shr(ux, sizeof(vt_t) * 8 - 1) + u_t(Valmax<vt_t>());
          return bit_cast(
              if_else(
                  is_gez(bit_cast(bit_ornot(bit_xor(ux, uy), bit_xor(uy, res)), as(a))), ux, res),
              as(a));
        }
        else
        {
          return map(saturated_(add), a, b);
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        T r = a + b;
        return bit_or(r, bit_mask(is_less(r, a)));
      }
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto add_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(add(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? add(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return add(r_t(t), if_else(cond, r_t(f), eve::zero_));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), T const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(add(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? saturated_(add)(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return saturated_(add)(r_t(t), if_else(cond, r_t(f), eve::zero_));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), not_t<T> const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(add(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : add(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return add(r_t(t), if_else(cond.value, eve::zero_, r_t(f)));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto add_(EVE_SUPPORTS(cpu_),
                            not_t<T> const &cond,
                            saturated_type const &,
                            U const &t,
                            V const &f) noexcept requires compatible_values<U, V>
  {
    using r_t = decltype(add(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : saturated_(add)(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return saturated_(add)(r_t(t), if_else(cond.value, eve::zero_, r_t(f)));
    }
  }
}

#endif
