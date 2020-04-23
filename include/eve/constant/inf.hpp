//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_INF_HPP_INCLUDED
#define EVE_CONSTANT_INF_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(inf_, inf_);

  template<floating_value T>
  EVE_FORCEINLINE auto Inf(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    return T(std::numeric_limits<t_t>::infinity());
  }

  EVE_MAKE_NAMED_CONSTANT(inf_, Inf);
}

#endif
