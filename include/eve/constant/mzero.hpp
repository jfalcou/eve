//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(mzero_, mzero);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto mzero_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        return T(-0.0f);
      }
      else if constexpr(std::is_same_v<t_t, double>){
        return T(-0.0);
      }
      else
      {
        return T(0);
      }
    }
  }
}
