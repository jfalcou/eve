//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::div, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::div, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr( std::is_floating_point_v<value_type_t<T>> )
        {
          return mul(abi_cast<U>(a),rec( abi_cast<T>(b)));
        }
        else
        {
          return map( eve::div, abi_cast<value_type_t<U>>(a)
                    , abi_cast<value_type_t<T>>(b) );
        }
      }
    }
    else //if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::div(abi_cast<U>(a), abi_cast<T>(b) );
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , saturated_type const & st
                            , T const &a
                            , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::div, st, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::div, st, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && !is_vectorized_v<U> )
    {
      return saturated_(div)(a, T(b)); 
    }
    else if constexpr( !is_vectorized_v<T> && is_vectorized_v<U> )
    {
      return saturated_(div)(U(a), b); 
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr( std::is_floating_point_v<value_type_t<T>> )
        {
          return mul(abi_cast<U>(a),rec( abi_cast<T>(b)));
        }
        else if constexpr(std::is_signed_v<value_type_t<T>>)
        {
           using sT = value_type_t<T>;
          auto iseqzb = is_eqz(b);
          // replace valmin/-1 by (valmin+1)/-1
          auto x = inc[logical_not(inc(b) | (a + Valmin<T>()))](a);
          // negative -> valmin
          // positive -> valmax
          const T x2 = bitwise_xor(Valmax<T>(), shr(x, sizeof(sT)*8-1));
          x = if_else(logical_and(iseqzb, is_nez(x)), x2, x);
          const T y = if_else(iseqzb, One<T>(), b);
          return div(x, y);
        }
        else
        {
          auto iseqzb = is_eqz(b);
          auto bb = if_else(iseqzb, One(as(a)), b);
          auto aa = if_else(iseqzb, bitwise_mask(a), a);
          return div(aa, bb);
        }
      }
      return T();
     }
    else //if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::div(abi_cast<U>(a), abi_cast<T>(b) );
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator/(T const &v0, U const &v1) noexcept
  -> decltype( eve::div(v0,v1) )
  {
    return eve::div(v0, v1);
  }
}

#endif

#include <eve/module/core/function/simd/common/if_div.hpp>
