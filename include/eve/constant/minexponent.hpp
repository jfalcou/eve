//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MINEXPONENT_HPP_INCLUDED
#define EVE_CONSTANT_MINEXPONENT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp> 
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(minexponent_, minexponent_);

  template<typename T>
  EVE_FORCEINLINE auto Minexponent(as_<T> const & = {})
  {
    using i_t = as_integer_t<T>;
    if  constexpr(std::isfloating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>) return i_t(-126);
      if constexpr(std::is_same_v<T, double >) return i_t(-1022);
    }
    else
      return i_t(0); 
  }

  EVE_MAKE_NAMED_CONSTANT(minexponent_, Minexponent);
}

#endif
