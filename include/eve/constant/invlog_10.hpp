//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_INVLOG_10_HPP_INCLUDED
#define EVE_CONSTANT_INVLOG_10_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(invlog_10_, invlog_10_);

  template<floating_value T>
  constexpr EVE_FORCEINLINE auto Invlog_10(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x3ede5bd9U>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3fdbcb7b1526e50eULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(invlog_10_, Invlog_10);
}

#endif
