//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/forward.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto nextafter_(EVE_SUPPORTS(cpu_)
                                 , T const &x
                                 , U const &y) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>
          , either<is_vectorized_v<T>, is_vectorized_v<U>>
          , behave_as<totally_ordered, T>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::nextafter, abi_cast<value_type_t<U>>(x), abi_cast<value_type_t<T>>(y));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::nextafter, abi_cast<value_type_t<U>>(x), abi_cast<value_type_t<T>>(y));
    }
    else if constexpr(is_vectorized_v<T> && is_vectorized_v<U>)
    {
      return if_else(x < y,  next(x), if_else(y < x, prev(x), x)); 
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::pedantic_(eve::nextafter)(abi_cast<U>(x), abi_cast<T>(y));
    }  
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto nextafter_(EVE_SUPPORTS(cpu_)
                                 , pedantic_type const &   
                                 , T const &x
                                 , U const &y) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>
          , either<is_vectorized_v<T>, is_vectorized_v<U>>
          , behave_as<totally_ordered, T>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::pedantic_(eve::nextafter), abi_cast<value_type_t<U>>(x), abi_cast<value_type_t<T>>(y));
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::pedantic_(eve::nextafter), abi_cast<value_type_t<U>>(x), abi_cast<value_type_t<T>>(y));
    }
    else if constexpr(is_vectorized_v<T> && is_vectorized_v<U>)
    {
      if constexpr(std::is_floating_point_v<value_type_t<T>>)
        return if_else(is_unordered(x, y), eve::allbits_, nextafter(x, y));
      else
        return nextafter(x, y); 
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::pedantic_(eve::nextafter)(abi_cast<U>(x), abi_cast<T>(y));
    } 
  }
}

#endif
