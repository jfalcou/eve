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

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(allbits_, allbits);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      using i_t           = detail::as_integer_t<t_t, unsigned>;
      constexpr auto mask = ~0ULL;

      if constexpr(std::is_integral_v<t_t>) return T(mask);
      else                                  return T(bit_cast(i_t(mask), as_<t_t>() ));
    }
  }
}
