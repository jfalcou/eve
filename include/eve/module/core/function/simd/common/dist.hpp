//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>  
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE  auto dist_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return dist(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return dist(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::dist, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::dist, a, b);
        }
        else
        {
          return eve::max(a, b)-eve::min(a, b);
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::dist] - Incompatible types.");
        return {};
      }
    }
  }
   
  // -----------------------------------------------------------------------------------------------
  // saturated_type
  template<typename T, typename U>
  EVE_FORCEINLINE  auto dist_(EVE_SUPPORTS(cpu_)
                            , saturated_type const &
                            , T const &v0
                            , U const &v1) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return dist(saturated_, v0, T{v1});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return dist(saturated_, U{v0},v1);
    }
    else
    {
      if constexpr(std::is_integral_v<typename T::value_type> && std::is_signed_v<typename T::value_type>)
      {
        auto tmp = dist(v0, v1);
        return if_else(is_ltz(tmp), Valmax(as(v0)), tmp);
      }
      else
        return eve::dist(v0, v1);
    }
  }
}

#endif
