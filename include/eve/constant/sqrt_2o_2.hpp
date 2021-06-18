//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(sqrt_2o_2_, sqrt_2o_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto sqrt_2o_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      return T(0.70710678118654752440084436210484903928483593768847);
    }
  }
}
