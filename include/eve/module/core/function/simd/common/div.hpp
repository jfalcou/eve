//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/trunc.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>
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
    else if constexpr( is_Vectorized_v<T> ^ is_Vectorized_v<U> )
    {
      return eve::div(abi_cast<U>(a), abi_cast<T>(b) );
    }
    else if constexpr( is_Vectorized_v<T> && is_Vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr( std::is_floating_point_v<value_type_t<T>> )
        {
          return mul(abi_cast<U>(a),rec( abi_cast<T>(b)));
        }
        else
        {
          if constexpr(sizeof(T) == 8)
          {
            return map( eve::div, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b) );
          }
          else if constexpr(sizeof(T) == 4)
          {
             return convert(div(convert(a, double_)), convert(b, double_), as <value_type_t<T>>());
          }
          else //if constexpr(sizeof(T) <  4)
          {
            return convert(div(convert(a, single_)), convert(b, single_), as <value_type_t<T>>());
          }
          
        }
      }
     return T(); 
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , saturated_type const & st
                            , T const &a
                            , U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( saturated_(eve::div), abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( saturated_(eve::div), abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_Vectorized_v<T> && !is_Vectorized_v<U> )
    {
      return saturated_(div)(a, T(b)); 
    }
    else if constexpr( !is_Vectorized_v<T> && is_Vectorized_v<U> )
    {
      return saturated_(div)(U(a), b); 
    }
    else if constexpr( is_Vectorized_v<T> ^ is_Vectorized_v<U> )
    {
      return eve::div(st, abi_cast<U>(a), abi_cast<T>(b) );
    }
    else if constexpr( is_Vectorized_v<T> && is_Vectorized_v<U> )
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
          const T x2 = bit_xor(Valmax<T>(), shr(x, sizeof(sT)*8-1));
          x = if_else(logical_and(iseqzb, is_nez(x)), x2, x);
          const T y = if_else(iseqzb, One<T>(), b);
          return div(x, y);
        }
        else
        {
          auto iseqzb = is_eqz(b);
          auto bb = if_else(iseqzb, One(as(a)), b);
          auto aa = if_else(iseqzb, bit_mask(a), a);
          return div(aa, bb);
        }
      }
      return T();
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

// #include <eve/module/core/function/simd/common/div_upward.hpp>
// #include <eve/module/core/function/simd/common/div_downward.hpp>
// #include <eve/module/core/function/simd/common/div_towards_zero.hpp>
// #include <eve/module/core/function/simd/common/div_to_nearest.hpp>
#include <eve/module/core/function/simd/common/if_div.hpp>
