//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FNMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FNMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fnma_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>)
  {
    return eve::fma(-a, b, c);
  }

  template<typename D, typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fnma_(EVE_SUPPORTS(cpu_)
     ,  D const & deco
      , T const &a, U const &b, V const &c) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>)
  {
    return deco(fma)(-a, b, c); 
  }  
}

#endif
