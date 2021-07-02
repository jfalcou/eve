//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(allbits_, allbits);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      using i_t           = as_integer_t<t_t, unsigned>;
      constexpr auto mask = ~0ULL;

      if constexpr(std::is_integral_v<t_t>) return T(mask);
      else                                  return T(bit_cast(i_t(mask), as<t_t>() ));
    }
  }
}
