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
  EVE_MAKE_CALLABLE(minexponent_, minexponent_);

  template<floating_value T>
  EVE_FORCEINLINE auto Minexponent(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<t_t>;

    if constexpr(std::is_same_v<t_t, float>) return i_t(-126);
    else if constexpr(std::is_same_v<t_t, double >) return i_t(-1022);
  }

  EVE_MAKE_NAMED_CONSTANT(minexponent_, Minexponent);
}

