//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ARG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ARG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>  
#include <eve/assert.hpp>
#include <eve/tags.hpp>
#include <eve/as.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    if constexpr(!std::is_floating_point_v<value_type<T>>)
      EVE_ASSERT(false, "[eve::arg] -this function is not to be used with integral types"); 
    return if_else(is_negative(a),Pi(as(a)), eve::zero_);

  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr T arg_(EVE_SUPPORTS(cpu_)
                                  , pedantic_type const &  
                                  , T const &a) noexcept
  {
    if constexpr(!std::is_floating_point_v<value_type<T>>)
      EVE_ASSERT(false, "[eve::arg[pedantic_]] -this function is notto be used with integral types"); 
    auto r = arg(a); 
#ifndef BOOST_SIMD_NO_NANS
    return if_else(is_nan(a),eve::allbits_, r);
#else
    return r;
#endif
  }
}

#endif
