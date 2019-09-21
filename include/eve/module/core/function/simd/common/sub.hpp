//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SUB_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SUB_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/max.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/valmax.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto sub_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::sub, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::sub, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      static_assert(wrong<T, U>, "[eve::sub] - no support for current simd api");
      return {};
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::sub(abi_cast<U>(a), abi_cast<T>(b) );
    } 
  }

  template<typename T, typename U>
  EVE_FORCEINLINE  auto sub_(EVE_SUPPORTS(cpu_)
                            , saturated_type const & st
                            , T const &a
                            , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::sub, st, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::sub, st, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        using vt_t = value_type_t<T>; 
        if constexpr(std::is_integral_v<vt_t>)
        {
          if constexpr(std::is_signed_v<vt_t>)
          {
            if constexpr( sizeof(vt_t) >= 4)
            {
              using su_t =  std::conditional_t<sizeof(vt_t) == 4, uint32_t, uint64_t>; 
              using u_t = wide < su_t, typename T::cardinal_type, t_abi>;
              u_t ux = bitwise_cast<u_t>(a);
              u_t uy = bitwise_cast<u_t>(b);
              u_t res = ux - uy;
              
              ux = shr(ux, sizeof(vt_t)*8-1) +  u_t(Valmax<vt_t>());
              return  bitwise_cast<T>(if_else(is_ltz(bitwise_cast<T>(bitwise_and(bitwise_xor(ux,uy)
                                                                                , bitwise_xor(ux,res))))
                                             , ux, res));
            }
             else return map( eve::sub, st, a, b); 
          }
          else // if  constexpr(std::is_unsigned_v<vt_t>)
          {
            T r  = a - b;
            return bitwise_and(r, bitwise_mask(is_less_equal(r, a)));
          }
        }
        else return map( eve::sub, st, a, b);
      }
      else
      {
        static_assert(wrong<T, U>, "[saturated_(eve::sub)] - no support for current simd api");
        return {};
      }
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::sub(st, abi_cast<U>(a), abi_cast<T>(b) );
    }
  }
}


namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator-(T const &v0, U const &v1) noexcept -> decltype( eve::sub(v0,v1) )
  {
    return eve::sub(v0, v1);
  }
}

#endif

#include "if_sub.hpp"
