//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_select.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/minus.hpp>

namespace eve::detail
{
  template<value T, value U, value V>
  EVE_FORCEINLINE auto if_else_(T const & cond, U const & t, V const & f )
    requires compatible_values<U, V>
  {
    if constexpr(scalar_value<T>)
    {
           if constexpr(simd_value<U> && simd_value<V>) return  cond ? t : f;
      else if constexpr(simd_value<U>) return  cond ? t : U(f);
      else if constexpr(simd_value<V>) return  cond ? V(t) : f;
      else                             return  cond ? t : f;
    }
    else if constexpr(simd_value<T>)
    {
           if constexpr(has_aggregated_abi_v<V>||has_aggregated_abi_v<U>) return aggregate(if_else, cond, t, f);
      else if constexpr(has_emulated_abi_v<V>||has_emulated_abi_v<U>)   return map(if_else, cond, t, f);
      else if constexpr(scalar_value<U> && scalar_value<V>)
      {
        using r_t =  as_wide_t<element_type_t<U>, cardinal_t<T>>;
        return  if_else(is_nez(cond), r_t(t), r_t(f));
      }
      else if constexpr(simd_value<U> && scalar_value<V>)
      {
        return if_else(is_nez(cond), t, U(f));
      }
      else if constexpr(scalar_value<U> && simd_value<V>)
      {
        return if_else(is_nez(cond), V(t), f);
      }
    }
  }

  template<value T, value U>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_)
                               , T const &cond
                               , U const &t
                               , U const &f) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return cond ? t : f;
    }
    else
    {
           if constexpr(has_aggregated_abi_v<T>||has_aggregated_abi_v<U>) return aggregate(if_else, cond, t, f);
      else if constexpr(has_emulated_abi_v<T>||has_emulated_abi_v<U>)   return map(if_else, cond, t, f);
      else if constexpr(scalar_value<U>)
      {
        using r_t =  as_wide_t<element_type_t<U>, cardinal_t<T>>;
        return if_else(bit_mask(cond), r_t(t), r_t(f));
      }
      else
      {
        auto cond_mask = bit_mask(cond);
        return bit_select(cond_mask, t, f);
      }
    }
  }


  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,zero},{zero,t})
  template<value T, value U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_zero_ const
                                          &) noexcept
  //requires has_native_abi_v<T> && bit_compatible_values<T, U>
  {
    if constexpr(scalar_value<T>) return  static_cast<bool>(cond) ? t : U(0);
    else                                  return bit_and(t, bit_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_zero_ const &,
                                          U const &t) noexcept
  // requires has_native_abi_v<T> && bit_compatible_values<T, U>
  {
     if constexpr(scalar_value<T>) return static_cast<bool>(cond) ? U(0) : t;
     else                          return bit_andnot(t, bit_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,allbits},{allbits,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_allbits_ const
                                          &) noexcept
  {
    if constexpr(scalar_value<T>) return  static_cast<bool>(cond) ? t : Allbits(as(t));
    else                          return bit_ornot(t, bit_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_allbits_ const &,
                                          U const &t) noexcept
  {
    if constexpr(scalar_value<T>) return static_cast<bool>(cond) ? Allbits(as(t)) : t;
    else                          return bit_or(t, bit_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,mone},{mone,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_mone_ const
                                          &) noexcept
  {
    if constexpr(scalar_value<T>)        return  static_cast<bool>(cond) ? t : Mone(as(t));
    else if constexpr(integral_value<U>) return bit_ornot(t, bit_mask(cond));
    else                                 return if_else(cond, t, eve::Mone<U>());
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_mone_ const &,
                                          U const &t) noexcept
  {
    if constexpr(scalar_value<T>)        return  static_cast<bool>(cond) ? Mone(as(t)) : t;
    else if constexpr(integral_value<U>) return bit_or(t, bit_mask(cond));
    else                                 return if_else(cond, Mone(as(t)), t);
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,one},{one,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_one_ const
                                          &) noexcept
  {
    if constexpr(scalar_value<T>)       return  static_cast<bool>(cond) ? t : One(as(t));
    else if constexpr(std::is_integral_v<U>) return minus(bit_ornot(minus(t), bit_mask(cond)));
    else                                return if_else(cond, t, One(as(t)));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_one_ const &,
                                          U const &t) noexcept
  {
    if constexpr(scalar_value<T>)       return  static_cast<bool>(cond) ? One(as(t)) : t;
    else if constexpr(std::is_integral_v<U>) return minus(bit_or(minus(t), bit_mask(cond)));
    else                                return if_else(cond, One(as(t)), t);
  }
}
