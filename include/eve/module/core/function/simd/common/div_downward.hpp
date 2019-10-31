//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_DOWNWARD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIV_DOWNWARD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/floor.hpp> 
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/shr.hpp>
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
                            , downward_type const & dwt_
                            ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::div, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b), dwt_);
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::div, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b), dwt_ );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        using v_t = value_type_t<T>; 
        if constexpr(std::is_floating_point_v<v_t>)
        {
          return floor(a/b);
        }
        else if constexpr(std::is_signed_v<v_t>)
        {
          if constexpr(std::is_same_v<v_t, std::int64_t>)
          {
            auto bb = if_else(is_eqz(b), eve::one_, b);
            auto q = saturated_(eve::div)(a, bb);
            auto r =a-q*b;
            q = saturated_(dec[is_nez(r)&&is_lez(bitwise_xor(a, b))])(q);
            return if_else(is_nez(b)
                          , q
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
                          , saturated_(convert)(ifloor(convert(a, double_)/
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
          T q = saturated_(div)(a, bb);
          q = dec[is_nez(a-q*b)](q); 
          return if_else(is_nez(b), q, bitwise_mask(a));
        }
        return T();
      }
      else //if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
      {
        return eve::div(abi_cast<U>(a), abi_cast<T>(b), dwt_ );
      }
    }
  }
}

#endif
