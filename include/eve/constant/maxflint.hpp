//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MAXFLINT_HPP_INCLUDED
#define EVE_CONSTANT_MAXFLINT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(maxflint_, maxflint_);

  template<typename T>
  EVE_FORCEINLINE auto Maxflint(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x4b800000U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x4340000000000000LL>();
    if constexpr(std::is_integral_v<t_t>) return Valmax<T>();
  }

  EVE_MAKE_NAMED_CONSTANT(maxflint_, Maxflint);
}

#endif
