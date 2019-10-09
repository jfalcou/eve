//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_GENERIC_BITINTEGER_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_GENERIC_BITINTEGER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_cast.hppq > 
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez>
#include <eve/function/sub.hpp> 
#include <eve/constant/signmask.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_integer_t<T> 
  bitinteger( T const &a) noexcept
  {
    using r_t = as_integer_t<T>; 
    r_t a0 = simd::bitwise_cast(a, as<r_t>());
    return if_else(bs::is_positive(a), a0, Signmask<result>()-a0 );
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_floating_point_t<T> 
  bitfloating( T const &a) noexcept
  {
    using r_t = as_floating_point_t<T>;
    r_t s = bitwise_cast(Signmask<r_t>(), as<r_t>());
    return bitwise_cast(if_else(is_gez(a), a, s-a), as<r_t>());
  }
  
}

#endif
