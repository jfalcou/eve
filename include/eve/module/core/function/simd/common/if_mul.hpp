//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/one.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  //-----------------------------------------------------------------------------------------------
  // masked case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  mul_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
  requires( std::conditional_t<is_vectorized_v<U>,U,V>,
            detail::either<is_vectorized_v<V>, is_vectorized_v<U>>
          )
  {
    return t * if_else(cond, abi_cast<U>(f), eve::one_);
  }

   //-----------------------------------------------------------------------------------------------
  //  Saturated Masked case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE  auto mul_( EVE_SUPPORTS(cpu_)
                            , T const &cond
                            , saturated_type const &
                            , U const &a
                            , V const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<U>,U,V>,
            detail::either<is_vectorized_v<V>, is_vectorized_v<U>>
          )
  {
    if constexpr(is_vectorized_v<T>) return if_else(cond, saturated_(mul)(a, b), a);
    else return cond ? saturated_(mul)(a, b) : a;
  }
}

#endif
