//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(minf_, minf);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minf_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      return T(-std::numeric_limits<t_t>::infinity());
    }
  }
}
