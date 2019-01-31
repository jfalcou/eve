//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ALLBITS_HPP_INCLUDED
#define EVE_CONSTANT_ALLBITS_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  EVE_FORCEINLINE auto Allbits(as_<T> const & = {})
  {
    using t_t           = detail::value_type_t<T>;
    using i_t           = detail::as_integer_t<t_t, unsigned>;
    constexpr auto mask = ~0ULL;

    if constexpr(std::is_integral_v<t_t>)
      return T(mask);
    else
      return T(bitwise_cast<t_t>(i_t(mask)));
  }
}

#endif
