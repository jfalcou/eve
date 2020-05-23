//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MAXEXPONENTM1_HPP_INCLUDED
#define EVE_CONSTANT_MAXEXPONENTM1_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(maxexponentm1_, maxexponentm1_);

  template<floating_value T>
  EVE_FORCEINLINE auto Maxexponentm1(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return i_t(126);
    else if constexpr(std::is_same_v<t_t, double >) return i_t(1022);
  }

  EVE_MAKE_NAMED_CONSTANT(maxexponentm1_, Maxexponentm1);
}

#endif
