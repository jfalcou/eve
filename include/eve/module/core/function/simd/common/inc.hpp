//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_INC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_INC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/add.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto inc_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v) noexcept
  {
    return v+One(as(v)); 
  }
  

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto inc_(EVE_SUPPORTS(simd_)
                                     , U const & cond
                                     , wide<T, N, ABI> const &v) noexcept
  {
    using t_t =  wide<T, N, ABI>; 
    if constexpr(!is_vectorized_v<U>)
      return cond ? inc(v) : v;
    else
      if constexpr(std::is_integral_v<T>)
        return v-(bitwise_mask(bitwise_cast<t_t>(cond)));
      else
        return if_else(cond, v+One(as(v)), v);
  }

}

#endif
