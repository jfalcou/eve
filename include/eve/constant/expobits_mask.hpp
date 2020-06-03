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
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //TODO: RENOMMAGE EN  Exponentmask
  EVE_MAKE_CALLABLE(expobits_mask_, expobits_mask_);

  template<floating_value T>
  EVE_FORCEINLINE auto Expobits_mask(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<T, signed>;
    if constexpr(std::is_same_v<t_t, float>) return i_t(0x7f800000);
    else if constexpr(std::is_same_v<t_t, double >) return i_t(0x7ff0000000000000LL);
  }

  EVE_MAKE_NAMED_CONSTANT(expobits_mask_, Expobits_mask);
}

