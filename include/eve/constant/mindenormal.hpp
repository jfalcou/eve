//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MINDENORMAL_HPP_INCLUDED
#define EVE_CONSTANT_MINDENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(mindenormal_, mindenormal_);

  template<typename T>
  EVE_FORCEINLINE T Mindenormal(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>) return T(1);
    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x1U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x1ULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(mindenormal_, Mindenormal);
}

#endif
