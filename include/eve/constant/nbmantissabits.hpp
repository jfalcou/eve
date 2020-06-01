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
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(nbmantissabits_, nbmantissabits_);

  template<floating_value T>
  EVE_FORCEINLINE auto Nbmantissabits(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<T>;

    if constexpr(std::is_same_v<t_t, float>)
    {
      return i_t(23);
    }
    else if constexpr(std::is_same_v<t_t, double >)
    {
      return i_t(52);
    }
  }

  EVE_MAKE_NAMED_CONSTANT(nbmantissabits_, Nbmantissabits);
}

