//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_PI_HPP_INCLUDED
#define EVE_CONSTANT_PI_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(pi_, pi_);

  template<floating_value T>
  EVE_FORCEINLINE auto Pi(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x40490FDBU>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x400921FB54442D18ULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(pi_, Pi);
}

#endif
