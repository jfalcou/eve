//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ADD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  add_(EVE_SUPPORTS(cpu_), T const &cond
      , U const &t
      , V const &f) noexcept
  requires( std::conditional_t<is_vectorized_v<U>,U,V>,
            detail::either<is_vectorized_v<V>, is_vectorized_v<U>>
          )
  {
    if constexpr(is_vectorized_v<T>)
    {
      return t + if_else(cond, abi_cast<U>(f), eve::zero_);
    }
    else return  cond ? t + f : t;
  }


  // -----------------------------------------------------------------------------------------------
  // Saturated Masked case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto add_(EVE_SUPPORTS(cpu_)
                           , T const & cond
                           , saturated_type const &
                           , U const &t
                           , V const & f) noexcept
  requires( std::conditional_t<is_vectorized_v<U>,U,V>,
            detail::either<is_vectorized_v<V>, is_vectorized_v<U>>
          )
  {
    if constexpr(is_vectorized_v<T>)
    {
      return saturated_(add)(t, if_else(cond, abi_cast<U>(f), eve::zero_));
    }
    else return  cond ? saturated_(add)(t, f) : t;
  }

}

#endif
