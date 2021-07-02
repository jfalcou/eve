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
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, auto BitsPattern>
  EVE_FORCEINLINE auto Constant(eve::as<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
    {
      return static_cast<T>(BitsPattern);
    }
    else
    {
      if constexpr(sizeof(t_t) != sizeof(BitsPattern))
      {
        static_assert ( sizeof(t_t) == sizeof(BitsPattern),
                        "[eve::constant] floating_point case - BitsPattern has not the correct size"
                      );
        return T{};
      }
      else
      {
        return static_cast<T>(bit_cast(BitsPattern,as<t_t>{}));
      }
    }
  }
}

