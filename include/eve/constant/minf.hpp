//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
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
  EVE_MAKE_CALLABLE(minf_, minf_);

  template<floating_value T>
  EVE_FORCEINLINE auto Minf(eve::as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    return T(-std::numeric_limits<t_t>::infinity());
  }

  EVE_MAKE_NAMED_CONSTANT(minf_, Minf);
}

