//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(limitexponent_, limitexponent_);

  template<typename T>
  EVE_FORCEINLINE auto Limitexponent(eve::as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<t_t>;

    if constexpr(std::is_same_v<t_t, float>) return i_t(128);
    else if constexpr(std::is_same_v<t_t, double >) return i_t(1024);
  }

  EVE_MAKE_NAMED_CONSTANT(limitexponent_, Limitexponent);
}

