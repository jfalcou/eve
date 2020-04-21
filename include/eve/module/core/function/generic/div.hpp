//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <limits>

#ifdef EVE_COMP_IS_MSVC
#pragma warning(push)
#pragma warning(disable: 4723) // potential divide by 0
#endif

#include <eve/module/core/function/generic/div_upward.hpp>
#include <eve/module/core/function/generic/div_downward.hpp>
#include <eve/module/core/function/generic/div_tonearest.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////
  // general decorated
  template<real_value T, real_value U, typename D>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , D  const &
                            , T const &a
                            , U const &b
                            ) noexcept -> decltype(div(a, b))
  requires compatible_values<T, U>
  {
    return arithmetic_call(D()(div), a, b);
  }

  //////////////////////////////////////////////////////////////////////
  // toward_zero
  template<real_value T>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , toward_zero_type  const &
                            , T const &a
                            , T const &b
                            ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_real_value<T>) return trunc(div(a, b));
      else                                 return       div(a, b);
    }
    else return apply_over(toward_zero_(div), a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_)
                            , saturated_type const &
                            , T const &a
                            , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(floating_real_value<T>) return div(a, b);
    else if constexpr( signed_integral_value<T> )
    {
      if constexpr(scalar_value<T>)
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto aa = a + !((b + One(as(a))) | ((ui_t)a + Valmin(as(a))));
        if (b) return aa/b;
        else if (a) return Valmax(as(a)) + ((ui_t)a >> (sizeof(T)*8-1));
        else        return Zero(as(a));
      }
      else if constexpr( simd_value<T>)
      {
        constexpr int shft = sizeof(element_type_t<T>)*8-1;
        auto iseqzb = is_eqz(b);
        // replace valmin/-1 by (valmin+1)/-1
        auto x = inc[logical_not(inc(b) | (a + Valmin<T>()))](a);
        // negative -> valmin
        // positive -> valmax
        auto x2 = bit_xor(Valmax<T>(), shr(x, shft));
        x = if_else(logical_and(iseqzb, is_nez(x)), x2, x);
        auto y = if_else(iseqzb, One<T>(), b);
        return div(x, y);
      }
    }
    else if constexpr(unsigned_value<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return b ? a/b : bit_mask(a);
      }
      else if constexpr( simd_value<T>)
      {
        auto iseqzb = is_eqz(b);
        auto bb = if_else(iseqzb, One(as(a)), b);
        auto aa = if_else(iseqzb, bit_mask(a), a);
        return div(aa, bb);
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_)
                           , T const & cond
                           , U const & t
                           , V const & f) noexcept
  requires compatible_values<U, V>
  {
    if constexpr(has_native_abi_v<T>)
    {
      using r_t = decltype(div(t, f));
           if constexpr(scalar_value<T>) return  cond ? div(t, f) : r_t(t);
      else if constexpr(simd_value<T>)   return  div(t, if_else(cond, r_t(f), eve::one_));
    }
    else return apply_over(div, cond, t, f);
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_)
                           , T const & cond
                           , saturated_type const &
                           , U const &t
                           , V const & f) noexcept
  requires compatible_values<U, V>
  {
    if constexpr(has_native_abi_v<T>)
    {
      using r_t = decltype(div(t, f));
           if constexpr(scalar_value<T>) return cond ? saturated_(div)(t, f) : r_t(t);
      else if constexpr(simd_value<T>)   return saturated_(div)(t, if_else(cond, r_t(f), eve::one_));
    }
    else return apply_over(saturated_(div), cond, t, f);

  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_)
                           , not_t<T> const & cond
                           , U const & t
                           , V const & f) noexcept
  requires compatible_values<U, V>
  {
    if constexpr(has_native_abi_v<T>)
    {
      using r_t = decltype(div(t, f));
           if constexpr(scalar_value<T>) return  cond.value ? r_t(t) : div(t, f);
      else if constexpr(simd_value<T>)   return  div(t, if_else(cond.value, eve::one_, r_t(f)));
    }
    else return apply_over(div, cond, t, f);
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_)
                           ,  not_t<T> const & cond
                           , saturated_type const &
                           , U const & t
                           , V const & f) noexcept
  requires compatible_values<U, V>
  {
    if constexpr(has_native_abi_v<T>)
    {
      using r_t = decltype(div(t, f));
           if constexpr(scalar_value<T>) return cond.value ? r_t(t) : saturated_(div)(t, f);
      else if constexpr(simd_value<T>)   return saturated_(div)(t, if_else(cond.value, eve::one_, r_t(f)));
    }
    else return apply_over(saturated_(div), cond, t, f);
  }
}

#ifdef EVE_COMP_IS_MSVC
# pragma warning(pop)
#endif

#endif
