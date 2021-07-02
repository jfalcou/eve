//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(valmax_, valmax);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto valmax_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = detail::value_type_t<T>;
      return T(std::numeric_limits<t_t>::max());
    }
  }
}
