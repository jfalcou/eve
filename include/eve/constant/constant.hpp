//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_CONSTANT_HPP_INCLUDED
#define EVE_CONSTANT_CONSTANT_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, auto BitsPattern>
  EVE_FORCEINLINE auto Constant(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
      return static_cast<T>(BitsPattern);
    else
      return static_cast<T>(bitwise_cast<t_t>(BitsPattern));
  }
}

#endif
