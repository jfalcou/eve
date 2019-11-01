//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_TO_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_TO_NEAREST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/inearest.hpp>  
#include <eve/function/rec.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/logical_ornot.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/saturated.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto div_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b
                            , to_nearest_type const & tnt_
                            ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::div, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b), tnt_);
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::div, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b), tnt_ );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        using v_t = value_type_t<T>; 
        if constexpr(std::is_floating_point_v<v_t>)
        {
          return nearest(a/b);
        }
        else if constexpr(std::is_signed_v<v_t>)
        {
          if constexpr(std::is_same_v<v_t, std::int64_t>)
          {
            auto aa = saturated_(eve::abs)(a);
            auto bb = saturated_(eve::abs)(b);
            bb = if_else(is_eqz(bb), eve::allbits_, bb);
            auto q = eve::saturated_(eve::div)(aa, bb); 
            auto rx2 = 2*(aa-q*bb);
            q = if_else (is_greater_equal(rx2, bb)
                        , inc[logical_ornot(rx2 != bb, is_even(q))](q)
                        , q); 
            return if_else(is_nez(b)
                          , eve::copysign(q, a^b) 
                          , if_else(is_eqz(a)
                                   , eve::zero_
                                   , if_else(is_gtz(a)
                                            , Valmax<T>()
                                            , Valmin<T>()
                                            )
                                   )
                          ); 
          }
          else
          {
            return if_else(is_nez(b)
                          , saturated_(convert)(inearest(convert(a, double_)/
                                                      convert(b, double_)), as<v_t>())
                          , if_else(is_eqz(a)
                                   , eve::zero_
                                   , if_else(is_gtz(a)
                                            , Valmax<T>()
                                            , Valmin<T>()
                                            )
                                   )
                          ); 
          }
        }
        else // if constexpr(std::is_unsigned_v<v_t>)
        {
          auto bb = if_else(is_eqz(b), eve::allbits_, b); 
          T q = div(a, bb);
          T rx2 = 2*(a-q*bb);
          q = if_else(is_greater_equal(rx2, bb)
                     ,inc[logical_ornot(rx2 != bb, is_even(q))](q)
                     , q); 
          return if_else(is_nez(b), q, bitwise_mask(a));         
        }
        return T();
      }
      else //if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
      {
        return eve::div(abi_cast<U>(a), abi_cast<T>(b), tnt_ );
      }
    }
  }
}

#endif
