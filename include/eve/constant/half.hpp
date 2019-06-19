//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_HALF_HPP_INCLUDED
#define EVE_CONSTANT_HALF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp> 
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(half_, half_);

  template<typename T>
  EVE_FORCEINLINE auto Half(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    
    if constexpr(std::is_integral_v<t_t>)     return T(0);
    if constexpr(std::is_same_v<t_t, float>)  return Constant<T, 0x3F000000U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3FE0000000000000ULL>();           
  }
  
  EVE_MAKE_NAMED_CONSTANT(half_, Half);
}

#endif
