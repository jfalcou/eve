//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ADD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<typename T, typename U>
  EVE_FORCEINLINE  auto add_(EVE_SUPPORTS(cpu_)
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
      return map( eve::add, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::add, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      static_assert(wrong<T, U>, "[eve::add] - Missing implementation");
      return {};
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::add(abi_cast<U>(a), abi_cast<T>(b) );
    }
  }

  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<typename T, typename U>
  EVE_FORCEINLINE  auto add_(EVE_SUPPORTS(cpu_)
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
      return map( eve::add, st, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::add, st, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
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
              using su_t = std::conditional_t<sizeof(vt_t) == 4, uint32_t, uint64_t>;
              using u_t = wide < su_t, typename T::cardinal_type, t_abi>;
              auto ux = bit_cast(a,as_<u_t>());
              auto uy = bit_cast(b,as(ux));
              u_t  res = ux + uy;

              ux = shr(ux, sizeof(vt_t)*8-1) +  u_t(Valmax<vt_t>());
              return  bit_cast( if_else ( is_gez( bit_cast( bit_ornot ( bit_xor(ux,uy)
                                                                                  , bit_xor(uy,res)
                                                                                  )
                                                                  , as(a)
                                                                  )
                                                    )
                                             , ux, res
                                             )
                                  , as(a)
                                  );
            }
            else return map( eve::add, st, a, b);
          }
          else // if  constexpr(std::is_unsigned_v<vt_t>)
          {
            T r  = a + b;
            return bit_or(r, bit_mask(is_less(r, a)));
          }
        }
        else return map( eve::add, st, a, b);
      }
      else
      {
        static_assert(wrong<T, U>, "[saturated_(eve::add)] - no support for current simd api");
        return {};
      }
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::add(st, abi_cast<U>(a), abi_cast<T>(b) );
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator+(T const &a, U const &b) noexcept -> decltype( eve::add(a,b) )
  {
    return eve::add(a, b);
  }
}

#endif

#include "if_add.hpp"
