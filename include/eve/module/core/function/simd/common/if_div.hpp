//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/one.hpp>
#include <eve/forward.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve::detail
{
  //-----------------------------------------------------------------------------------------------
  // masked
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE  auto
  div_( EVE_SUPPORTS(cpu_)
      , T const &cond
      , U const &a
      , V const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<U>,U,V>,
            detail::either<is_Vectorized_v<V>, is_Vectorized_v<U>>
          )
  {
    if constexpr(is_Vectorized_v<T>)  return div(a, if_else(cond, b, eve::one_));
    else  return cond ? div(a, b) : a;
  }

  //-----------------------------------------------------------------------------------------------
  //  Saturated Masked case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE  auto div_( EVE_SUPPORTS(cpu_)
                            , T const &cond
                            , saturated_type const &
                            , U const &a
                            , V const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<U>,U,V>,
            detail::either<is_Vectorized_v<V>, is_Vectorized_v<U>>
          )
  {
    if constexpr(is_Vectorized_v<T>) return if_else(cond, saturated_(div)(a, b), a);
    else return cond ? saturated_(div)(a, b) : a;
  }
}

#endif
