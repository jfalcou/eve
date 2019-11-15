//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_EXPOBITS_MASK_HPP_INCLUDED
#define EVE_CONSTANT_EXPOBITS_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp> 
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve 
{
  EVE_MAKE_CALLABLE(expobits_mask_, expobits_mask_);

  template<typename T>
  EVE_FORCEINLINE auto Expobits_mask(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>; 
    using i_t = detail::as_integer_t<T, signed>;
    if  constexpr(std::is_floating_point_v<t_t>)
    {
      if constexpr(std::is_same_v<t_t, float>) return i_t(0x7f800000);
      if constexpr(std::is_same_v<t_t, double >) return i_t(0x7ff0000000000000LL);
    }
    else
      return i_t(0); 
  }

  EVE_MAKE_NAMED_CONSTANT(expobits_mask_, Expobits_mask);
}

#endif
