//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/ 
//==================================================================================================
#ifndef EVE_CONSTANT_LIMITEXPONENT_HPP_INCLUDED
#define EVE_CONSTANT_LIMITEXPONENT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as_logical.hpp> 
#include <eve/is_logical.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(limitexponent_, limitexponent_);

  template<typename T>
  EVE_FORCEINLINE auto Limitexponent(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>; 
    using i_t = detail::as_integer_t<t_t>;
    if  constexpr(std::is_floating_point_v<t_t>)
    {
      if constexpr(std::is_same_v<t_t, float>) return i_t(1286);
      if constexpr(std::is_same_v<t_t, double >) return i_t(1024);
    }
    else
      return i_t(0); 
  }

  EVE_MAKE_NAMED_CONSTANT(limitexponent_, Limitexponent);
}

#endif
