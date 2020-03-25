//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FNMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FNMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/fms.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fnms_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept Requires(
      std::conditional_t<!is_Vectorized_v<T>, std::conditional_t<is_Vectorized_v<U>, U, V>, T>,
      detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>, is_Vectorized_v<V>>)
  {
    return fms(-a, b, c);
  }

  template<typename D, typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fnms_(EVE_SUPPORTS(cpu_)
       , D const &
       , T const &a, U const &b, V const &c) noexcept
  Requires(
    std::conditional_t<!is_Vectorized_v<T>, std::conditional_t<is_Vectorized_v<U>, U, V>, T>,
    detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>, is_Vectorized_v<V>>)
  {
    return D()(fms)(-a, b, c);
  } 
}

#endif
